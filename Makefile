# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sko <marvin@42.fr>                         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/04 16:15:27 by sko               #+#    #+#              #
#    Updated: 2019/10/04 16:15:31 by sko              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC_PATH = srcs/
SRCS = *.c

SRC = $(addprefix $(SRC_PATH), $(SRCS))

MLX = minilibx_macos/
FT = libft/
LIBMLX = libmlx.a
LIBFT = libft.a
HEAD = ./includes
OBJ = *.o
FLAG = -Wextra -Werror -Wall
DEL = rm -rf

all: $(NAME)

$(NAME):
	@make -C $(MLX)
	@make -C $(FT)
	@gcc $(FLAG) -o $(NAME) $(SRC) -I $(HEAD) -I $(FT) -I $(MLX) -L. $(FT)$(LIBFT) -L $(MLX) -lmlx -framework OpenGL -framework Appkit -g
	@echo "[=================]"
	@echo "|     success !   |"
	@echo "|     libmlx.a    |"
	@echo "|   was summoned  |"
	@echo "[=================]"

clean:
	@$(DEL) $(OBJ)
	@make -C $(MLX) clean
	@make -C $(FT) clean
	@echo "[=================]"
	@echo "|     succes !    |"
	@echo "|     XXXXX.o     |"
	@echo "|  was destroyed  |"
	@echo "[=================]"

fclean:	clean
	@$(DEL) $(NAME)
	@$(DEL) fractol.dSYM
	@make -C $(FT) fclean
	@echo "[=================]"
	@echo "|     succes !    |"
	@echo "|     libmlx.a    |"
	@echo "|  was destroyed  |"
	@echo "[=================]"

re: fclean all

debug:
	gcc -g -o $(NAME) $(SRC) -I $(HEAD)
