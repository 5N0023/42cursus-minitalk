NAME =	client \
		server
BONUS = client_bonus \
		server_bonus

CC_FLAGS = -Wall -Wextra -Werror

all: $(NAME)

server.o : server.c
		cc  server.c -c
client.o : client.c
		cc  client.c -c

server : server.o
		cc  server.o helpers.c -o server

client : client.o helpers.c
		cc  client.o helpers.c -o client

server_bonus.o : server_bonus.c
		cc  server_bonus.c -c
client_bonus.o : client_bonus.c
		cc  client_bonus.c -c

server_bonus : server_bonus.o
		cc  server_bonus.o -o server_bonus

client_bonus : client_bonus.o
		cc  client_bonus.o -o client_bonus


bonus : $(BONUS)

clean:
	rm -f server.o client.o
	rm -f server_bonus.o client_bonus.o

fclean: clean
	rm -f $(NAME) $(BONUS)
	

re: fclean all

.PHONY : clean fclean re all