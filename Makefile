.PHONY: all clean fclean re bonus

NAME	=	Cub3D
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror -g
INC		=	include
OBJ		=	objs
SRC		=	sources
LIBFT	=	libft
LIBMLX 	=	libmlx
INCS	=	$(addprefix $(INC)/, cub3D.h)
OBJS	=	$(addprefix $(OBJ)/, $(SRCS:.c=.o))
SRCS 	=	main.c \
			free.c \
			init.c \
			parsing_map.c

all: bonus $(NAME)

bonus:
	mkdir -p $(OBJ)
	make -C $(LIBMLX)

$(NAME): $(OBJS) $(INCS)
	make -C $(LIBFT)
	$(CC) $(FLAGS) -I$(INC) -o $(NAME) $(OBJS) -Llibmlx -lmlx -lX11 -lXext -lm libft/libft.a

$(OBJ)/%.o: $(SRC)/%.c $(INCS)
	$(CC) $(FLAGS) -I$(INC) -c $< -o $@

clean:
	rm -rf $(OBJ)
	make -C $(LIBFT) clean
	make -C $(LIBMLX) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all
