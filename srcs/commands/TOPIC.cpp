#include "ft_irc.hpp"

void	topic(CommandArgs cArgs)
{
	if (cArgs.msg.params.size() < 1 || cArgs.msg.params.size() > 3)
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
		if (itChannel->getTopic().empty())
			cArgs.client.sendReplyToClient(RPL_NOTOPIC(cArgs.client.getNick(), channelName), cArgs.client);
		else
			cArgs.client.sendReplyToClient(RPL_TOPIC(cArgs.client.getNick(), channelName, itChannel->getTopic()), cArgs.client);
		return ;
	}
	if (itChannel->getTopicOPOnly() && !itChannel->isOperator(cArgs.client))
	{
		cArgs.client.sendReplyToClient(ERR_CHANOPRIVSNEEDED(channelName), cArgs.client);
		return ;
	}
	itChannel->setTopic(cArgs.msg.params[1]);
	cArgs.client.sendReplyToBroadcastList(TOPICMSG(cArgs.client.getNick(), cArgs.client.getUser(), channelName, cArgs.msg.params[1]), itChannel->getClients());
}
