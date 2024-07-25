/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:16:01 by byoshimo          #+#    #+#             */
/*   Updated: 2024/07/24 21:17:50 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

std::vector<std::string> Utils::split(std::string str, std::string delimiter)
{
	std::vector<std::string>	tokens;

	size_t	start = 0;
	size_t	end;
	size_t	del_size = delimiter.size();

	while((end = str.find(delimiter, start)) != std::string::npos)
	{
		tokens.push_back(str.substr(start, end - start));
		start = end + del_size;
		// std::cout << "tokens.back: ." << tokens.back() << "." << std::endl;
	}
	tokens.push_back(str.substr(start));
	tokens.erase(std::remove(tokens.begin(), tokens.end(), ""), tokens.end());
	// std::cout << "tokens.back2: ." << tokens.back() << "." << std::endl;
	return (tokens);
}
