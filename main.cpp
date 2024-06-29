
#include "ft_irc.hpp"
#include <iostream>

int	main(int argc, char **argv)
{
	try
	{
		if (argc != 3)
			throw std::runtime_error("Error: wrong number of arguments!\nUsage: ./ircserv <port> <password>");

		Server	server;
		server.setPort(argv[1]);
		server.setPassword(argv[2]);
		server.configureTCP();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
