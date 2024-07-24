#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "ft_irc.hpp"

class	Commands
{
	public:
		typedef std::string (*funcPtr)(CommandArgs);

		static void			populateMap(void);
		static std::string	callFunction(CommandArgs &cArgs);

		Commands(void) {}
		~Commands(void) {}

	private:
		static std::map<std::string, funcPtr>	_commands;
};

std::string	user(CommandArgs cArgs);

#endif