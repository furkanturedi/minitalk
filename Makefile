NAME = minitalk
CC = cc
CFLAGS = -Wall -Wextra -Werror
CLIENT = client
SERVER = server
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

CLIENT_SRCS = client.c
SERVER_SRCS = server.c
CLIENT_BONUS_SRCS = client_bonus.c
SERVER_BONUS_SRCS = server_bonus.c

CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_BONUS_OBJS = $(CLIENT_BONUS_SRCS:.c=.o)
SERVER_BONUS_OBJS = $(SERVER_BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJS)

$(SERVER): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS): $(CLIENT_BONUS_OBJS)
	$(CC) $(CFLAGS) -o $(CLIENT_BONUS) $(CLIENT_BONUS_OBJS)

$(SERVER_BONUS): $(SERVER_BONUS_OBJS)
	$(CC) $(CFLAGS) -o $(SERVER_BONUS) $(SERVER_BONUS_OBJS)

clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS) $(CLIENT_BONUS_OBJS) $(SERVER_BONUS_OBJS)

fclean: clean
	rm -f $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
