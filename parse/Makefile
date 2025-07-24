# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/12 13:07:24 by jlima-so          #+#    #+#              #
#    Updated: 2025/07/24 20:13:11 by jlima-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES=	$(wildcard *.c)

OBJ_FILES=	${SRC_FILES:.c=.o}

LIBFT_DIR=	jojo_libft

LIBFT=		jojo_libft.a

NAME=		parse.a

CC=			cc

AR=			ar rcs

CFLAGS=		-Wall -Wextra -Werror -lreadline -lncurses

all: ${NAME} ${LIBFT}

${NAME}: ${OBJ_FILES}
	${AR} ${NAME} $?

${LIBFT}:
	$(MAKE) -C $(LIBFT_DIR)

%o: %c
	${CC} ${CFLAGS} $@ $<

clean:
	rm -f ${OBJ_FILES} ${NAME} ${LIBFT}
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f ${NAME} ${LIBFT}
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
	$(MAKE) -C $(LIBFT_DIR)

.PHONY: re fclean clean all

# so:
#	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC_FILES)
#	gcc -nostartfiles -shared -o libft.so $(OBJ_FILES)