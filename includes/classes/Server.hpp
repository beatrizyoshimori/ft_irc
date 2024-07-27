/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:10:30 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/27 18:18:47 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "ft_irc.hpp"

class	Server
{
	private:
		int						_serverPort;
		std::string				_serverPassword;
		int						_socketFileDescriptor;
		sockaddr_in				_serverAddress;
		std::vector<pollfd>		_connectionsPollfds;
		std::vector<Client>		_clients;
		std::vector<Channel>	_channels;

		void		createSocket(void);
		void		defineServerAddress(void);
		void		bindSocket(void);
		void		listenForConnections(void);
		void		pollActiveConnections(void);
		void		acceptNewClients(void);
		void		processClientsActivity(void);
		bool		detectedActivity(const int &clientFd);

	public:
		Server(void) {};
		~Server(void) {};

		void	setPort(char *input);
		void	setPassword(char *input);
		void	configureTCP(void);
		void	start(void);

		std::string				getServerPassword(void) const;
		std::vector<Client>		getClients(void) const;
		std::vector<Channel>	getChannels(void) const;
		void					addChannel(Channel &channel);
};

#endif