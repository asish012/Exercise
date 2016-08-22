#include <netinet/in.h>
#include <string>
#include "TCPStream.h"

//
// TCPClient / TCPAcceptor
//
class TCPServer {
public:
  explicit TCPServer(std::string const &address, int port);
  ~TCPServer();

  int start();
  TCPStream* accept();

private:
  int _sd;    //socket descriptor
  std::string _address;
  int _port;
  bool _isListening;
};
