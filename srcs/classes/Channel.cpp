/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:58:42 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/19 19:58:44 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

std::string	Channel::getName(void) const
{
	return (this->_name);
}

void	Channel::setName(std::string name)
{
	this->_name = name;
}

std::string	Channel::getTopic(void) const
{
	return (this->_topic);
}

void	Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}

std::string	Channel::getKey(void) const
{
	return (this->_key);
}

void	Channel::setKey(std::string key)
{
	this->_key = key;
}

bool	Channel::isClientOnChannel(const Client &client)
{
    std::vector<Client>::iterator	it;
	it = find(this->_clients.begin(), this->_clients.end(), client);
	if (it == this->_clients.end())
		return (false);
	return (true);
}
