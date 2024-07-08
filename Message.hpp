#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include "ft_irc.hpp"

class	Message
{
	private:
		std::string					prefix;
		std::string					command;
		std::vector<std::string>	params;	

	public:
		Message(void) {};
		~Message(void) {};

		void	parseMessage(std::string line);
};

#endif