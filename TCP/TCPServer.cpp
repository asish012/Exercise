#include <stdio.h>
#include <arpa/inet.h>
#include "TCPServer.h"

TCPServer::TCPServer(std::string const &address, int port) :
  _sd(0), _address(address.length() ? address : "localhost"), _port(port), _isListening(false)
{}

TCPServer::~TCPServer() {
  if (_sd) { close(_sd); }
}

int TCPServer::start() {
  if (_isListening) return 0;

  _sd = socket(PF_INET, SOCK_STREAM, 0);

  struct sockaddr_in address;
  memset(&address, 0, sizeof(address));

  address.sin_family = PF_INET;
  address.sin_port   = htons(_port);

  if (_address.size() > 0) {
    inet_pton(PF_INET, _address.c_str(), &(address.sin_addr));
  }
  else {
    address.sin_addr.s_addr = INADDR_ANY;
  }

  int optval = 1;
  setsockopt(_sd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

  int result = bind(_sd, (struct sockaddr*)&address, sizeof(address));
  if (result != 0) {
    perror ("bind() failed");
    return result;
  }

  result =  listen(_sd, 5);
  if (result != 0) {
    perror ("listen() failed");
    return result;
  }

  _isListening = true;
  return result;
}

TCPStream* TCPServer::accept() {
  if (not _isListening) return nullptr;

  struct sockaddr_in address;
  socklen_t len = sizeof(address);
  memset(&address, 0, sizeof(address));

  int sd = ::accept(_sd, (struct sockaddr*)&address, &len);
  if (sd < 0) {
    perror("accept() failed");
    return nullptr;
  }

  return new TCPStream(sd, &address);
}












