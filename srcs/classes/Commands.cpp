/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:16:13 by byoshimo          #+#    #+#             */
/*   Updated: 2024/08/10 20:21:29 by byoshimo         ###   ########.fr       */
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
	// _commands["MODE"] = mode;
	// _commands["TOPIC"] = topic;
	_commands["INVITE"] = invite;
}

void	Commands::callFunction(CommandArgs &cArgs)
{
	//Check user authentication
	if (_commands.find(cArgs.msg.command) == _commands.end())
	{
		std::cerr << "Invalid command\r\n" << std::endl;
		return ;
	}
	_commands[cArgs.msg.command](cArgs);
}
