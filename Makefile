NAME = ft_malcolm

CC = gcc
CFLAGS = -Wextra -Werror -Wall -I inc -I libft/
LDFLAGS = -L libft/ -lft

NLBFT = ./libft/libft.a
DLBFT = ./libft


FSRC = main \
       parser

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
	@make clean -C $(DLBFT)
	rm -rf /obj/*.o

fclean : clean
	@make fclean -C $(DLBFT)

re : fclean $(NAME)

.PHONY: all clean fclean re 
