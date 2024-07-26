/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:16:24 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/24 21:16:26 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP

# define FTIRC std::string(":ircserv")
# define CRLF std::string("\r\n")

# define RPL_WELCOME(nick, user)					(FTIRC + " 001 " + user + " :Welcome to the Internet Relay Chat " + nick + "!" + user + "@*" + CRLF)

# define ERR_NONICKNAMEGIVEN()						(FTIRC + " 431 :No nickname given" + CRLF)
# define ERR_ERRONEUSNICKNAME(nick)					(FTIRC + " 432 * " + nick + " :Nickname is invalid" + CRLF)
# define ERR_NICKNAMEINUSE(nick)					(FTIRC + " 433 * " + nick + " :Nickname is already in use" + CRLF)
# define ERR_NEEDMOREPARAMS(command, reason)		(FTIRC + " 461 * " + command + " :" + reason + CRLF)
# define ERR_ALREADYREGISTRED(user)					(FTIRC + " 462 * " + user + ":User already registered)" + CRLF)
# define ERR_PASSWDMISMATCH()						(FTIRC + " 464 * :Password incorrect" + CRLF)

#endif