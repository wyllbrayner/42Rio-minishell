NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC =	ft_strlen.c \
		ft_strdup.c \
		ft_memcpy.c \
		ft_split.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strchr.c \
		ft_substr.c \
		ft_isalnum.c \
		ft_isdigit.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_strncmp.c \
		ft_calloc.c \
		ft_bzero.c \
		ft_memset.c \
		ft_strcmp.c \
		ft_itoa.c \
		ft_atoi.c \
		ft_putstr_fd.c \
		ft_putchar_fd.c

OBJECTS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar -rcs $(NAME) $(OBJECTS)

$(OBJECTS): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	$(RM) $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
