SRCS	= 	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
			ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
			ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
			ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_isspace.c
OBJDIR		= ./obj/
OBJS	= $(addprefix $(OBJDIR), $(notdir $(SRCS:.c=.o)))
PROJ	= ft
NAME	= libft
RM		= rm -rf
UTIL	= ar
OPT		= rc
SUMM	= ranlib
COMP	= cc
FLAG	= -Wall -Wextra -Werror
LOCLIB	= .
YELLOW	= \033[33m
GREEN	= \033[32m
RESET	= \033[0m

all:	$(NAME)

$(OBJDIR)%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(COMP) $(FLAG) -c $< -o $@
	@echo -n "#"

$(NAME):	$(OBJS) lib$(PROJ).h
	@$(UTIL) $(OPT) $(NAME).a $(OBJS)
	@$(SUMM) $(NAME).a
	@echo "\n\$(GREEN) 💯 | $(NAME) default created.$(RESET)"

clean:
	@$(RM) $(OBJDIR)
	@echo "$(YELLOW) 🧹 | $(NAME) cleaned.$(RESET)"

fclean: clean
	@$(RM) $(NAME).a
	@echo "$(YELLOW) 🌪️ | $(NAME) all cleaned.$(RESET)"

re: fclean all

list:
	ls -la

.PRONH: all $(NAME) clean fclean re list
