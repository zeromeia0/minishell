# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/28 15:47:43 by vivaz-ca          #+#    #+#              #
#    Updated: 2025/11/10 23:30:12 by vvazzs           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC_DIR = libft
GNL_DIR = get_next_line

SRC_FILES = $(SRC_DIR)/ft_atoi.c \
			$(SRC_DIR)/ft_bzero.c \
			$(SRC_DIR)/ft_calloc.c \
			$(SRC_DIR)/ft_emptystr.c \
			$(SRC_DIR)/ft_free_matrix.c \
			$(SRC_DIR)/ft_free_matrix_count.c \
			$(SRC_DIR)/ft_isalnum.c \
			$(SRC_DIR)/ft_isalpha.c \
			$(SRC_DIR)/ft_isascii.c \
			$(SRC_DIR)/ft_isdigit.c \
			$(SRC_DIR)/ft_str_is_alnum.c \
			$(SRC_DIR)/ft_isprint.c \
			$(SRC_DIR)/ft_itoa.c \
			$(SRC_DIR)/ft_lstadd_back.c \
			$(SRC_DIR)/ft_lstadd_front.c \
			$(SRC_DIR)/ft_lstclear.c \
			$(SRC_DIR)/ft_lstdelone.c \
			$(SRC_DIR)/ft_lstiter.c \
			$(SRC_DIR)/ft_lstlast.c \
			$(SRC_DIR)/ft_lstmap.c \
			$(SRC_DIR)/ft_lstnew.c \
			$(SRC_DIR)/ft_lstsize.c \
			$(SRC_DIR)/ft_matlen.c \
			$(SRC_DIR)/ft_memchr.c \
			$(SRC_DIR)/ft_memcmp.c \
			$(SRC_DIR)/ft_memcpy.c \
			$(SRC_DIR)/ft_memmove.c \
			$(SRC_DIR)/ft_memset.c \
			$(SRC_DIR)/ft_print_matrix.c \
			$(SRC_DIR)/ft_putchar_fd.c \
			$(SRC_DIR)/ft_putendl_fd.c \
			$(SRC_DIR)/ft_putnbr_fd.c \
			$(SRC_DIR)/ft_putstr_fd.c \
			$(SRC_DIR)/ft_split.c \
			$(SRC_DIR)/ft_strcat.c \
			$(SRC_DIR)/ft_strchr.c \
			$(SRC_DIR)/ft_strcmp.c \
			$(SRC_DIR)/ft_strcpy.c \
			$(SRC_DIR)/ft_strdup.c \
			$(SRC_DIR)/ft_striteri.c \
			$(SRC_DIR)/ft_strjoin.c \
			$(SRC_DIR)/ft_strjoin_free.c \
			$(SRC_DIR)/ft_strlcat.c \
			$(SRC_DIR)/ft_strlcpy.c \
			$(SRC_DIR)/ft_strlen.c \
			$(SRC_DIR)/ft_strmapi.c \
			$(SRC_DIR)/ft_strmat.c \
			$(SRC_DIR)/ft_strncmp.c \
			$(SRC_DIR)/ft_strndup.c \
			$(SRC_DIR)/ft_strnmat.c \
			$(SRC_DIR)/ft_strnstr.c \
			$(SRC_DIR)/ft_strrchr.c \
			$(SRC_DIR)/ft_strstr.c \
			$(SRC_DIR)/ft_strtrim.c \
			$(SRC_DIR)/ft_substr.c \
			$(SRC_DIR)/ft_tolower.c \
			$(SRC_DIR)/ft_toupper.c \
			$(SRC_DIR)/ft_wrdchr.c \
			$(SRC_DIR)/pipex_split.c \
			$(GNL_DIR)/get_next_line_bonus.c \
			$(GNL_DIR)/get_next_line_utils_bonus.c

OBJ_FILES = $(SRC_FILES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@ar rcs $@ $^
	@echo "$(NAME) created successfully!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_FILES)
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) removed."

re: fclean all

.PHONY: all clean fclean re
