#include <string>
#include "TCPClient.h"

//
// Client main
//
int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "usage: Client <server/ip> <port>\n";
    return 0;
  }

  int len = 256;
  std::string message;
  std::string line(len, '\0');

  TCPClient *client = new TCPClient();
  TCPStream *stream = client->connect(argv[1], atoi(argv[2]));

  if (stream) {
    while (true) {
      std::cout << "write: ";
      std::cin >> message;

      stream->send(message);

      len = stream->receive(line, line.length());
      if (len) {
        std::cout << "server said: " << line << '\n';
      }

      if (line == "quit" or message == "quit") { break; }
    }
  }


  return 0;
}
