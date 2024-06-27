#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM_PORTS 10

int get_listener_socket(const char *port) {
  struct addrinfo hints, *res, *p;
  int s;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags =
      AI_PASSIVE; // letting the local machine host the server for now

  if (getaddrinfo(NULL, port, &hints, &res) != 0) {
    perror("getaddrinfo");
    exit(1);
  }

  for (p = res; p != NULL; p = p->ai_next) {
    s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (s < 0)
      continue;

    if (bind(s, p->ai_addr, p->ai_addrlen) < 0) {
      close(s);
      continue;
    }
    break;
  }
  freeaddrinfo(res);

  if (p == NULL)
    return -1;

  if (listen(s, NUM_PORTS) < 0)
    return -1;

  return s;
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("usage: port number to listen on\n");
    exit(1);
  }
  int s = get_listener_socket(argv[1]);

  struct sockaddr_storage client_addr;
  socklen_t client_size = sizeof client_addr;

  for (;;) {
    int client_fd = accept(s, (struct sockaddr *)&client_addr, &client_size);
    if (client_fd == -1) {
      perror("accept");
      continue;
    }

    if (send(client_fd, "HTTP/1.0 200 OK/r/n/r/nasdf", 27, 0) == -1)
      perror("send");
    close(client_fd);
  }

  return 0;
}
