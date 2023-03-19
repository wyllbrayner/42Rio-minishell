LB          = lib$(NAME).a
LOCLIBFT    = ./libft
LOCLHEADER  = ./header
SRCDIR      = ./src
OBJDIR      = ./obj
#SRCS        = $(wildcard $(SRCDIR)/ft_*.c) $(wildcard $(SRCDIR)/builtins/ft_*.c) 
SRCS        = $(wildcard $(SRCDIR)/ft_*.c) $(wildcard $(SRCDIR)/builtins/ft_*.c) $(wildcard $(SRCDIR)/42Rio-printf/ft_*.c)
OBJS        = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
NAME        = minishell
UTIL        = ar
OPT         = rc
SUMM        = ranlib
RM          = rm -f
#FLAG        = -g -Wall -Wextra -Werror -fsanitize=address
FLAG        = -Wall -Wextra -Werror
COMP        = cc
IN          = -I ./includes/

ifeq ($(OS), Linux)
		IN2 = -L ~/.brew/opt/readline/lib -L /opt/homebrew/Cellar/readline/8.2.1/lib -I /opt/homebrew/Cellar/readline/8.2.1/include -I ~/.brew/opt/readline/include
else
		IN2 = -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
endif

### -L ~/.brew/opt/readline/lib -L /opt/homebrew/Cellar/readline/8.2.1/lib -I /opt/homebrew/Cellar/readline/8.2.1/include -I ~/.brew/opt/readline/include

all:    $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(COMP) $(FLAG) $(IN) -c $< -o $@

$(NAME):    $(LB) $(LOCLHEADER)/ft_$(NAME).h
	$(COMP) $(FLAG) -o $(NAME) -L. -l$(NAME) -lreadline $(IN2)

$(LB):    $(LOCLIBFT)/libft.a $(OBJS) $(LOCLHEADER)/ft_$(NAME).h
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

.PHONY: all clean fclean re list norminette norminetteh
