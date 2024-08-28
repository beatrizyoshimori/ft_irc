#include "ft_irc.hpp"
#include <utility>

void	mode(CommandArgs cArgs)
{
	if (cArgs.msg.params.size() < 1)
	{
		cArgs.client.sendReplyToClient(ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong number of parameters"), cArgs.client);
		return ;
	}

	std::string	channelName = cArgs.msg.params[0];
	std::vector<Channel>::iterator	itChannel = find(cArgs.server.getChannels().begin(), cArgs.server.getChannels().end(), channelName);
	if (itChannel == cArgs.server.getChannels().end())
	{
		cArgs.client.sendReplyToClient(ERR_NOSUCHCHANNEL(channelName), cArgs.client);
		return ;
	}
	if (!itChannel->isClientOnChannel(cArgs.client))
	{
		cArgs.client.sendReplyToClient(ERR_NOTONCHANNEL(channelName), cArgs.client);
		return ;
	}
	if (cArgs.msg.params.size() == 1)
	{
		cArgs.client.sendReplyToClient(RPL_CHANNELMODEIS(cArgs.client.getNick(), channelName, itChannel->getModes()), cArgs.client);
		return ;
	}
	if (!itChannel->isOperator(cArgs.client))
	{
		cArgs.client.sendReplyToClient(ERR_CHANOPRIVSNEEDED(channelName), cArgs.client);
		return ;
	}

	std::map<
	std::vector<std::string>	modes;
	std::vector<std::string>	modesParams;
	for (size_t i = 1; i < cArgs.msg.params.size(); i++)
	{
		if (cArgs.msg.params[i][0] == '+' || cArgs.msg.params[i][0] == '-')
			modes.push_back(cArgs.msg.params[i]);
		else
	}
}
