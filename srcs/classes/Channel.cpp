/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:58:42 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/27 19:09:56 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(void) : _i(false) {}
// Channel::Channel(void) : _i(false), _t(false), _k(false), _o(false) {}

Channel::Channel(std::string &name) : _name(name), _i(false) {}
// Channel::Channel(std::string &name) : _name(name), _i(false), _t(false), _k(false), _o(false) {}

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

std::vector<Client>	Channel::getClients(void) const
{
	return (this->_clients);
}

void	Channel::setClients(std::vector<Client> clients)
{
	this->_clients = clients;
}

std::vector<Client>	Channel::getOperators(void) const
{
	return (this->_operators);
}

void	Channel::addOperator(Client	&client)
{
	this->_operators.push_back(client);
}

size_t	Channel::getUserLimit(void) const
{
	return (this->_userLimit);
}

void	Channel::setUserLimit(size_t limit)
{
	this->_userLimit = limit;
}

bool	Channel::getInviteOnly(void) const
{
	return (this->_i);
}

void	Channel::setInviteOnly(bool action)
{
	this->_i = action;
}

bool	Channel::isClientOnChannel(const Client &client)
{
	std::vector<Client>::iterator	it;
	it = find(this->_clients.begin(), this->_clients.end(), client);
	if (it == this->_clients.end())
		return (false);
	return (true);
}

void	Channel::addClient(Client &client)
{
	this->_clients.push_back(client);
}

std::string	Channel::getChannelUsers(void)
{
	std::string	users;
	for (size_t i = 0; i < this->_clients.size(); i++)
		users += this->_clients[i].getUser() + " ";
	return (users);
}

bool Channel::operator==(const std::string& str)
{
	return (this->_name == str);
}
