/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:16:44 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/27 18:55:38 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
std::string	nick(CommandArgs cArgs);
std::string	pass(CommandArgs cArgs);
std::string	quit(CommandArgs cArgs);
std::string	join(CommandArgs cArgs);

#endif