NAME = libftprintf.a

SRCS = ft_printf.c \
        parser.c parser_utils.c \
        print_conv.c print_utils.c print_digits.c \
		mod_utils.c utils.c

LIB_DIR = lib.rest

SRCS_L = ft_atoi.c ft_bzero.c ft_calloc.c \
		 ft_isdigit.c ft_memcpy.c ft_memset.c \
		 ft_strchr.c ft_strdup.c ft_strlcpy.c \
		 ft_strlen.c ft_substr.c

SRCS_LIB = $(addprefix ${LIB_DIR}/,${SRCS_L})

INCLUDE = -I. -I${LIB_DIR}

OBJS = ${SRCS:.c=.o} 

OBJS_LIB = ${SRCS_LIB:.c=.o}

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror 

all	: ${NAME} 

${NAME} : ${OBJS} ${OBJS_LIB} 
	ar rcs ${NAME} $?

bonus : all

%.o :	%.c ./ft_printf.h ./${LIB_DIR}/libft.h 
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@ 

clean	:
	rm -rf ${OBJS} ${OBJS_LIB} 
fclean	:	clean
	rm -rf ${NAME}

re		:	fclean all  

.PHONY	:	fclean all clean re bonus 
