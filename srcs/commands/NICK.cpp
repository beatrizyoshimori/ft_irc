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

std::string	nick(CommandArgs	cArgs)
{
	if (cArgs.msg.params.size() != 1)
		return (ERR_NONICKNAMEGIVEN());
	if (cArgs.msg.params[0].empty())
	{
		// cArgs.client.incrementRetries(); precisa?
		return (ERR_ERRONEUSNICKNAME(cArgs.msg.params[0]));
	}
	for (size_t i = 0; i < cArgs.clients.size(); i++)
	{
		if (cArgs.clients[i].getNick() == cArgs.msg.params[0])
		{
			// cArgs.client.incrementRetries(); precisa?
			return (ERR_NICKNAMEINUSE(cArgs.msg.params[0]));
		}
	}
	cArgs.client.setNick(cArgs.msg.params[0]);
	if (cArgs.client.isAuthenticated())
		return (RPL_WELCOME(cArgs.client.getNick(), cArgs.client.getUser()));
	return ("");
}
