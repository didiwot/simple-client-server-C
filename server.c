#include "erproc.h"
#include <sys/types.h> 
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
	int server = Socket(AF_INET, SOCK_STREAM, 0); 
	/*Создание сокета, т.к. взаимодействие происходит через IPv4 первый аругмент = AF_INET
	второй аргумент - настройка передачи данных
	протокол задаём по умолчанию
	Библиотеки: sys/types.h | sys/socket.h*/
	struct sockaddr_in adr = {0}; // инициализируем adr и заполняем структуру нулями(c99)
	adr.sin_family = AF_INET; //семейство адресов как на сокете
	adr.sin_port = htons(12345); //порт задаём (htons(Host To Network Short) - конвертация в сетевой порядок расположения байтов)
	Bind(server,(struct sockaddr *) &adr,sizeof adr);
	/*Именование сокета(связывание с адресом в выбранном домене)
	первый аргумент дескриптор сокета, второй - адрес сокета, третий размер структуры*/
	Listen(server, 5); //сервер привязывается к аддресу сервера
	socklen_t addrlen = sizeof adr;
	int fd = Accept(server,(struct sockaddr *) &adr, &addrlen); //функция для готовности сервера
	ssize_t nread; //
	char buf[256];
	nread = read(fd,buf,256);
	if(nread == -1){
		perror("read failed");
		exit(EXIT_FAILURE);
	}
	if(nread == 0){
		printf("END OF FILE\n");
	}
	write(STDOUT_FILENO, buf, nread);
	write(fd, buf, nread);

	sleep(15);

	close(fd);
	close(server);
	return 0;
}
