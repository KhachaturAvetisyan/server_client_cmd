#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define IP "127.0.0.1"
#define PORT 8080


int main(int argc, char const* argv[])
{
    // init
    int sock = 0, client_fd;
    struct sockaddr_in serv_addr{};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, IP, &serv_addr.sin_addr)
        <= 0)
    {
        printf(
                "\nInvalid address/ Address not supported \n");
        return -1;
    }

    // connect
    if ((client_fd
                 = connect(sock, (struct sockaddr*)&serv_addr,
                           sizeof(serv_addr)))
        < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    char buffer[1024] = { 0 };

    // read command
    char *command = readline("~ ");
    int16_t size_command = (int16_t) strlen(command);

    // send sizeof command
    if (send(sock, &size_command, 2, 0) < 0) {
        perror("Error send size of command");
        exit(EXIT_FAILURE);
    }
    printf("Client: send size of command: %hd\n", size_command);

    // send command
    if (send(sock, command, size_command, 0) < 0) {
        perror("Error send command");
        exit(EXIT_FAILURE);
    }
    printf("Client: send command: %s\n", command);

    bzero(buffer, 1024);
    read(sock, buffer, 1024);
    printf("%s\n", buffer);

    // closing the connected socket
    close(client_fd);

    return 0;
}
