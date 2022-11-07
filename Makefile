.PHONY: all clean fclean re bonus

NAME	=	Cub3D
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
INC		=	include
OBJ		=	objs
SRC		=	sources
LIBMLX 	=	libmlx
INCS	=	$(addprefix $(INC)/, cub3D.h)
OBJS	=	$(addprefix $(OBJ)/, $(SRCS:.c=.o))
SRCS 	=	main.c 

all: bonus $(NAME)

bonus:
	mkdir -p $(OBJ)
	make -C $(LIBMLX)

$(NAME): $(OBJS) $(INCS)
	$(CC) $(FLAGS) -I$(INC) -o $(NAME) $(OBJS) -Llibmlx -lmlx -lX11 -lXext

$(OBJ)/%.o: $(SRC)/%.c $(INCS)
	$(CC) $(FLAGS) -I$(INC) -c $< -o $@

clean:
	rm -rf $(OBJ)
	make -C $(LIBMLX) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all
