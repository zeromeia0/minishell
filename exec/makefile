# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/28 15:37:14 by vivaz-ca          #+#    #+#              #
#    Updated: 2025/10/28 16:42:30 by vivaz-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJ        = execution.a
OTHER_SRCS  = exec_pipes_aux.c \
              exec_pipes.c \
              exec_redirections_aux.c \
              exec_redirections.c \
              exec_redirections_tokenization.c \
              exec_tree_aux1.c \
              exec_tree_aux2.c \
              exec_tree.c \
              heredoc.c \
              shadow1.c \
              shadow2.c \
              shadow3.c \
              shadow4.c \
              shadow5.c \
              signal_handler.c \
              super_duper_hiper_free.c \
              zeta.c
BUILTIN_SRCS = builtin/aspas_aux.c \
               builtin/aspas.c \
               builtin/builtin.c \
               builtin/builtin_cd.c \
               builtin/builtin_pwd.c \
               builtin/env_aux1.c \
               builtin/env_aux2.c \
               builtin/env_aux3.c \
               builtin/env_aux4.c \
               builtin/env_aux5.c \
               builtin/env.c \
               builtin/export.c \
               builtin/export_aux.c \
               builtin/overall_builtin_aux.c \
               builtin/unset.c
PATH_SRCS    = exec_path/exec_path_aux1.c \
               exec_path/exec_path_aux2.c \
               exec_path/exec_path_aux3.c \
               exec_path/exec_path_aux4.c \
               exec_path/exec_path.c
ALL_SRCS     = $(OTHER_SRCS) $(BUILTIN_SRCS) $(PATH_SRCS)
OBJS         = $(ALL_SRCS:.c=.o)
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -fsanitize=address
RM          = rm -f
GREEN       = \033[0;32m
BLUE        = \033[0;34m
RESET       = \033[0m

all: $(PROJ)

$(PROJ): $(OBJS)
	@echo -e "$(BLUE)Building execution.a...$(RESET)"
	@ar rcs $(PROJ) $(OBJS)
	@echo -e "$(GREEN)execution.a built successfully!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo -e "$(BLUE)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS)

fclean: clean
	@echo -e "$(BLUE)Cleaning execution.a...$(RESET)"
	@$(RM) $(PROJ)
	@echo -e "$(GREEN)Archive removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
