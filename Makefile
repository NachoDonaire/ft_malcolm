NAME = ft_malcolm

CC = gcc
CFLAGS = -Wextra -Werror -Wall -I inc -I libft/
LDFLAGS = -L libft/ -lft

NLBFT = ./libft/libft.a
DLBFT = ./libft


FSRC = main		\
       arp_packet	\
       utils		\
       ether_header	\
       log		\
       parser		\
       send_packet

ALLC = $(addsuffix .c, $(FSRC))
SRC = $(addprefix src/, $(ALLC))

ALLOBJ = $(addsuffix .o, $(FSRC))
OBJ = $(addprefix obj/, $(ALLOBJ))

all : $(NAME)

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) :  $(OBJ)
	@make -C $(DLBFT)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(NAME)

clean :
	rm -rf obj/*.o
	@make clean -C $(DLBFT)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)

####### SCENARIO INSTRUCTIONS #######

up:
	docker-compose -f ./docker-compose.yml up --build -d

down:
	docker-compose -f ./docker-compose.yml down

spoofer:
	docker exec -it spoofer /bin/bash

source:
	docker exec -it source /bin/bash

target:
	docker exec -it target /bin/bash

.PHONY: all clean fclean re 
