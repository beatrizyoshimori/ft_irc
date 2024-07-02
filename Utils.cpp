#include "Utils.hpp"

std::vector<std::string> Utils::split(std::string str, std::string delimeter)
{
	std::vector<std::string>	tokens;

	size_t	start = 0;
	size_t	end;
	size_t	del_size = delimeter.size();

	while((end = str.find(delimeter, start)) != std::string::npos)
	{
		tokens.push_back(str.substr(start, end - start));
		start = end + del_size;
	}
	tokens.push_back(str.substr(start));
	tokens.erase(std::remove(tokens.begin(), tokens.end(), ""), tokens.end());
	return (tokens);
}
