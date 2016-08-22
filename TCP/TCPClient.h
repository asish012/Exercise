#include <iostream>
#include "TCPStream.h"

//
// TCPHost / TCPConnector
//
class TCPClient {
public:
  TCPStream* connect(std::string const &server, int port);

private:
  int resolveHostName(std::string const &host, struct in_addr *addr);
};
