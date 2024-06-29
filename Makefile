NAME			=		ircserv

CC				=		c++ -g3
FLAGS			=		-Wall -Wextra -Werror -std=c++98
RM				=		rm -rf

OBJECTS_PATH	=		objects/

SOURCES			=		main.cpp \
						Server.cpp \
						Client.cpp

HEADERS			=		ft_irc.hpp \
						Server.hpp \
						Client.hpp

OBJECTS			=		$(patsubst %.cpp, $(OBJECTS_PATH)%.o, $(SOURCES))

all:					$(NAME)

$(OBJECTS_PATH)%.o:		%.cpp $(HEADERS)
						@mkdir -p $(dir $@)
						@$(CC) $(FLAGS) -c $< -o $@

$(NAME):				$(OBJECTS)
						@$(CC) $(FLAGS) $(OBJECTS) -o $@
						@echo "\033[32mircserv compiled!\033[0m"

clean:
						@$(RM) $(OBJECTS_PATH)

fclean:					clean
						@$(RM) $(NAME)

re:						fclean all

.PHONY:					all bonus clean fclean re