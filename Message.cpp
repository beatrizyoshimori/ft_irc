#include "Message.hpp"

void	Message::parseMessage(std::string line)
{
	if (line.empty())
		throw std::runtime_error("Empty line.");
	if (line[0] == ':')
	{
		this->prefix = line.substr(1, line.find(' ') - 1);
		line = line.substr(line.find(' ') + 1, line.size() - 1);
	}
	this->params = Utils::split(line, " ");
	this->command = params.front();
	this->params.erase(this->params.begin());
	if (params.back().find(':') != std::string::npos)
		params.back().erase(0, 1);

	// // Parse checking
	// std::cout << "prefix:" << this->prefix << std::endl;
	// std::cout << "command:" << this->command << std::endl << "params:";
	// for (std::vector<std::string>::iterator i = this->params.begin(); i != params.end(); i++)
	// 	std::cout << *i << ' ';
	// std::cout << std::endl;
}
