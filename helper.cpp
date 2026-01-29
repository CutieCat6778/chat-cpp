#include <iostream>

std::string readInputFromTerminal() {
  std::string input;
  std::cout << "Enter text: ";
  std::getline(std::cin, input);
  return input;
}

int printMessage(const std::string &message, int side) {
  std::string sideStr = (side == 0) ? "Server" : "Client";
  std::cout << sideStr << ": " << message << std::endl;
  return 0;
}
