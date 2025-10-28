# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/28 15:37:14 by vivaz-ca          #+#    #+#              #
#    Updated: 2025/10/28 15:39:44 by vivaz-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell
PIPEX       = pipex
PIPEX_BONUS = pipex_bonus
PIPEX_DIR   = pipex
LIBFT_DIR   = my_libft
BULTIN_DIR  = builtin
BULTIN_SRCS = $(BULTIN_DIR)/aspas_aux.c \
			  $(BULTIN_DIR)/aspas.c \
			  $(BULTIN_DIR)/builtin.c \
			  $(BULTIN_DIR)/builtin_cd.c \
			  $(BULTIN_DIR)/builtin_pwd.c \
			  $(BULTIN_DIR)/env_aux1.c \
			  $(BULTIN_DIR)/env_aux2.c \
			  $(BULTIN_DIR)/env_aux3.c \
			  $(BULTIN_DIR)/env_aux4.c \
			  $(BULTIN_DIR)/env_aux5.c \
			  $(BULTIN_DIR)/env.c \
			  $(BULTIN_DIR)/export.c \
			  $(BULTIN_DIR)/export_aux.c \
			  $(BULTIN_DIR)/overall_builtin_aux.c \
			  $(BULTIN_DIR)/unset.c

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS     = -L/usr/local/opt/readline/lib -lreadline -g
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
#	@$(CC) $(CFLAGS) $(BULTIN_SRCS) ../minishell.c signal_handler.c \
#		$(PIPEX_DIR)/$(PIPEX).a $(LIBFT_DIR)/libft.a -o $(NAME) $(LDFLAGS)
	@echo -e "$(GREEN)Minishell built successfully!$(RESET)"

bonus:
	@echo -e "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@echo -e "$(BLUE)Building pipex (bonus)...$(RESET)"
	@$(MAKE) --no-print-directory -C $(PIPEX_DIR) bonus
	@echo -e "$(BLUE)Building minishell with bonus...$(RESET)"
	@$(CC) $(CFLAGS) $(BULTIN_SRCS) executor.c path_cmd.c \
		$(PIPEX_DIR)/$(PIPEX_BONUS).a $(LIBFT_DIR)/libft.a -o $(NAME) $(LDFLAGS)
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
