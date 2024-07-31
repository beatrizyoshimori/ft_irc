/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:16:08 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/24 21:16:10 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

void	Message::parseMessage(std::string line)
{
	if (line.empty())
		throw std::runtime_error("Empty line.");
	if (line[0] == ':')
	{
		this->prefix = line.substr(1, line.find(' ') - 1);
		line = line.substr(line.find(' ') + 1, line.size() - 1);
	}
	this->params = Utils::split(line, " ");
	this->command = params.front();
	this->params.erase(this->params.begin());
	if (!params.empty() && params.back().find(':') != std::string::npos)
		params.back().erase(0, 1);

	// // Parse checking
	// std::cout << "prefix:" << this->prefix << std::endl;
	// std::cout << "command:" << this->command << std::endl << "params:";
	// for (std::vector<std::string>::iterator i = this->params.begin(); i != params.end(); i++)
	// 	std::cout << *i << ' ';
	// std::cout << std::endl;
}

void	Message::handleMessage(CommandArgs &cArgs)
{
	if (cArgs.msg.params.size() > 15)
	{
		cArgs.client.sendReplyToClient(ERR_NEEDMOREPARAMS(cArgs.msg.command, "Too many params"), cArgs.client);
		return ;
	}
	Commands::callFunction(cArgs);
}
