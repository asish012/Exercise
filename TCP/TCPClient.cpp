#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include "TCPClient.h"
#include <iostream>

TCPStream* TCPClient::connect(std::string const &server, int port) {
  struct sockaddr_in address;
  memset(&address, 0, sizeof(address));

  address.sin_family = AF_INET;
  address.sin_port   = htons(port);

  if (resolveHostName(server.c_str(), &(address.sin_addr)) != 0) {
    // host_name could not be resolved. thus it is assumed to be an ip address
    // so, copy that value (server) to address.sin_addr
    inet_pton(AF_INET, server.c_str(), &(address.sin_addr));
  }

  int sd = ::socket(AF_INET, SOCK_STREAM, 0);
  std::cout << "client:: sd: " << sd << std::endl;

  if (::connect(sd, (struct sockaddr*) &address, sizeof(address)) != 0) {
    return nullptr;
  }

  return new TCPStream(sd, &address);
}

// resolve the underneath ip_address of a string host_name
int TCPClient::resolveHostName(std::string const &host, in_addr *addr) {
  struct addrinfo *info;

  int result = getaddrinfo(host.c_str(), nullptr, nullptr, &info);
  if (not result) {
    memcpy( addr, &(((struct sockaddr_in *)info->ai_addr)->sin_addr), sizeof(struct in_addr) );
    freeaddrinfo(info);
  }

  return result;
}
