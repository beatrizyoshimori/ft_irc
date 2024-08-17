#include "ft_irc.hpp"

void	invite(CommandArgs cArgs)
{
	if (cArgs.msg.params.size() != 2)
	{
		cArgs.client.sendReplyToClient(ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong number of parameters"), cArgs.client);
		return ;
	}

	std::string	nickName = cArgs.msg.params[0];
	std::string	channelName = cArgs.msg.params[1];
	int			foundPosition = -1;

	for (size_t i = 0; i < cArgs.server.getClients().size(); i++)
	{
		if (cArgs.server.getClients()[i] == nickName)
		{
			foundPosition = i;
			break ;
		}
	}
	if (foundPosition == -1)
	{
		cArgs.client.sendReplyToClient(ERR_NOSUCHNICK(cArgs.client.getNick(), nickName), cArgs.client);
		return ;
	}

	Client	&recipient = cArgs.server.getClients()[foundPosition];
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
	if (itChannel->getInviteOnly() && !itChannel->isOperator(cArgs.client))
	{
		cArgs.client.sendReplyToClient(ERR_CHANOPRIVSNEEDED(channelName), cArgs.client);
		return ;
	}
	if (itChannel->isClientOnChannel(recipient))
	{
		cArgs.client.sendReplyToClient(ERR_USERONCHANNEL(nickName, channelName), cArgs.client);
		return ;
	}
	recipient.sendReplyToClient(RPL_INVITEMSG(cArgs.client.getNick(), cArgs.client.getUser(), nickName, channelName), recipient);
	// if (channel.getIsInviteOnly())
	// 	recipient.addChannelToInvited(channelName);
	cArgs.client.sendReplyToClient(RPL_INVITING(cArgs.client.getNick(), nickName, channelName), cArgs.client);
}
