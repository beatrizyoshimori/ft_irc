/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:58:45 by byoshimo          #+#    #+#             */
/*   Updated: 2024/08/10 19:48:30 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ft_irc.hpp"

class	Channel
{
	private:
		std::string			_name;
		std::string			_topic;
		std::string			_key;
		std::vector<Client>	_clients;
		std::vector<Client>	_operators;
		size_t				_userLimit;

		bool				_i;
		bool				_t;
		// bool				_k;
		// bool				_o;

	public:
		Channel(void);
		Channel(std::string &name);
		~Channel(void) {}
		Channel&	operator=(const Channel &obj);

		std::string			getName(void) const;
		void				setName(std::string name);
		std::string			getTopic(void) const;
		void				setTopic(std::string topic);
		std::string			getKey(void) const;
		void				setKey(std::string key);
		std::vector<Client>	getClients(void) const;
		void				setClients(std::vector<Client> clients);
		std::vector<Client>	getOperators(void) const;
		void				addOperator(Client &client);
		size_t				getUserLimit(void) const;
		void				setUserLimit(size_t limit);
		bool				getInviteOnly(void) const;
		void				setInviteOnly(bool action);
		bool				getTopicOPOnly(void) const;
		void				setTopicOPOnly(bool action);

		bool				isClientOnChannel(const Client &client);
		bool				isOperator(const Client &client);
		void				addClient(Client &client);
		void				removeClient(Client &client);
		std::string			getChannelUsers(void);

		bool operator==(const std::string& str);
};

#endif