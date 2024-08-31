/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:15:47 by byoshimo          #+#    #+#             */
/*   Updated: 2024/08/31 20:15:51 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#include <utility>

void	mode(CommandArgs cArgs)
{
	if (cArgs.msg.params.size() < 1)
	{
		cArgs.client.sendReplyToClient(ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong number of parameters"), cArgs.client);
		return ;
	}

	std::string	channelName = cArgs.msg.params[0];
	std::vector<Channel>::iterator	itChannel = find(cArgs.server.getChannels().begin(), cArgs.server.getChannels().end(), channelName);
	if (itChannel == cArgs.server.getChannels().end())
	{
		cArgs.client.sendReplyToClient(ERR_NOSUCHCHANNEL(channelName), cArgs.client);
		return ;
	}
	if (!itChannel->isClientOnChannel(cArgs.client))
	{
		cArgs.client.sendReplyToClient(ERR_NOTONCHANNEL(channelName), cArgs.client);
		return ;
	}
	if (cArgs.msg.params.size() == 1)
	{
		cArgs.client.sendReplyToClient(RPL_CHANNELMODEIS(cArgs.client.getNick(), channelName, itChannel->getModes()), cArgs.client);
		return ;
	}
	if (!itChannel->isOperator(cArgs.client))
	{
		cArgs.client.sendReplyToClient(ERR_CHANOPRIVSNEEDED(channelName), cArgs.client);
		return ;
	}

	std::string					modes = cArgs.msg.params[1];
	std::vector<std::string>	modesParams(cArgs.msg.params.begin() + 2, cArgs.msg.params.end());
	bool						action = true;
	for (size_t i = 0; modes.size(); i++)
	{
		if (modes[i] == '+')
			action = true;
		else if (modes[i] == '-')
			action = false;
		else if (modes[i] == 'i')
			itChannel->setInviteOnly(action);
		else if (modes[i] == 't')
			itChannel->setTopicOPOnly(action);
		else if (modes[i] == 'k')
		{
			if (action && !modesParams.empty())
			{
				itChannel->setKey(modesParams[0]);
				modesParams.erase(modesParams.begin());
			}
			else if (modesParams.empty())
				cArgs.client.sendReplyToClient(ERR_SETKEY(channelName), cArgs.client); //retirar o k da resposta?
			else
				itChannel->removeKey();
		}
		else if (modes[i] == 'o')
		{
			std::vector<Client>::iterator	itClient = find(itChannel->getClients().begin(), itChannel->getClients().end(), *modesParams.begin());
			if (itClient == itChannel->getClients().end())
				cArgs.client.sendReplyToClient(ERR_USERNOTINCHANNEL(*modesParams.begin(), channelName), cArgs.client);
			if (action == true && !itChannel->isOperator(*itClient))
				itChannel->addOperator(*itClient);
			else if (action == false)
				itChannel->removeOperator(*itClient);
			modesParams.erase(modesParams.begin());
		}
		else if (modes[i] == 'l')
		{
			if (action == true && (modesParams.empty() || (*modesParams.begin()).find_first_not_of("0123456789") != std::string::npos))
				cArgs.client.sendReplyToClient(ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong argument"), cArgs.client);
			if (action == true)
			{
				itChannel->setUserLimit(std::atoi(modesParams[0].c_str()));
				modesParams.erase(modesParams.begin());
			}
			else
				itChannel->removeUserLimit();
		}
		else
			cArgs.client.sendReplyToClient(ERR_UNKNOWNMODE(modes[i], channelName), cArgs.client);
	}
}
