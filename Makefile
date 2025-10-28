# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 15:40:32 by vivaz-ca          #+#    #+#              #
#    Updated: 2025/10/28 17:20:06 by vivaz-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OTHER_SRCS  =	exec/exec_pipes_aux.c \
            	exec/exec_pipes.c \
            	exec/exec_redirections_aux.c \
            	exec/exec_redirections.c \
            	exec/exec_redirections_tokenization.c \
            	exec/exec_tree_aux1.c \
            	exec/exec_tree_aux2.c \
            	exec/exec_tree.c \
            	exec/heredoc.c \
            	exec/shadow1.c \
            	exec/shadow2.c \
            	exec/shadow3.c \
            	exec/shadow4.c \
            	exec/shadow5.c \
            	exec/signal_handler.c \
            	exec/super_duper_hiper_free.c \
            	exec/zeta.c
BUILTIN_SRCS =	exec/builtin/aspas_aux.c \
            	exec/builtin/aspas.c \
            	exec/builtin/builtin.c \
            	exec/builtin/builtin_cd.c \
            	exec/builtin/builtin_pwd.c \
            	exec/builtin/env_aux1.c \
            	exec/builtin/env_aux2.c \
            	exec/builtin/env_aux3.c \
            	exec/builtin/env_aux4.c \
            	exec/builtin/env_aux5.c \
            	exec/builtin/env.c \
            	exec/builtin/export.c \
            	exec/builtin/export_aux.c \
            	exec/builtin/overall_builtin_aux.c \
            	exec/builtin/unset.c
PATH_SRCS    =	exec/exec_path/exec_path_aux1.c \
            	exec/exec_path/exec_path_aux2.c \
            	exec/exec_path/exec_path_aux3.c \
            	exec/exec_path/exec_path_aux4.c \
            	exec/exec_path/exec_path.c

ALL_SRCS     = $(OTHER_SRCS) $(BUILTIN_SRCS) $(PATH_SRCS)

PROJ=		minishell
NAME=		${PROJ}.a
PARSER_DIR=	parse
PARSER=		$(PARSER_DIR)/$(PARSER_DIR).a
EXEC_DIR=	exec
BIN_DIR=	$(EXEC_DIR)/builtin
EXEC_PATH_DIR=	$(EXEC_DIR)/exec_path
# EXEC=			$(wildcard ${EXEC_DIR}/*.c) \
# 				$(wildcard ${BIN_DIR}/*.c) \
# 				$(wildcard ${EXEC_PATH_DIR}/*.c)
EXEC=			exec/execution.a

CC=			cc
AR=			ar rcs
CFLAGS=		-Wall -Wextra -Werror -g -finstrument-functions
PIPEX       = pipex
PIPEX_BONUS = pipex_bonus
PIPEX_DIR   = pipex
LIBFT_DIR   = my_libft
BULTIN_DIR  = builtin



all: exec_rule parse_rule $(PROJ)

$(PROJ): $(PROJ).c
	$(CC) $(CFLAGS) -lreadline -lncurses $(PROJ).c ${ALL_SRCS} $(PARSER) $(PARSER_DIR)/jojo_libft.a $(EXEC_DIR)/$(LIBFT_DIR)/libft.a -o $(PROJ) -lncurses -lreadline

parse_rule:
	$(MAKE) -C $(PARSER_DIR)

exec_rule:
	$(MAKE) -C $(EXEC_DIR)
clean:
	rm -f ${OBJ_FILES} ${NAME}
	$(MAKE) -C $(PARSER_DIR) clean
	$(MAKE) -C $(EXEC_DIR) clean

fclean: clean
	rm -f $(PROJ)
	$(MAKE) -C $(PARSER_DIR) fcleanlocal
	$(MAKE) -C $(EXEC_DIR) fclean

re: fclean all
	$(MAKE) -C $(PARSER_DIR)
	$(MAKE) -C $(EXEC_DIR)

r: fclean all
	$(MAKE) -C $(PARSER_DIR)
	$(MAKE) -C $(EXEC_DIR)
	make clean
	clear && ./minishell

rr:
	rm -fr ${OBJ_FILES} ${NAME}
	rm -fr $(PROJ)
	make

norm:
	@norminette $(shell find . -type f \( -name "*.c" -o -name "*.h" \)) \
	| awk '/c: Error/ { c++; if (c % 2 == 1) printf "\033[1;35m%s\033[0m\n", $$0; else printf "\033[1;36m%s\033[0m\n", $$0 }'
	@echo "Amount of errors: " && norminette $(shell find . -type f \( -name "*.c" -o -name "*.h" \)) | grep "Error" | wc -l

val: re
	clear
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

cal1:
	clear
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

cal2:
	clear
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --suppressions=readline.supp ./minishell

.PHONY: re fclean clean all exec_rule parse_rule

# so:
