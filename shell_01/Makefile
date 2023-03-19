LB          = lib$(NAME).a
LOCLIBFT    = ./libft
LOCLHEADER  = ./header
SRCDIR      = ./src
OBJDIR      = ./obj
SRCS        = ft_bin.c ft_cmd_builder_0.c ft_cmd_builder_1_ok.c ft_error_ok.c ft_exec_token.c ft_execute.c ft_expander_quote.c ft_expander_var_0.c \
			  ft_expander_var_1.c ft_expander_var_2.c ft_expander_var_3.c ft_free_ok.c ft_heredoc_0_ok.c ft_heredoc_1_ok.c ft_init_var_ok.c ft_is_exec.c ft_list_0.c \
			  ft_list_1.c ft_main_ok.c ft_parse.c ft_parse_redirect.c ft_pipe_j.c ft_redirect_builder.c ft_redirect_j.c ft_utils_ok.c ft_valid_lexcal_cmd.c ft_valid_quotes_0.c \
			  ft_valid_quotes_1.c ft_valid_redirect_0_ok.c ft_valid_redirect_1_ok.c ft_var_expansion.c ft_cd.c ft_echo_0.c ft_env.c ft_exit.c ft_export.c ft_pwd.c \
			  ft_unset.c ft_printf.c ft_printf_utils.c ft_puthex.c ft_utoa.c
SRCS        := $(addprefix $(SRCDIR)/,$(SRCS))
OBJS        = $(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))
NAME        = minishell
UTIL        = ar
OPT         = rc
SUMM        = ranlib
RM          = rm -f
FLAG        = -Wall -Wextra -Werror
COMP        = cc
IN          = -I ./includes/

detected_OS := $(shell uname)
ifeq ($(detected_OS),Linux)
LDFLAGS = -L /usr/local/opt/readline/lib
CPPFLAGS = -I /usr/local/opt/readline/include
else
CPPFLAGS += -I/Users/woliveir/.brew/opt/readline/include
LDFLAGS += -L/Users/woliveir/.brew/opt/readline/lib
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(COMP) $(FLAG) $(IN) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LOCLIBFT)/libft.a $(LOCLHEADER)/ft_$(NAME).h
	$(COMP) $(FLAG) -o $(NAME) $(OBJS) -L$(LOCLIBFT) -lft -lreadline $(CPPFLAGS) $(LDFLAGS)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(LOCLIBFT)/libft.a:
	make -C $(LOCLIBFT)

.c.o:
	$(COMP) $(FLAG) -I ~/.brew/opt/readline/include -c $< -o $(<:.c=.o)

clean:
	make clean -C $(LOCLIBFT)
	$(RM) -r $(OBJDIR)

fclean: clean
	make fclean -C $(LOCLIBFT)
	$(RM) $(NAME) $(LB)

re: fclean all

install: all
		cp minishell ~/.minishell
		echo "alias jw='~/.minishell'" >> ~/.bashrc
		. ~/.bashrc
		exec bash

uninstall:
	@echo "Removing jw alias from bashrc..."
	@sed -i '/alias jw='.*'/d' ~/.bashrc
	@echo "Deleting minishell executable from home directory..."
	@rm -f ~/.minishell
	exec bash

.PHONY: all re clean fclean uninstall install