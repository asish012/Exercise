#include <sys/socket.h>
#include <string>
#include <unistd.h>

//
// Peer
//
class Peer {
public:
  friend class TCPStream;
private:
  Peer(std::string const &ip, int port) : _peerIP(ip), _peerPort(port) {}

  std::string _peerIP;
  int _peerPort;
};


//
// TCPStream
//
class TCPStream {
public:
  friend class TCPServer;
  friend class TCPClient;

  Peer* getPeer() { return _peer; }
  ssize_t send(std::string const &buffer);
  ssize_t receive(std::string const &buffer, size_t len);

  ~TCPStream();
private:
  TCPStream(int sd, struct sockaddr_in *address);

  int _sd;  //socket descriptor
  Peer *_peer;
};
