/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:20:42 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/27 21:41:39 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::string	part(CommandArgs cArgs)
{
	if (cArgs.msg.params.size() < 1 || cArgs.msg.params.size() > 2)
		return (ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong number of parameters"));
	
	std::string					reply;
	std::vector<std::string>	channels = Utils::split(cArgs.msg.params[0], ",");
	std::string					message;
	if (cArgs.msg.params.size() == 2)
		message = cArgs.msg.params[1];
	else
		message = "No message";
	for (size_t i = 0; i < channels.size(); i++)
	{
		std::string	channelName = channels[i];
		std::vector<Channel>::iterator	it = find(cArgs.server.getChannels().begin(), cArgs.server.getChannels().end(), channelName);
		if (it == cArgs.server.getChannels().end())
		{
			// cArgs.client.sendReply(ERR_NOSUCHCHANNEL(channelName),)
			// reply += ERR_NOSUCHCHANNEL(channelName);
			continue ;
		}
		if (!it->isClientOnChannel(cArgs.client))
		{
			reply += ERR_NOTONCHANNEL(channelName);
			continue ;
		}
		it->removeClient(cArgs.client);
		if (it->getClients().empty())
			cArgs.server.getChannels().erase(it);
		
	}
	return (reply);
}
