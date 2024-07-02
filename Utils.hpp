#ifndef UTILS_HPP
# define UTILS_HPP

#include "ft_irc.hpp"

class	Utils
{
	public:
		Utils(void);
		~Utils(void);

		static std::vector<std::string>	split(std::string str, std::string delimeter);
};

#endif