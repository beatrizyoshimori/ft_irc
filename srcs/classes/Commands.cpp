#include "Commands.hpp"

std::map<std::string, Commands::funcPtr> Commands::_commands;

void	Commands::populateMap(void)
{
	_commands["USER"] = user;
	// _commands["NICK"] = nick;
	// _commands["PASS"] = pass;
	// _commands["CAP"] = cap;
	// _commands["QUIT"] = quit;
	// _commands["JOIN"] = join;
	// _commands["LISTC"] = listc;
	// _commands["PRIVMSG"] = privmsg;
	// _commands["KICK"] = kick;
	// _commands["PART"] = part;
	// _commands["WHO"] = who;
	// _commands["MODE"] = mode;
	// _commands["TOPIC"] = topic;
	// _commands["INVITE"] = invite;
}

std::string	Commands::callFunction(CommandArgs &cArgs)
{
	std::cout << "aqui" << std::endl;
	//Check user authentication
	if (_commands.find(cArgs.msg.command) == _commands.end())
		return (cArgs.msg.command + " :Invalid command\r\n");
	return (_commands[cArgs.msg.command](cArgs));
}