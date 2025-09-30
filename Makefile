PROJ=		minishell
NAME=		${PROJ}.a
PARSER_DIR=	parse
PARSER=		$(PARSER_DIR)/$(PARSER_DIR).a
EXEC_DIR=	exec
BIN_DIR=	$(EXEC_DIR)/builtin
EXEC_PATH_DIR=	$(EXEC_DIR)/exec_path
EXEC=			$(wildcard ${EXEC_DIR}/*.c) \
				$(wildcard ${BIN_DIR}/*.c) \
				$(wildcard ${EXEC_PATH_DIR}/*.c)

CC=			cc
AR=			ar rcs
# CFLAGS=		-Wall -Wextra -Werror -g -finstrument-functions
CFLAGS=		-g -finstrument-functions
PIPEX       = pipex
PIPEX_BONUS = pipex_bonus
PIPEX_DIR   = pipex
LIBFT_DIR   = my_libft
BULTIN_DIR  = builtin
BULTIN_SRCS = $(wildcard $(BULTIN_DIR)/*.c)

all: exec_rule parse_rule $(PROJ)

$(PROJ): $(PROJ).c
	$(CC) $(CFLAGS) -lreadline -lncurses $(PROJ).c ${EXEC} $(PARSER) $(PARSER_DIR)/jojo_libft.a $(EXEC_DIR)/$(PIPEX_DIR)/$(PIPEX).a $(EXEC_DIR)/$(LIBFT_DIR)/libft.a -o $(PROJ) -lncurses -lreadline

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

norm:
	@norminette $(shell find . -type f \( -name "*.c" -o -name "*.h" \)) \
	| awk '/c: Error/ { c++; if (c % 2 == 1) printf "\033[1;35m%s\033[0m\n", $$0; else printf "\033[1;36m%s\033[0m\n", $$0 }'
	@echo "Amount of errors: " && norminette $(shell find . -type f \( -name "*.c" -o -name "*.h" \)) | grep "Error" | wc -l

make val: re
	clear
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell


.PHONY: re fclean clean all exec_rule parse_rule

# so:
