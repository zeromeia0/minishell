LIB_DIR=	libft

SRC_FILES=  ${LIB_DIR}/ft_abs_strcmp.c ${LIB_DIR}/ft_atoi.c ${LIB_DIR}/ft_atol.c ${LIB_DIR}/ft_bzero.c ${LIB_DIR}/ft_calloc.c ${LIB_DIR}/ft_emptystr.c \
			${LIB_DIR}/ft_free_matrix.c ${LIB_DIR}/ft_free_matrix_count.c ${LIB_DIR}/ft_free_matrix_node.c ${LIB_DIR}/pipex_split.c \
			${LIB_DIR}/ft_giga_split.c ${LIB_DIR}/ft_isalnum.c ${LIB_DIR}/ft_isalpha.c ${LIB_DIR}/ft_isascii.c ${LIB_DIR}/ft_isdigit.c \
			${LIB_DIR}/ft_isminishell.c ${LIB_DIR}/ft_isprint.c ${LIB_DIR}/ft_itoa.c ${LIB_DIR}/ft_join_matrix.c ${LIB_DIR}/ft_lstadd_back.c \
			${LIB_DIR}/ft_lstadd_front.c ${LIB_DIR}/ft_lstclear.c ${LIB_DIR}/ft_lstdelone.c ${LIB_DIR}/ft_lstiter.c ${LIB_DIR}/ft_lstlast.c \
			${LIB_DIR}/ft_lstmap.c ${LIB_DIR}/ft_lstnew.c ${LIB_DIR}/ft_lstsize.c ${LIB_DIR}/ft_mat_join.c ${LIB_DIR}/ft_matlen.c ${LIB_DIR}/ft_matnstr.c \
			${LIB_DIR}/ft_matrix_in_matrix.c ${LIB_DIR}/ft_matrix_unify.c ${LIB_DIR}/ft_memchr.c ${LIB_DIR}/ft_memcmp.c ${LIB_DIR}/ft_memcpy.c \
			${LIB_DIR}/ft_memmove.c ${LIB_DIR}/ft_memset.c ${LIB_DIR}/ft_print_matrix.c ${LIB_DIR}/ft_putchar_fd.c ${LIB_DIR}/ft_putendl_fd.c \
			${LIB_DIR}/ft_putnbr_fd.c ${LIB_DIR}/ft_putstr_fd.c ${LIB_DIR}/ft_rmrep.c ${LIB_DIR}/ft_split.c ${LIB_DIR}/ft_split_sep.c ${LIB_DIR}/ft_strcat.c \
			${LIB_DIR}/ft_strchr.c ${LIB_DIR}/ft_strcmp.c ${LIB_DIR}/ft_str_count.c ${LIB_DIR}/ft_strcpy.c ${LIB_DIR}/ft_strdup.c ${LIB_DIR}/ft_striteri.c \
			${LIB_DIR}/ft_strjoin.c ${LIB_DIR}/ft_strjoin_free.c ${LIB_DIR}/ft_strlcat.c ${LIB_DIR}/ft_strlcpy.c ${LIB_DIR}/ft_strlen.c ${LIB_DIR}/ft_strmapi.c \
			${LIB_DIR}/ft_strmat.c ${LIB_DIR}/ft_strncmp.c ${LIB_DIR}/ft_strndup.c ${LIB_DIR}/ft_strnmat.c ${LIB_DIR}/ft_strnstr.c ${LIB_DIR}/ft_strrchr.c ${LIB_DIR}/ft_strstr.c \
			${LIB_DIR}/ft_strsubs.c ${LIB_DIR}/ft_strtrim.c ${LIB_DIR}/ft_substr.c ${LIB_DIR}/ft_swap.c ${LIB_DIR}/ft_tolower.c ${LIB_DIR}/ft_toupper.c ${LIB_DIR}/ft_wrdchr.c
	
OBJ_FILES=	${SRC_FILES:.c=.o}

NAME=		../jojo_libft.a

HDR_FILE=	libft.h

CC=			cc

CFLAGS=		-Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJ_FILES}
	ar rcs $@ $?

%o: %c
	${CC} ${CFLAGS} -c $@ -o $<

clean: 
	rm -f $(OBJ_BONUS) $(OBJ_FILES) 
	@rm -f .bonus

fclean: clean 
	rm -f ${NAME}

fcleanlocal:
	rm -f ${NAME}

re: fclean all

.PHONY: re fclean clean all