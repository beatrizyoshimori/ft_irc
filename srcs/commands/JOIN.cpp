/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:14:52 by byoshimo          #+#    #+#             */
/*   Updated: 2024/09/15 11:35:59 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void	join(CommandArgs cArgs)
{
	if (cArgs.msg.params.size() < 1 || cArgs.msg.params.size() > 2)
	{
		cArgs.client.sendReplyToClient(ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong number of parameters"), cArgs.client);
		return ;
	}
	if (cArgs.msg.params[0] == "0")
	{
		cArgs.msg.params[0].clear();
		for (size_t i = 0; i < cArgs.channels.size(); i++)
		{
			if (cArgs.channels[i].isClientOnChannel(cArgs.client))
			{
				cArgs.msg.params[0].append(cArgs.channels[i].getName());
				cArgs.msg.params[0].append(",");
			}
		}
		// part(cArgs);
		return ;
	}
	std::string					channelUsers;
	std::string					channelTopic;
	std::vector<std::string>	channels = Utils::split(cArgs.msg.params[0], ",");
	std::vector<std::string>	keys;
	if (cArgs.msg.params.size() > 1)
		keys = Utils::split(cArgs.msg.params[1], ",");
	for (size_t i = 0; i < channels.size(); i++)
	{
		std::string	channelName = channels[i];
		std::string	channelKey;
		if (!keys.empty())
		{
			channelKey = keys[i];
			keys.erase(keys.begin());
		}
		if (channelName[0] != '#' && channelName[0] != '&')
		{
			cArgs.client.sendReplyToClient(ERR_NOSUCHCHANNEL(channelName), cArgs.client);
			continue ;
		}
		std::vector<Channel> channels = cArgs.channels;
		std::cout << "channel:" << channels.size() << std::endl;
		std::vector<Channel>::iterator	itChan = channels.begin();
		while (itChan != channels.end())
		{
			std::cout << "channelName: " << itChan->getName();
			itChan++;
		}
		std::vector<Channel>::iterator	it = find(cArgs.channels.begin(), cArgs.channels.end(), channelName);
		Channel	&channel = *it;
		if (it != cArgs.channels.end())
		{
			std::cout << "Channel it: " << it->getName() << std::endl; 
			if (channel.isClientOnChannel(cArgs.client))
				continue ;
			if (channel.getInviteOnly()) // && !cArgs.client.channelOnInviteList(channelName)
			{
				cArgs.client.sendReplyToClient(ERR_INVITEONLYCHAN(channelName), cArgs.client);
				continue ;
			}
			if (channel.getKey() != "" && channel.getKey() != channelKey)
			{
				cArgs.client.sendReplyToClient(ERR_BADCHANNELKEY(channelName), cArgs.client);
				continue ;
			}
			if (channel.getUserLimit() == channel.getClients().size())
			{
				cArgs.client.sendReplyToClient(ERR_CHANNELISFULL(channelName), cArgs.client);
				continue ;
			}
			channel.addClient(cArgs.client);
			channelUsers = channel.getChannelUsers();
			channelTopic = channel.getTopic();
			// if (cArgs.client.channelOnInviteList(channelName))
			// 	cArgs.client.removeChannelFromInviteList(channelName);
			cArgs.client.sendReplyToBroadcastList(JOIN(cArgs.client.getNick(), cArgs.client.getUser(), channelName), channel.getClients());
		}
		else
		{
			Channel	newChannel(channelName);
			newChannel.addClient(cArgs.client);
			newChannel.addOperator(cArgs.client);
			if (!channelKey.empty())
				newChannel.setKey(channelKey);
			channelUsers = newChannel.getChannelUsers();
			cArgs.channels.push_back(newChannel);
			std::vector<Channel> channels = cArgs.channels;
			std::vector<Channel>::iterator	it = channels.begin();
			for ( ; it != channels.end(); it++)
				std::cout << it->getName() << std::endl;
			
			cArgs.client.sendReplyToBroadcastList(JOIN(cArgs.client.getNick(), cArgs.client.getUser(), channelName), newChannel.getClients());
		}
		if (!channelTopic.empty())
			cArgs.client.sendReplyToClient(RPL_TOPIC(cArgs.client.getNick(), channelName, channelTopic), cArgs.client);
		cArgs.client.sendReplyToClient(RPL_NAMREPLY(cArgs.client.getNick(), channelName, channelUsers), cArgs.client);
		cArgs.client.sendReplyToClient(RPL_ENDOFNAMES(cArgs.client.getNick(), channelName), cArgs.client);
	}
}
