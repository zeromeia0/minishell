PROJ=		minishell

NAME=		${PROJ}.a

PARSER_DIR=	parse

PARSER=		$(PARSER_DIR)/$(PARSER_DIR).a

EXEC_DIR=	exec

EXEC=		$(wildcard ${EXEC_DIR}/*.c)

CC=			cc

AR=			ar rcs

CFLAGS=		-Wall -Wextra -Werror

PIPEX       = pipex
PIPEX_BONUS = pipex_bonus

PIPEX_DIR   = pipex
LIBFT_DIR   = my_libft

all: exec_rule parse_rule $(PROJ)

$(PROJ): $(PROJ).c
	$(CC) -lreadline -lncurses $(PROJ).c ${EXEC} $(PARSER) $(PARSER_DIR)/jojo_libft.a $(PIPEX_DIR)/$(PIPEX).a $(LIBFT_DIR)/libft.a -o $(PROJ) -lncurses -lreadline

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

.PHONY: re fclean clean all



# so:
