<<<<<<< HEAD
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 18:53:42 by jlima-so          #+#    #+#              #
#    Updated: 2025/07/25 15:13:22 by jlima-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJ=		minishell

NAME=		${PROJ}.a

PARSER_DIR=	parse

PARSER=		$(PARSER_DIR)/$(PARSER_DIR).a

EXEC_DIR=	exec

EXEC =		$(EXEC_DIR)/$(EXEC_DIR).a

CC=			cc

AR=			ar rcs

CFLAGS=		-Wall -Wextra -Werror

all: parse_rule $(PROJ) #$(EXEC)

$(PROJ): $(PROJ).c
	$(CC) -lreadline -lncurses $(PROJ).c $(PARSER) $(PARSER_DIR)/jojo_libft.a -o $(PROJ) -lncurses -lreadline
# $(EXEC)

parse_rule:
	$(MAKE) -C $(PARSER_DIR)

#$(EXEC): 
#	 $(MAKE) -C $(EXEC_DIR)

clean:
	rm -f ${OBJ_FILES} ${NAME}
	$(MAKE) -C $(PARSER_DIR) clean
#	$(MAKE) -C $(EXEC_DIR) clean

fclean: clean
	rm -f $(PROJ)
	$(MAKE) -C $(PARSER_DIR) fcleanlocal
#	$(MAKE) -C $(EXEC_DIR) fclean

re: fclean all
	$(MAKE) -C $(PARSER_DIR)
#	$(MAKE) -C $(EXEC_DIR)

.PHONY: re fclean clean all

# so:
=======
NAME        = minishell
PIPEX       = pipex
PIPEX_BONUS = pipex_bonus

PIPEX_DIR   = pipex
LIBFT_DIR   = my_libft

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
LDFLAGS     = -L/usr/local/opt/readline/lib -lreadline
RM          = rm -f

GREEN       = \033[0;32m
BLUE        = \033[0;34m
RESET       = \033[0m

all: $(NAME)

$(NAME):
	@echo -e "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@echo -e "$(BLUE)Building pipex...$(RESET)"
	@$(MAKE) --no-print-directory -C $(PIPEX_DIR)
	@echo -e "$(BLUE)Building minishell...$(RESET)"
	
	@$(CC) $(CFLAGS) executor.c builtin.c signal_handler.c $(PIPEX_DIR)/$(PIPEX).a $(LIBFT_DIR)/libft.a -o $(NAME) $(LDFLAGS)
	
	@echo -e "$(GREEN)Minishell built successfully!$(RESET)"

bonus:
	@echo -e "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@echo -e "$(BLUE)Building pipex (bonus)...$(RESET)"
	@$(MAKE) --no-print-directory -C $(PIPEX_DIR) bonus
	@echo -e "$(BLUE)Building minishell with bonus...$(RESET)"
	@$(CC) $(CFLAGS) executor.c $(PIPEX_DIR)/$(PIPEX_BONUS).a $(LIBFT_DIR)/libft.a -o $(NAME) $(LDFLAGS)
	@echo -e "$(GREEN)Minishell with bonus built successfully!$(RESET)"

clean:
	@echo -e "$(BLUE)Cleaning libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo -e "$(BLUE)Cleaning pipex...$(RESET)"
	@$(MAKE) --no-print-directory -C $(PIPEX_DIR) clean

fclean: clean
	@echo -e "$(BLUE)Full cleaning libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo -e "$(BLUE)Full cleaning pipex...$(RESET)"
	@$(MAKE) --no-print-directory -C $(PIPEX_DIR) fclean
	@$(RM) $(NAME)
	@echo -e "$(GREEN)Everything cleaned!$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
>>>>>>> main
