/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:58:42 by byoshimo          #+#    #+#             */
/*   Updated: 2024/08/10 19:49:36 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(void) : _i(false), _t(false) {}
// Channel::Channel(void) : _i(false), _t(false), _k(false), _o(false) {}

Channel::Channel(std::string &name) : _name(name), _i(false), _t(false) {}
// Channel::Channel(std::string &name) : _name(name), _i(false), _t(false), _k(false), _o(false) {}

Channel&	Channel::operator=(const Channel &obj)
{
	if (this != &obj)
	{
		this->_name = obj._name;
		this->_topic = obj._topic;
		this->_key = obj._key;
		this->_clients = obj._clients;
		this->_operators = obj._operators;
		this->_userLimit = obj._userLimit;
		this->_i = obj._i;
		// this->_t = obj._t;
		// this->_k = obj._k;
		// this->_o = obj._o;
	}
	return (*this);
}

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

bool	Channel::getTopicOPOnly(void) const
{
	return (this->_t);
}

void	Channel::setTopicOPOnly(bool action)
{
	this->_t = action;
}

bool	Channel::isClientOnChannel(const Client &client)
{
	std::vector<Client>::iterator	it;
	it = find(this->_clients.begin(), this->_clients.end(), client);
	if (it == this->_clients.end())
		return (false);
	return (true);
}

bool	Channel::isOperator(const Client &client)
{
	std::vector<Client>::iterator	it;
	it = find(this->_operators.begin(), this->_operators.end(), client);
	if (it == this->_operators.end())
		return (false);
	return (true);
}

void	Channel::addClient(Client &client)
{
	this->_clients.push_back(client);
}

void	Channel::removeClient(Client &client)
{
	std::vector<Client>::iterator	itClient = find(this->_clients.begin(), this->_clients.end(), client);
	std::vector<Client>::iterator	itOperator = find(this->_operators.begin(), this->_operators.end(), client);

	if (itClient != this->_clients.end())
		this->_clients.erase(itClient);
	if (itOperator != this->_operators.end())
		this->_operators.erase(itOperator);
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
