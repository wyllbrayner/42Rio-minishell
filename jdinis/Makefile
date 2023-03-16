LB			= lib$(NAME).a
LOCLIBFT	= ./libft
LOCLHEADER	= ./header
SRCDIR		= ./src
OBJDIR		= ./obj
SRCS		= $(wildcard $(SRCDIR)/ft_*.c) $(wildcard $(SRCDIR)/builtins/ft_*.c)
OBJS		= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
NAME		= minishell
UTIL		= ar
OPT			= rc
SUMM		= ranlib
RM			= rm -rf
FLAG		= -Wall -Wextra -Werror -g#-fsanitize=address
COMP		= cc
IN			= -I ./includes/

all:	$(NAME) 
	 valgrind --leak-check=full ./minishell

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(COMP) $(FLAG) $(IN) -c $< -o $@

$(NAME):	$(LB) $(LOCLHEADER)/ft_$(NAME).h
	$(COMP) $(FLAG) -o $(NAME) -L. -l$(NAME) -lreadline

$(LB):	$(LOCLIBFT)/libft.a $(OBJS) $(LOCLHEADER)/ft_$(NAME).h
	cp $(LOCLIBFT)/libft.a $(LB)
	$(UTIL) $(OPT) $(LB) $(OBJS)
	$(SUMM) $(LB)

$(LOCLIBFT)/libft.a:
	make -C $(LOCLIBFT)

clean:
	make clean -C $(LOCLIBFT)
	$(RM) $(OBJDIR)

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

.PHONY: all clean fclean re list norminette norminetteh
