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

	std::string					modes = cArgs.msg.params[1];
	std::vector<std::string>	modesParams(cArgs.msg.params.begin() + 2, cArgs.msg.params.end());
	bool						action = true;
	for (size_t i = 0; modes.size(); i++)
	{
		if (modes[i] == '+')
			action = true;
		else if (modes[i] == '-')
			action = false;
		else if (modes[i] == 'i')
			itChannel->setInviteOnly(action);
		else if (modes[i] == 't')
			itChannel->setTopicOPOnly(action);
		else if (modes[i] == 'k')
		{
			if (action && !modesParams.empty())
				itChannel->setKey(modesParams[0]);
			else if (modesParams.empty())
				cArgs.client.sendReplyToClient(ERR_SETKEY(channelName), cArgs.client); //retirar o k da resposta?
			else
				itChannel->removeKey();
		}
	}
}
