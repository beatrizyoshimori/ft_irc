#ifndef REPLIES_HPP
# define REPLIES_HPP

# define FTIRC std::string(":ircserv")
# define CRLF std::string("\r\n")

# define RPL_WELCOME(nick, user)					(FTIRC + " 001 " + user + " :Welcome to the Internet Relay Chat " + nick + "!" + user + "@*" + CRLF)

# define ERR_NONICKNAMEGIVEN()						(FTIRC + " 431 :No nickname given" + CRLF)
# define ERR_ERRONEUSNICKNAME(nick)					(FTIRC + " 432 * " + nick + " :Nickname is invalid" + CRLF)
# define ERR_NICKNAMEINUSE(nick)					(FTIRC + " 433 * " + nick + " :Nickname is already in use" + CRLF)


#endif