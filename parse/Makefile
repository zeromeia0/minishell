# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/12 13:07:24 by jlima-so          #+#    #+#              #
#    Updated: 2025/10/28 16:06:55 by jlima-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES=	binary_tree.c check_syntax.c expansions_aux.c expansions.c get_pattern.c \
			here_doc_aux.c parsing.c struct_clear.c struct_new.c syntax_error_msg.c \
			tokenization.c wildcards1.c wildcards2.c wildcards_aux1.c wildcards_aux2.c

OBJ_FILES=	${SRC_FILES:.c=.o}

LIBFT_DIR=	jojo_libft

LIBFT=		jojo_libft.a

NAME=		parse.a

CC=			cc

AR=			ar rcs

CFLAGS=		-Wall -Wextra -Werror -g

all: lib ${NAME}

${NAME}: ${OBJ_FILES}
	${AR} ${NAME} $?

lib:
	$(MAKE) -C $(LIBFT_DIR)

%o: %c
	${CC} ${CFLAGS} $@ $<

clean:
	rm -f ${OBJ_FILES} ${NAME} ${LIBFT}
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f ${NAME} ${LIBFT}
	$(MAKE) -C $(LIBFT_DIR) fclean

fcleanlocal:
	rm -f ${NAME} ${LIBFT}
	$(MAKE) -C $(LIBFT_DIR) fcleanlocal

re: fclean all
	$(MAKE) -C $(LIBFT_DIR)

.PHONY: re fclean clean all lib
