# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/28 15:37:14 by vivaz-ca          #+#    #+#              #
#    Updated: 2025/10/28 16:31:56 by vivaz-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell
PROJ        = execution.a
PIPEX       = pipex
PIPEX_BONUS = pipex_bonus
PIPEX_DIR   = pipex
LIBFT_DIR   = my_libft
BUILTIN_DIR = builtin
PATH_DIR    = exec_path

BUILTIN_SRCS = $(BUILTIN_DIR)/aspas_aux.c \
               $(BUILTIN_DIR)/aspas.c \
               $(BUILTIN_DIR)/builtin.c \
               $(BUILTIN_DIR)/builtin_cd.c \
               $(BUILTIN_DIR)/builtin_pwd.c \
               $(BUILTIN_DIR)/env_aux1.c \
               $(BUILTIN_DIR)/env_aux2.c \
               $(BUILTIN_DIR)/env_aux3.c \
               $(BUILTIN_DIR)/env_aux4.c \
               $(BUILTIN_DIR)/env_aux5.c \
               $(BUILTIN_DIR)/env.c \
               $(BUILTIN_DIR)/export.c \
               $(BUILTIN_DIR)/export_aux.c \
               $(BUILTIN_DIR)/overall_builtin_aux.c \
               $(BUILTIN_DIR)/unset.c

PATH_SRCS   = $(PATH_DIR)/exec_path_aux1.c \
              $(PATH_DIR)/exec_path_aux2.c \
              $(PATH_DIR)/exec_path_aux3.c \
              $(PATH_DIR)/exec_path_aux4.c \
              $(PATH_DIR)/exec_path.c

OTHER_SRCS  = exec_pipes_aux.c exec_pipes.c exec_redirections_aux.c exec_redirections.c \
              exec_redirections_tokenization.c exec_tree_aux1.c exec_tree_aux2.c exec_tree.c \
              heredoc.c shadow1.c shadow2.c shadow3.c shadow4.c shadow5.c signal_handler.c \
              super_duper_hiper_free.c zeta.c executor.c path_cmd.c

OBJS        = $(OTHER_SRCS:.c=.o)
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS     = -L/usr/local/opt/readline/lib -lreadline -g
RM          = rm -f

GREEN       = \033[0;32m
BLUE        = \033[0;34m
RESET       = \033[0m


all: $(PROJ)

$(PROJ): $(OBJS)
	@echo -e "$(BLUE)Building execution.a...$(RESET)"
	@ar rcs $(PROJ) $(OBJS)
	@echo -e "$(GREEN)execution.a built successfully!$(RESET)"

$(NAME): $(PROJ)
	@echo -e "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@echo -e "$(BLUE)Building pipex...$(RESET)"
	@$(MAKE) --no-print-directory -C $(PIPEX_DIR)
	@echo -e "$(BLUE)Linking minishell...$(RESET)"
	@$(CC) $(CFLAGS) $(BUILTIN_SRCS) $(PATH_SRCS) $(PROJ) \
		$(PIPEX_DIR)/$(PIPEX).a $(LIBFT_DIR)/libft.a -o $(NAME) $(LDFLAGS)
	@echo -e "$(GREEN)Minishell built successfully!$(RESET)"

bonus: $(PROJ)
	@echo -e "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@echo -e "$(BLUE)Building pipex (bonus)...$(RESET)"
	@$(MAKE) --no-print-directory -C $(PIPEX_DIR) bonus
	@echo -e "$(BLUE)Linking minishell with bonus...$(RESET)"
	@$(CC) $(CFLAGS) $(BUILTIN_SRCS) $(PATH_SRCS) $(PROJ) \
		$(PIPEX_DIR)/$(PIPEX_BONUS).a $(LIBFT_DIR)/libft.a -o $(NAME) $(LDFLAGS)
	@echo -e "$(GREEN)Minishell with bonus built successfully!$(RESET)"

clean:
	@echo -e "$(BLUE)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS)
	@echo -e "$(BLUE)Cleaning libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo -e "$(BLUE)Cleaning pipex...$(RESET)"
	@$(MAKE) --no-print-directory -C $(PIPEX_DIR) clean

fclean: clean
	@echo -e "$(BLUE)Full cleaning libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo -e "$(BLUE)Full cleaning pipex...$(RESET)"
	@$(MAKE) --no-print-directory -C $(PIPEX_DIR) fclean
	@$(RM) $(NAME) $(PROJ)
	@echo -e "$(GREEN)Everything cleaned!$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
