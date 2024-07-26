/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandArgs.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:16:50 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/24 21:16:51 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_ARGS_HPP
# define COMMAND_ARGS_HPP

#include "ft_irc.hpp"

class	CommandArgs
{
	public:
		Client					&client;
		Message					&msg;
		Server					&server;
		std::vector<Client>		&broadcastList;

		CommandArgs(Client &client, Message &msg, Server &server, std::vector<Client> &broadcastList) \
			: client(client), msg(msg), server(server), broadcastList(broadcastList) {}
		~CommandArgs(void) {}
};

#endif