# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 16:49:59 by mlektaib          #+#    #+#              #
#    Updated: 2023/01/17 19:31:04 by mlektaib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	client \
		server
BONUS = client_bonus \
		server_bonus

SRCS =	server.c	\
		helpers.c	

SRCC =	client.c	\
		helpers.c	

SRCBS =	server_bonus.c	\
		helpers.c	

SRCBC =	client_bonus.c	\
		helpers.c	
		
CC_FLAGS = -Wall -Wextra -Werror

%.o : %.c minitalk.h
	@cc $(CC_FLAGS) -c $< -o $@

OBJSS = $(SRCS:.c=.o)
OBJSC = $(SRCC:.c=.o)

OBJSBS = $(SRCBS:.c=.o)
OBJSBC = $(SRCBC:.c=.o)

$(NAME): $(OBJSS) $(OBJSC)
	@cc  $(OBJSS) -o server
	@cc  $(OBJSC) -o client

$(BONUS): $(OBJSBS) $(OBJSBC)
	@cc  $(OBJSBS) -o server_bonus
	@cc  $(OBJSBC) -o client_bonus

all : $(NAME) $(BONUS)

bonus : $(BONUS)

clean:
	@rm -f $(OBJSBS) $(OBJSBC) $(OBJSS) $(OBJSC)

fclean: clean
	@rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY : clean fclean re all