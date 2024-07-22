/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:10:36 by byoshimo          #+#    #+#             */
/*   Updated: 2024/06/29 19:10:39 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

# define MAX_PORT 65535
# define TIMEOUT_MS 1000
# define BUFFER_SIZE 512

# define CRLF std::string("\r\n")

#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>

#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <poll.h>

class	Server;
class	Client;

#include "Client.hpp"
#include "Server.hpp"
#include "Message.hpp"
#include "Utils.hpp"

#endif