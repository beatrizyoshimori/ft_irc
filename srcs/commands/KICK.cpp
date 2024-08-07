/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:44:47 by byoshimo          #+#    #+#             */
/*   Updated: 2024/08/07 19:56:02 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void	kick(CommandArgs cArgs)
{
	if (cArgs.msg.params.size() < 2)
	{
		cArgs.client.sendReplyToClient(ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong number of parameters"), cArgs.client);
		return ;
	}
	std::vector<std::string>	channels = Utils::split(cArgs.msg.params[0], ",");
	std::vector<std::string>	clients = Utils::split(cArgs.msg.params[1], ",");
	if (channels.size() != 1 && channels.size() != clients.size())
	{
		cArgs.client.sendReplyToClient(ERR_NEEDMOREPARAMS(cArgs.msg.command, "Different numbers of channels and clients given"), cArgs.client);
		return ;
	}
}
