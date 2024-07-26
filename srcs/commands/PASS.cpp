#include "ft_irc.hpp"

std::string	pass(CommandArgs cArgs)
{
	if (cArgs.msg.params.size() != 1)
		return (ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong number of parameters"));
	if (!cArgs.client.getPass().empty())
		return (ERR_ALREADYREGISTRED(cArgs.client.getUser()));
	cArgs.client.setPass(cArgs.msg.params[0]);
	if (cArgs.client.getPass() != cArgs.server.getServerPassword())
	{
		cArgs.client.setRemoveClient(true);
		return (ERR_PASSWDMISMATCH());
	}
	if (cArgs.client.isAuthenticated())
		return (RPL_WELCOME(cArgs.client.getNick(), cArgs.client.getUser()));
	return ("");
}
