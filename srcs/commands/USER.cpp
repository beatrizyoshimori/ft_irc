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

std::string	user(CommandArgs cArgs)
{
	if (cArgs.msg.params.size() != 4)
		return (ERR_NEEDMOREPARAMS(cArgs.msg.command, "Not enough parameters"));
	for (size_t i = 0; i < cArgs.clients.size(); i++)
	{
		if (cArgs.clients[i].getUser() == cArgs.msg.params[0])
		{
			cArgs.clients[i].setRemoveClient(true);
			return (ERR_ALREADYREGISTRED(cArgs.clients[i].getUser()));
		}
	}
	if (cArgs.msg.params[3][0] == ':')
		cArgs.msg.params[3] = cArgs.msg.params[3].substr(1);
	cArgs.client.setUser(cArgs.msg.params[0]);
	cArgs.client.setRealname(cArgs.msg.params[3]);
	// if (cArgs.client.getRetries())
	// 	return(""); precisa?
	if (cArgs.client.isAuthenticated())
		return (RPL_WELCOME(cArgs.client.getNick(), cArgs.client.getUser()));
	return ("");
}
