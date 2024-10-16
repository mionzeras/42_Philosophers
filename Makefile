# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 18:12:41 by gcampos-          #+#    #+#              #
#    Updated: 2024/10/16 14:49:48 by gcampos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Setup
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I includes -pthread
SRC = srcs/checker.c srcs/init.c srcs/main.c srcs/parsing.c \
srcs/routine.c srcs/utils.c

# Regras
OBJ = $(SRC:.c=.o)
MAKE = make -s
RM = rm -f

# Colors
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
RESET = \033[0m

# Regra genérica para compilar .c em .o
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Regra principal para compilar o programa final
all: $(NAME)

# Compilação do executável a partir dos objetos
$(NAME): $(OBJ)
	@echo "$(CYAN)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(MAGENTA)$(NAME) compiled!$(RESET)"

# Limpeza dos arquivos .o e do executável
clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@$(RM) $(OBJ)

fclean: clean
	@echo "$(YELLOW)Cleaning executable...$(RESET)"
	@$(RM) $(NAME)

re: fclean all

# Declaração de dependências adicionais
.PHONY: all clean fclean re
