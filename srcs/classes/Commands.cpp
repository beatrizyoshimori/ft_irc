/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:16:13 by byoshimo          #+#    #+#             */
/*   Updated: 2024/08/31 19:37:52 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::map<std::string, Commands::funcPtr> Commands::_commands;

void	Commands::populateMap(void)
{
	_commands["USER"] = user;
	_commands["NICK"] = nick;
	_commands["PASS"] = pass;
	// _commands["CAP"] = cap;
	_commands["QUIT"] = quit;
	_commands["JOIN"] = join;
	// _commands["LISTC"] = listc;
	_commands["PRIVMSG"] = privmsg;
	_commands["KICK"] = kick;
	_commands["PART"] = part;
	// _commands["WHO"] = who;
	_commands["MODE"] = mode;
	_commands["TOPIC"] = topic;
	_commands["INVITE"] = invite;
}

void	Commands::callFunction(CommandArgs &cArgs)
{
	if (_commands.find(cArgs.msg.command) == _commands.end())
	{
		std::cerr << "Invalid command\r\n" << std::endl; //colocar sendReplyToClient
		return ;
	}
	if (!cArgs.client.isAuthenticated() && (cArgs.msg.command != "USER" && cArgs.msg.command != "NICK" && cArgs.msg.command != "PASS"))
	{
		cArgs.client.sendReplyToClient(ERR_NOTREGISTERED(cArgs.client.getNick()), cArgs.client);
		return ;
	}
	_commands[cArgs.msg.command](cArgs);
}
