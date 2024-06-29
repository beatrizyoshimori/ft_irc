#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "ft_irc.hpp"

class	Client
{
	private:
		int			_fd;
		bool		_removeClient;
		std::string	_data;

		std::queue<std::string>	_commandsQueue;

	public:
		Client(void);
		Client(int socketDescriptor);
		~Client(void) {};

		int						getFd(void) const;
		void					setRemoveClient(bool state);
		std::queue<std::string>	getCommandsQueue(void) const;

		void	receiveData(void);
		void	pushToCommandQueue(void);
};

#endif