#ifndef FT_IRC_HPP
# define FT_IRC_HPP

# define MAX_PORT 65535
# define TIMEOUT_MS 1000
# define BUFFER_SIZE 512

#define CRLF std::string("\r\n")

#include <string>
#include <sstream>
#include <vector>
#include <queue>

#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <poll.h>

class   Server;
class   Client;

#include "Client.hpp"
#include "Server.hpp"

#endif