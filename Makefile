# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssicard <ssicard@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/20 16:17:18 by ssicard           #+#    #+#              #
#    Updated: 2016/05/07 11:26:36 by ssicard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = ft_sh1.a

INC_DIR = includes

CC = gcc

CFLAGS = -I$(INC_DIR)

SOURCES = struct.c\
		  builtins.c\
		  builtins2.c\
		  cd_pwd.c\
		  var_env.c\
		  tools.c

SRC = $(addprefix sources/,$(SOURCES))

OBJ = $(SRC:.c=.o)

all : $(NAME) $(LIB)

$(NAME) : $(LIB)
	@$(CC) -lreadline -o $(NAME) main.c $(LIB) $(CFLAGS) libft/libft.a libft/libftprintf.a
	@echo "MiniOns Arrived!"
	@echo "A New Challenger!"

$(LIB) : $(OBJ)
	@ar -r $(LIB) $(OBJ)
	@ranlib $(LIB)
	@echo "Cpt. ft_sh1 Lib. Arrived."

clean :
	@rm -rf $(OBJ)
	@echo "MiniOns Died!"

fclean : clean
	@rm -rf $(NAME) $(LIB)
	@echo "All's Destroyed! R.I.P :'("

re : fclean all
	@echo "And The Rain Against! ^^"

.PHONY: all clean fclean re
