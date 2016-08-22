#include <iostream>
#include "TCPServer.h"

//
// Server main
//
int main(int argc, char** argv) {

  std::cout << "usage: server <port> <server/ip>\n";
  if (argc < 2 or argc > 4) { return 0; }

  TCPStream *stream = nullptr;
  TCPServer *server = nullptr;

  if (argc == 3) {
    server = new TCPServer(std::string(argv[1]), atoi(argv[2]));
  }
  else {
    server = new TCPServer(std::string(), atoi(argv[1]));
  }

  if (server->start() == 0) {
    while (true) {
      stream = server->accept();

      if (stream != nullptr) {
        std::string line(256, '\0');
        size_t len;
        while ( (len = stream->receive(line, sizeof(line))) > 0 ) {
          std::cout << "server received: " << line << std::endl;

          stream->send("Server says: Fuck-off");
        }
        delete stream;
      }
    }
  }

  perror("Couldn't start the server");

  return 0;
}
