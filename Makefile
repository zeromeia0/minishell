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
BULTIN_DIR  = builtin
BULTIN_SRCS = $(wildcard $(BULTIN_DIR)/*.c)

<<<<<<< HEAD
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
LDFLAGS     = -L/usr/local/opt/readline/lib -lreadline -g
RM          = rm -f
=======
all: exec_rule parse_rule $(PROJ)
>>>>>>> jojo

$(PROJ): $(PROJ).c
	$(CC) -lreadline -lncurses $(PROJ).c ${EXEC} $(PARSER) $(PARSER_DIR)/jojo_libft.a $(PIPEX_DIR)/$(PIPEX).a $(LIBFT_DIR)/libft.a -o $(PROJ) -lncurses -lreadline

parse_rule:
	$(MAKE) -C $(PARSER_DIR)

<<<<<<< HEAD
$(NAME):
	@echo -e "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@echo -e "$(BLUE)Building pipex...$(RESET)"
	@$(MAKE) --no-print-directory -C $(PIPEX_DIR)
	@echo -e "$(BLUE)Building minishell...$(RESET)"
	@$(CC) $(CFLAGS) $(BULTIN_SRCS) executor.c signal_handler.c \
		$(PIPEX_DIR)/$(PIPEX).a $(LIBFT_DIR)/libft.a -o $(NAME) $(LDFLAGS)
	@echo -e "$(GREEN)Minishell built successfully!$(RESET)"

bonus:
	@echo -e "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@echo -e "$(BLUE)Building pipex (bonus)...$(RESET)"
	@$(MAKE) --no-print-directory -C $(PIPEX_DIR) bonus
	@echo -e "$(BLUE)Building minishell with bonus...$(RESET)"
	@$(CC) $(CFLAGS) $(BULTIN_SRCS) executor.c \
		$(PIPEX_DIR)/$(PIPEX_BONUS).a $(LIBFT_DIR)/libft.a -o $(NAME) $(LDFLAGS)
	@echo -e "$(GREEN)Minishell with bonus built successfully!$(RESET)"
=======
exec_rule: 
	$(MAKE) -C $(EXEC_DIR)
>>>>>>> jojo

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

<<<<<<< HEAD
.PHONY: all bonus clean fclean re
=======
.PHONY: re fclean clean all

# so:
>>>>>>> jojo
