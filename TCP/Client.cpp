#include <string>
#include "TCPClient.h"

//
// Client main
//
int main(int argc, char **argv) {
  std::cout << "usage: client <server/ip> <port>\n";
  if (argc != 3) { return 0; }

  int len = 256;
  std::string message;
  std::string line(len, '\0');

  TCPClient *client = new TCPClient();
  TCPStream *stream = client->connect(argv[1], atoi(argv[2]));

  if (stream) {
    message = "Is there life on Server?";

    stream->send(message);
    std::cout << "sent: " << message << '\n';

    len = stream->receive(line, line.length());
    if (len) {
      std::cout << line << '\n';
    }
  }


  return 0;
}
