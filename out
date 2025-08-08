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