#include "Client.hpp"

Client::Client(int socketDescriptor)
{
    this->_fd = socketDescriptor;
	this->_removeClient = false;
}

int Client::getFd(void) const
{
    return (this->_fd);
}

void	Client::setRemoveClient(bool state)
{
	this->_removeClient = state;
}

std::queue<std::string>	Client::getCommandsQueue(void) const
{
	return (this->_commandsQueue);
}

void    Client::receiveData(void)
{
	char	buff[BUFFER_SIZE];
	std::memset(buff, 0, BUFFER_SIZE);

	long	nbytes = recv(this->getFd(), buff, BUFFER_SIZE, 0);
	if (nbytes == 0)
		this->setRemoveClient(true);
	else
		this->_data.append(buff, nbytes);
}

std::vector<std::string>	split(std::string str, std::string delimeter)
{
	std::vector<std::string>	tokens;

	size_t	start = 0;
	size_t	end;
	size_t	del_size = delimeter.size();

	while((end = str.find(delimeter, start)) != std::string::npos)
	{
		tokens.push_back(str.substr(start, end - start));
		start = end + del_size;
	}
	tokens.push_back(str.substr(start));
	tokens.erase(std::remove(tokens.begin(), tokens.end(), ""), tokens.end());
	return (tokens);
}

void	Client::pushToCommandQueue(void)
{
	if (this->_data.empty())
		return ;
	std::vector<std::string>	commands = split(this->_data, CRLF);
	if (commands.back().size() < 2 || commands.back().find(CRLF) == std::string::npos)
	{
		this->_data = commands.back();
		commands.pop_back();
	}
	else
		this->_data.clear();
	for (std::vector<std::string>::iterator command = commands.begin(); command != commands.end(); command++)
		this->_commandsQueue.push(*command);
}
