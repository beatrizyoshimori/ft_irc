/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:15:53 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/24 21:31:53 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void	nick(CommandArgs cArgs)
{
	if (cArgs.msg.params.size() != 1)
	{
		cArgs.client.sendReplyToClient(ERR_NONICKNAMEGIVEN(), cArgs.client);
		return ;
	}
	if (cArgs.msg.params[0].empty())
	{
		// cArgs.client.incrementRetries(); precisa?
		cArgs.client.sendReplyToClient(ERR_ERRONEUSNICKNAME(cArgs.msg.params[0]), cArgs.client);
		return ;
	}
	for (size_t i = 0; i < cArgs.server.getClients().size(); i++)
	{
		if (cArgs.server.getClients()[i].getNick() == cArgs.msg.params[0])
		{
			// cArgs.client.incrementRetries(); precisa?
			cArgs.client.sendReplyToClient(ERR_NICKNAMEINUSE(cArgs.msg.params[0]), cArgs.client);
		}
	}
	cArgs.client.setNick(cArgs.msg.params[0]);
	if (cArgs.client.isAuthenticated())
		cArgs.client.sendReplyToClient(RPL_WELCOME(cArgs.client.getNick(), cArgs.client.getUser()), cArgs.client);
}
