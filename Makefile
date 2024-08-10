LOCLIBFT    = ./libft
SRCDIR      = ./src/
SRCS        = ft_bin.c ft_cmd_builder_0.c ft_cmd_builder_1.c ft_error.c \
				ft_exec_token.c ft_execute.c ft_expander_quote.c \
				ft_expander_var_0.c ft_expander_var_1.c ft_expander_var_2.c \
				ft_expander_var_3.c ft_free.c ft_heredoc_0.c ft_heredoc_1.c \
				ft_init_var.c ft_is_exec.c ft_list_0.c ft_list_1.c ft_main.c \
				ft_parse.c ft_parse_redirect.c ft_pipe.c ft_redirect_builder.c \
				ft_redirect.c ft_utils.c ft_valid_lexcal_cmd.c \
				ft_valid_quotes_0.c ft_valid_quotes_1.c ft_valid_redirect_0.c \
				ft_valid_redirect_1.c ft_var_expansion.c ft_cd.c ft_echo.c \
				ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c \
				ft_printf.c ft_printf_utils.c ft_puthex.c ft_putnbr_u.c
SRCS        := $(addprefix $(SRCDIR), $(SRCS))
OBJDIR      = ./obj/
OBJS        = $(addprefix $(OBJDIR), $(notdir $(SRCS:.c=.o)))
NAME        = minishell
RM          = rm -rf
FLAG        = -Wall -Wextra -Werror
COMP        = cc
IN          = -I ./includes/
YELLOW		= \033[33m
GREEN		= \033[32m
RESET		= \033[0m

detected_OS := $(shell uname)
ifeq ($(detected_OS),Linux)
	LDFLAGS = -L /usr/local/opt/readline/lib
	CPPFLAGS = -I /usr/local/opt/readline/include
else
	CPPFLAGS += -I ~/.brew/opt/readline/include
	LDFLAGS += -L ~/.brew/opt/readline/lib
endif

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(COMP) $(FLAG) $(IN) -c $< -o $@
	@echo -n "#"

.c.o:
	$(COMP) $(FLAG) -I ~/.brew/opt/readline/include/ -c $< -o $(<:.c=.o)

$(NAME): $(LOCLIBFT)/libft.a $(OBJS)
	@$(COMP) $(FLAG) -o $(NAME) $(OBJS) -L$(LOCLIBFT) -lft -lreadline $(CPPFLAGS) $(LDFLAGS)
	@echo "\n\$(GREEN) 💯 | $(NAME) created.$(RESET)"

$(LOCLIBFT)/libft.a:
	make -C $(LOCLIBFT)

clean:
	make clean -C $(LOCLIBFT)
	@$(RM) $(OBJDIR)
	@echo "$(YELLOW) 🧹 | $(NAME) cleaned.$(RESET)"

fclean: clean
	make fclean -C $(LOCLIBFT)
	@$(RM) $(NAME)
	@echo "$(YELLOW) 🌪️ | $(NAME) all cleaned.$(RESET)"

re: fclean all

.PHONY: all $(NAME) $(LOCLIBFT)/libft.a clean fclean re