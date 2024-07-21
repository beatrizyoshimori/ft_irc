/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:10:12 by byoshimo          #+#    #+#             */
/*   Updated: 2024/06/29 19:10:14 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "ft_irc.hpp"

class	Client
{
	private:
		int			_fd;
		bool		_removeClient;
		std::string	_data;
		std::string	_nick;
		std::string	_user;
		std::string	_pass;

		std::queue<std::string>	_commandsQueue;

	public:
		Client(void);
		Client(int socketDescriptor);
		~Client(void) {};

		int						getFd(void) const;
		void					setRemoveClient(bool state);
		std::queue<std::string>	getCommandsQueue(void) const;
		std::string				getNick(void) const;
		std::string				getUser(void) const;
		std::string				getPass(void) const;

		bool					isAuthenticated() const;

		void	receiveData(void);
		void	pushToCommandQueue(void);
};

#endif