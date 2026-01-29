#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket < 0) {
    perror("socket");
    return 1;
  }

  sockaddr_in serverAddr{};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);

  // Connect to localhost
  if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) != 1) {
    std::cerr << "inet_pton failed\n";
    return 1;
  }

  if (connect(clientSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    perror("connect");
    return 1;
  }

  const char *message = "Hello from client";
  if (send(clientSocket, message, std::strlen(message), 0) < 0) {
    perror("send");
    return 1;
  }

  close(clientSocket);
  return 0;
}
