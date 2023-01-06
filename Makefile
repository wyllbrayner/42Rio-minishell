LB			= lib$(NAME).a
LOCLIBFT	= ./libft
LOCLHEADER	= ./header
SRCS		= $(wildcard src/ft_*.c)
OBJS		= $(SRCS:.c=.o)
NAME		= minishell
UTIL		= ar
OPT			= rc
SUMM		= ranlib
RM			= rm -f
FLAG		= -Wall -Wextra -Werror
COMP		= cc

all:	$(NAME)

$(NAME):	$(LB) $(LOCLHEADER)/ft_$(NAME).h
	$(COMP) $(FLAG) -o $(NAME) -L. -l$(NAME)

$(LB):	$(LOCLIBFT)/libft.a $(OBJS) $(LOCLHEADER)/ft_$(NAME).h
	cp $(LOCLIBFT)/libft.a $(LB)
	$(UTIL) $(OPT) $(LB) $(OBJS)
	$(SUMM) $(LB)

$(LOCLIBFT)/libft.a:
	make -C $(LOCLIBFT)

clean:
	make clean -C $(LOCLIBFT)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LOCLIBFT)
	$(RM) $(NAME) $(LB)

re: fclean all

list:
	ls -la

norminette:
	norminette

norminetteh:
	norminette -R CheckDefine

.PRONH: all $(NAME) $(LB) $(LOCLIBFT)/libft.a clean fclean re list norminette norminetteh
