NAME =	client \
		server


CC_FLAGS = -Wall -Wextra -Werror

all: $(NAME)

server.o : server.c
		cc  server.c -c
client.o : client.c
		cc  client.c -c

server : server.o
		cc  server.o -o server

client : client.o
		cc  client.o -o client

clean:
	rm -f server.o client.o

fclean: clean
	rm -f $(NAME)
	

re: fclean all

.PHONY : clean fclean re all