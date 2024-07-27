/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:14:52 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/27 19:11:10 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::string	join(CommandArgs cArgs)
{
	if (cArgs.msg.params.size() < 1 || cArgs.msg.params.size() > 2)
		return (ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong number of parameters"));
	// if (cArgs.msg.params[0] == "0")
	// {
	// 	//fazer command PART
	// }
	std::string					reply;
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
			reply += ERR_NOSUCHCHANNEL(channelName);
			continue ;
		}
		std::vector<Channel>::iterator	it = find(cArgs.server.getChannels().begin(), cArgs.server.getChannels().end(), channelName);
		Channel	&channel = *it;
		if (it != cArgs.server.getChannels().end())
		{
			if (channel.isClientOnChannel(cArgs.client))
				continue ;
			if (channel.getInviteOnly()) // && !cArgs.client.channelOnInviteList(channelName)
			{
				reply += ERR_INVITEONLYCHAN(channelName);
				continue ;
			}
			if (channel.getKey() != "" && channel.getKey() != channelKey)
			{
				reply += ERR_BADCHANNELKEY(channelName);
				continue ;
			}
			if (channel.getUserLimit() == channel.getClients().size())
			{
				reply += ERR_CHANNELISFULL(channelName);
				continue ;
			}
			channel.addClient(cArgs.client);
			channelUsers = channel.getChannelUsers();
			for (size_t i = 0; i < channel.getClients().size(); i++)
				cArgs.broadcastList.push_back(channel.getClients()[i]);
			channelTopic = channel.getTopic();
			// if (cArgs.client.channelOnInviteList(channelName))
			// 	cArgs.client.removeChannelFromInviteList(channelName);
		}
		else
		{
			Channel	newChannel(channelName);
			newChannel.addClient(cArgs.client);
			newChannel.addOperator(cArgs.client);
			if (!channelKey.empty())
				newChannel.setKey(channelKey);
			channelUsers = newChannel.getChannelUsers();
			cArgs.server.addChannel(newChannel);
		}
		reply += (JOIN(cArgs.client.getUser(), channelName)) \
		+ (channelTopic.empty() ? "" : RPL_TOPIC(cArgs.client.getNick(), channelName, channelTopic)) \
		+ (RPL_NAMREPLY(cArgs.client.getNick(), channelName, channelUsers)) \
		+ (RPL_ENDOFNAMES(cArgs.client.getNick(), channelName));
	}
	return (reply);
}
