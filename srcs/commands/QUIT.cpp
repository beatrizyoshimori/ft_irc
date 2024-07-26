#include "ft_irc.hpp"

std::string	quit(CommandArgs cArgs)
{
	cArgs.client.setRemoveClient(true);
	return ("User has quit IRC");
}
