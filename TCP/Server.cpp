#include <iostream>
#include "TCPServer.h"

//
// Server main
//
int main(int argc, char** argv) {

  if (argc != 3) {
    std::cout << "usual usage: Server <server/ip> <port>\n";
  }

  TCPStream *stream = nullptr;
  TCPServer *server = nullptr;

  if (argc == 3) {
    server = new TCPServer(std::string(argv[1]), atoi(argv[2]));
  }
  else {
    server = new TCPServer(std::string("localhost"), 9000);
    std::cout << "server localhost:9000 has been created\n";
  }

  if (server->start() == 0) {
    while (true) {
      stream = server->accept();

      if (stream) {
        std::string line(256, '\0');
        std::string outstr;
        size_t len = 0;
        while ( (len = stream->receive(line, sizeof(line))) > 0 ) {
          std::cout << "server received: " << line << std::endl;

          std::cout << "write response here: ";
          std::cin >> outstr;
          stream->send(outstr);
        }
        delete stream;
      }
    }
  }

  perror("Couldn't start the server");

  return 0;
}
