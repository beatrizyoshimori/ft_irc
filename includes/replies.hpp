/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:16:24 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/27 19:56:06 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP

# define FTIRC std::string(":ircserv")
# define CRLF std::string("\r\n")

# define RPL_WELCOME(nick, user)					(FTIRC + " 001 " + user + " :Welcome to the Internet Relay Chat " + nick + "!" + user + "@*" + CRLF)
# define RPL_TOPIC(nick, channel, topic)			(FTIRC + " 332 " + nick + " " + channel + " :" + topic + CRLF)
# define RPL_NAMREPLY(nick, channel, names)			(FTIRC + " 353 " + nick + " = " + channel + " :" + names + CRLF)
# define RPL_ENDOFNAMES(nick, channel)				(FTIRC + " 366 " + nick + " " + channel + " :End of NAMES list" + CRLF)

# define ERR_NOSUCHCHANNEL(channel)					(FTIRC + " 403 * " + channel + ":No such channel" + CRLF)
# define ERR_NONICKNAMEGIVEN()						(FTIRC + " 431 :No nickname given" + CRLF)
# define ERR_ERRONEUSNICKNAME(nick)					(FTIRC + " 432 * " + nick + " :Nickname is invalid" + CRLF)
# define ERR_NICKNAMEINUSE(nick)					(FTIRC + " 433 * " + nick + " :Nickname is already in use" + CRLF)
# define ERR_NOTONCHANNEL(channel)					(FTIRC + " 442 * " + channel + " :Client not on channel" + CRLF)
# define ERR_NEEDMOREPARAMS(command, reason)		(FTIRC + " 461 * " + command + " :" + reason + CRLF)
# define ERR_ALREADYREGISTRED(user)					(FTIRC + " 462 * " + user + ":User already registered" + CRLF)
# define ERR_PASSWDMISMATCH()						(FTIRC + " 464 * :Password incorrect" + CRLF)
# define ERR_CHANNELISFULL(channel)					(FTIRC + " 471 * " + channel + ":Cannot join channel (Channel is full)" + CRLF)
# define ERR_INVITEONLYCHAN(channel)				(FTIRC + " 473 * " + channel + ":Cannot join channel (Invite only channel)" + CRLF)
# define ERR_BADCHANNELKEY(channel)					(FTIRC + " 475 * " + channel + ":Cannot join channel (Incorrect password)" + CRLF)

# define JOIN(nick, user, channel)					(":" + nick + "!" + user + "@* JOIN " + channel + CRLF)
# define QUIT(nick, user)							(":" + nick + "!" + user + "@* QUIT : User has quit IRC" + CRLF)
# define PART(nick, user, channel, message)			(":" + nick + "!" + user + "@* PART :" + channel + " :" + message + CRLF)

#endif