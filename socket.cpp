#include "./helper.cpp"
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0) {
    perror("socket");
    return 1;
  }

  // Allows quick restart (avoids "Address already in use")
  int opt = 1;
  setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  sockaddr_in serverAddr{};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    perror("bind");
    return 1;
  }

  if (listen(serverSocket, 5) < 0) {
    perror("listen");
    return 1;
  }

  std::cout << "Server listening on port " << PORT << "...\n";

  int clientSocket = accept(serverSocket, nullptr, nullptr);
  if (clientSocket < 0) {
    perror("accept");
    return 1;
  }

  char buffer[1024];
  ssize_t n = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
  if (n < 0) {
    perror("recv");
    return 1;
  }
  buffer[n] = '\0';

  printMessage(std::string(buffer), 1);

  close(clientSocket);
  close(serverSocket);
  return 0;
}
