/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:15:57 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/24 21:15:59 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void	user(CommandArgs cArgs)
{
	if (cArgs.msg.params.size() != 4)
		cArgs.client.sendReplyToClient(ERR_NEEDMOREPARAMS(cArgs.msg.command, "Not enough parameters"), cArgs.client);
	for (size_t i = 0; i < cArgs.server.getClients().size(); i++)
	{
		if (cArgs.server.getClients()[i].getUser() == cArgs.msg.params[0])
		{
			cArgs.server.getClients()[i].setRemoveClient(true);
			cArgs.client.sendReplyToClient(ERR_ALREADYREGISTRED(cArgs.server.getClients()[i].getUser()), cArgs.client);
		}
	}
	if (cArgs.msg.params[3][0] == ':')
		cArgs.msg.params[3] = cArgs.msg.params[3].substr(1);
	cArgs.client.setUser(cArgs.msg.params[0]);
	cArgs.client.setRealname(cArgs.msg.params[3]);
	// if (cArgs.client.getRetries())
	// 	return(""); precisa?
	if (cArgs.client.isAuthenticated())
		cArgs.client.sendReplyToClient(RPL_WELCOME(cArgs.client.getNick(), cArgs.client.getUser()), cArgs.client);
}
