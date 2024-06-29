#include "Server.hpp"

void    Server::setPort(char *input)
{
    std::istringstream  toInt(input);
	int number;
	toInt >> number;

	if (number <= 0 || number > MAX_PORT)
		throw std::runtime_error("Invalid port number.");

	this->_serverPort = number;
}

void	Server::setPassword(char *input)
{
	// check valid characters

	this->_serverPassword = input;
}

void	Server::createSocket(void)
{
	const int	ENABLE = 1;

	this->_socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socketFileDescriptor < 0)
		throw std::runtime_error("Failed to create socket.");
	if (setsockopt(this->_socketFileDescriptor, SOL_SOCKET, SO_REUSEADDR, &ENABLE, sizeof(int)) < 0)
		throw std::runtime_error("Failed to set socket options.");
	if (fcntl(this->_socketFileDescriptor, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("Failed to set the non-blocking mode on socket file descriptor");
}

void	Server::defineServerAddress(void)
{
	// std::memset(&_serverAddr, 0, sizeof(_serverAddr)); precisa?
	this->_serverAddress.sin_family = AF_INET;
	this->_serverAddress.sin_port = htons(this->_serverPort);
	this->_serverAddress.sin_addr.s_addr = INADDR_ANY;
}

void	Server::bindSocket(void)
{
	if (bind(_socketFileDescriptor, (sockaddr *)&_serverAddress, sizeof(_serverAddress)))
		throw std::runtime_error("Failed to bind server file descriptor to socket.");
}

void	Server::listenForConnections(void)
{
	if (listen(_socketFileDescriptor, 1024) == -1)
		throw std::runtime_error("Failed to listen on socket.");
}

void	Server::configureTCP(void)
{
	createSocket();
	defineServerAddress();
	bindSocket();
	listenForConnections();
}

void	Server::pollActiveConnections(void)
{
	if (poll(_connectionsPollfds.data(), _connectionsPollfds.size(), TIMEOUT_MS) < 0)
		throw std::runtime_error("Polling error.");
}

void	Server::acceptNewClients(void)
{
	// if ((Server::_connectionsPollfds[0].revents & POLLIN) == POLLIN)
	// {
		sockaddr_in	newClientAddress;
		socklen_t	addressLength = sizeof(newClientAddress);
		int	newClientSocketDescriptor = accept(this->_socketFileDescriptor, (sockaddr *) &newClientAddress, &addressLength);

		if (newClientSocketDescriptor < 0)
			throw std::runtime_error("Failed to accept new client.");
		if (fcntl(newClientSocketDescriptor, F_SETFL, O_NONBLOCK) == -1)
			throw std::runtime_error("Failed to set client socket descriptor to non-blocking mode.");
		_connectionsPollfds.push_back((pollfd) {.fd = newClientSocketDescriptor, .events = POLLIN});
		
		Client	newClient(newClientSocketDescriptor);
		_clients.push_back(newClient);
	// }
}

bool operator==(const pollfd &pollfd, const int &clientFd)
{
	return (pollfd.fd == clientFd);
}

bool	Server::detectedActivity(const int &clientFd)
{
	std::vector<pollfd>::iterator pollfd = std::find(_connectionsPollfds.begin(), _connectionsPollfds.end(), clientFd);
	return ((pollfd->revents & POLLIN) == POLLIN);
}

void	Server::processClientsActivity(void)
{
	// if (_clients.empty())
	// 	return ;
	for (size_t i = 0; i < _clients.size(); i++)
	{
		Client &client = _clients[i];
		if (detectedActivity(client.getFd()))
		{
			return ;
			client.receiveData();
			client.pushToCommandQueue();

			std::queue<std::string>	commands = client.getCommandsQueue();
			while(!commands.empty())
			{
				std::string	line = commands.front();
				commands.pop();
				
			}
		}
	}
}

void	Server::start(void)
{
	//Handle signal

	_connectionsPollfds.push_back((pollfd) {.fd = this->_socketFileDescriptor, .events = POLLIN});
	while (true)
	{
		pollActiveConnections();
		acceptNewClients();
		processClientsActivity();
	}
}
