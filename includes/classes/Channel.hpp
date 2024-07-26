/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:58:45 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/19 20:03:23 by byoshimo         ###   ########.fr       */
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

	public:
		Channel(void) {}
		~Channel(void) {}

		std::string	getName(void) const;
		void		setName(std::string name);
		std::string	getTopic(void) const;
		void		setTopic(std::string topic);
		std::string	getKey(void) const;
		void		setKey(std::string key);

		bool 		isClientOnChannel(const Client &client);
};

#endif