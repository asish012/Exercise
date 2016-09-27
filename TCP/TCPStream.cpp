#include <arpa/inet.h>
#include "TCPStream.h"
#include <iostream>

TCPStream::TCPStream(int sd, struct sockaddr_in *address) : _sd(sd), _peer(nullptr) {
  char ip[50];
  inet_ntop(AF_INET, (struct in_addr*) &(address->sin_addr.s_addr), ip, sizeof(ip) - 1);
  _peer = new Peer(std::string(ip), ntohs(address->sin_port)); // ntohs = network to host (short)
}

TCPStream::~TCPStream() {
  close(_sd);
  delete _peer;
}

ssize_t TCPStream::send(std::string const &buffer) {
  std::cout << "sending through sd: " << _sd << std::endl;
  return ::write(_sd, buffer.c_str(), buffer.length());
}

ssize_t TCPStream::receive(std::string const &buffer, size_t len) {
  std::cout << "receiving through sd: " << _sd << std::endl;
  return ::read(_sd, (void *)buffer.c_str(), len);
}
