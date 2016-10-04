#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0)
        perror("invalid socket\n");

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    int bnd = bind(fd, (struct sockaddr *)&addr, sizeof(addr));

    if (bnd < 0)
        perror("bind failed\n");

    int lstn = listen(fd, 512);

    if (lstn < 0)
        perror("listen failed\n");

    struct sockaddr_in client;
    int length;
    int sock;
    char buffer[512];

    for (;;) {
        length = sizeof(client);
        sock = accept(fd, (struct sockaddr *)&client, (socklen_t *)&length);

        if (sock < 0)
            perror("accept failed\n");

        recv(sock, buffer, sizeof(buffer), 0);
        printf("%s\n", buffer);
    }

    return 0;
}
