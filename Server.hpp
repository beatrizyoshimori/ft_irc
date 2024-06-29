#ifndef SERVER_HPP
# define SERVER_HPP

#include "ft_irc.hpp"

class   Server
{
    private:
        int					_serverPort;
        std::string			_serverPassword;
		int					_socketFileDescriptor;
		sockaddr_in			_serverAddress;
		std::vector<pollfd>	_connectionsPollfds;
		std::vector<Client>	_clients;

		void		createSocket(void);
		void		defineServerAddress(void);
		void		bindSocket(void);
		void		listenForConnections(void);
		void		pollActiveConnections(void);
		void		acceptNewClients(void);
		void		processClientsActivity(void);
		bool		detectedActivity(const int &clientFd);

    public:
		Server(void) {};
        ~Server(void) {};

        void    setPort(char *input);
        void	setPassword(char *input);
		void	configureTCP(void);
		void	start(void);
};

#endif