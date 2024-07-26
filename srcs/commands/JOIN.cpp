/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:14:52 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/26 18:14:52 by byoshimo         ###   ########.fr       */
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
	std::vector<std::string>	channels = Utils::split(cArgs.msg.params[0], ",");
	std::queue<std::string>		keys;
	if (cArgs.msg.params > 1)
		keys = Utils::split(cArgs.msg.params[1], ",");
	for (size_t i = 0; i < channels.size(); i++)
	{
		std::string	channelName = channels[i];
		std::string	channelKey;
		if (!keys.empty())
		{
			channelKey = keys[i];
			keys.pop();
		}
		if (channelName[0] != '#' && channelName[0] != '&')
		{
			reply += ERR_NOSUCHCHANNEL(channelName);
			continue ;
		}
		std::vector<Channel>::iterator	foundChannel = find(cArgs.server.getChannels().begin(), cArgs.server.getChannels().end(), channelName);
		if (foundChannel != cArgs.server.getChannels().end())
		{
			if (foundChannel.isClientOnChannel(cArgs.client))
				continue ;
			
		}
	}
}
