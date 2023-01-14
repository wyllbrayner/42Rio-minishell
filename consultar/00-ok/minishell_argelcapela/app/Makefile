.PHONY: all clean fclean re

CC =            cc
CFLAGS = 		-Wall -Wextra -Werror -ggdb3
RLFLAG =		-lreadline
AR =            ar -rcs
RM =            rm -rfd

LIBFT_DIR = 	srcs/1_libft
LIBFT.A =       $(LIBFT_DIR)/libft.a

# Mandatory & Bonus

SRCS_DIR =   	srcs
OBJS_DIR =   	$(SRCS_DIR)/.objs
HEADER_DIR =   ./srcs/
HEADER =		$(HEADER_DIR)/_minishell.h
NAME =			minishell

SRCS_FILES +=	2_utils/env/ms_add_env.c \
				2_utils/env/ms_delete_env.c \
				2_utils/env/ms_find_env_value.c \
				2_utils/env/ms_free_env.c \
				2_utils/env/ms_is_in_env.c \
				2_utils/env/ms_last_env.c \
				2_utils/env/ms_init_env.c \
				2_utils/env/ms_update_env_value.c

SRCS_FILES +=	2_utils/history/ms_add_history.c   \
				2_utils/history/ms_print_history.c \
				2_utils/history/ms_last_history.c \
				2_utils/history/ms_init_history.c \
				2_utils/history/ms_free_history.c

SRCS_FILES +=	2_utils/cmd/ms_dll_cmd_last.c \
				2_utils/cmd/ms_dll_cmd_free.c \
				2_utils/prompt/ms_free_prompt.c

SRCS_FILES +=	4_init.c

SRCS_FILES +=	5_read_input.c \
				6_read_input_here_doc.c \
				7_read_input_signals.c

SRCS_FILES +=	8_tokenizer.c \
				9_tokenizer_sintax.c \
				9b_tokenizer_sintax_utils.c \
				11_tokenizer_check_quotes.c \
				11_tokenizer_check_quotesb.c \
				12_tokenizer_connectors_vs_quotes_bonus.c \
				13_tokenizer_connectors_vs_quotes_utils.c \
				14_tokenizer_expand_dolar.c \
				15_tokenizer_expand_dolar_utils.c \
				16_tokenizer_wildcard_bonus.c \
				17_tokenizer_wildcard_utils_bonus.c \
				17b_tokenizer_wildcard_utils_bonus_2.c

SRCS_FILES +=	18_parse.c \
				18b_parse_subshells.c \
				18c_parse_subshells_2.c \
				19_parse_prompts.c \
				20_parse_input_output.c \
				21_parse_input_output_2.c \
				21_parse_input_output_3.c \
				22_parse_commands.c \
				23_parse_commands_utils.c \
				24_parse_commands_utils2.c \
				24_parse_commands_utils3.c \
				24_parse_commands_utils4.c

SRCS_FILES +=   25_execute_subshells.c \
				26_execute_commands_utils_1.c \
				27_execute_commands_utils_2.c \
				28_execute_commands_utils_3.c \
				29_execute_commands.c

SRCS_FILES +=	30_builtin_echo.c \
				31_builtin_cd.c \
				32_builtin_env.c \
				33_builtin_exit.c \
				34_builtin_export.c \
				34_builtin_exportb.c \
				35_builtin_export_utils.c \
				36_builtin_pwd.c \
				37_builtin_unset.c

SRCS_FILES +=	38_main.c \
				39_deinit.c

SRCS = 			$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS =          $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
	$(CC) -I$(HEADER_DIR) $(CFLAGS) -c $< -o $@

all:	$(NAME)

bonus:	all

$(NAME):	$(OBJS_DIR) $(OBJS) $(HEADER)
	make -C $(LIBFT_DIR)
	$(CC) -I$(HEADER_DIR) $(RLFLAG) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT.A) $(RLFLAG)
	@echo "\033[1;32mMANDATORY COMPILED SUCCESFULY!\033[0m"

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)/2_utils
	mkdir -p $(OBJS_DIR)/2_utils/env
	mkdir -p $(OBJS_DIR)/2_utils/history
	mkdir -p $(OBJS_DIR)/2_utils/prompt
	mkdir -p $(OBJS_DIR)/2_utils/cmd

clean:
	$(RM) $(OBJS_DIR)
	@echo "\033[1;32mCLEAN EXECUTED SUCCESFULY!\033[0m"

fclean:	clean
	make fclean -C $(LIBFT_DIR)
	find . -maxdepth 1 -type f ! -name "Makefile" ! -name "*.cpp" ! -name "*.supp" ! -name "*.hpp" ! -name "minishell_tester" ! -name "test_files" -delete
	@echo "\033[1;32mFCLEAN EXECUTED SUCCESFULY!\033[0m"

re:
	@make fclean && make all
	@echo "\033[1;32mRE EXECUTED SUCCESFULY!\033[0m"


# TEST
SUPP="supp.supp"

run:	$(NAME)
	@./minishell

runs:	$(NAME)
	@valgrind  --suppressions=$(SUPP) --track-origins=yes --track-fds=yes ./minishell

runl:	$(NAME)

	@valgrind  --suppressions=$(SUPP) --leak-check=full --show-leak-kinds=all --show-reachable=no --track-fds=yes --track-origins=yes ./minishell

runr:	$(NAME)
	make re
	@./minishell

runrl:	$(NAME)
	make re
	@valgrind  --suppressions=$(SUPP) --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./minishell

n:
	norminette srcs
