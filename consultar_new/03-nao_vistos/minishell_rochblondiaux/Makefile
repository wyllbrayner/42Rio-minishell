# COLORS
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

# SYMBOLS
INFO = $(BLUE)ℹ️  $(NOC)
SUCCESS = $(GREEN)✅  $(GREEN)
WARNING = $(YELLOW)⚠️  $(YELLOW)
ERROR = $(RED)❌$(WHITE)  $(RED)

# Binary
NAME=minishell

# Path
SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INCDIR = ./includes

# Leaks cmd
LEAKS_CMD = leaks -atExit --

# Name
SRC_NAME =	main.c                                \
			app/load.c                            \
			app/loop.c                            \
			app/mode.c                            \
			app/runtime.c                         \
			app/start.c                           \
			app/stop.c                            \
			modules/executor.c                    \
			modules/syntaxer.c                    \
			modules/expander.c                    \
			modules/lexer.c                       \
			modules/parser.c                      \
			builtins/dispatcher.c                 \
			builtins/cd.c                         \
			builtins/echo.c                       \
			builtins/pwd.c                        \
			builtins/exit.c                       \
			builtins/unset.c                      \
			builtins/export.c                     \
			builtins/env.c                        \
			utils/app/prompt.c                    \
			utils/app/error.c                     \
			utils/app/signals.c                   \
			utils/commands/free.c                 \
			utils/commands/init.c                 \
			utils/commands/length.c               \
			utils/modules/executor/fork.c         \
			utils/modules/executor/checks.c       \
			utils/modules/executor/path.c         \
			utils/modules/executor/args.c         \
			utils/modules/executor/executable.c   \
			utils/modules/executor/execution.c    \
			utils/modules/executor/pipe.c         \
			utils/modules/lexer/token.c           \
			utils/modules/expander/wildcard.c     \
			utils/modules/expander/env.c          \
			utils/modules/expander/input.c        \
			utils/modules/expander/output.c       \
			utils/modules/syntaxer/token.c        \
			utils/modules/parser/redirections.c   \
			utils/modules/parser/tokens.c         \
			utils/modules/parser/commands.c       \
			utils/modules/parser/separators.c     \
			utils/modules/parser/quotes.c         \
			utils/modules/parser/fill_quotes.c    \
			utils/builtins/is.c                   \
			utils/builtins/get_path.c             \
			utils/builtins/path.c                 \
			utils/string/strcat.c                 \
			utils/string/replace.c                \
			utils/string/joins.c                  \
			utils/string/path.c                   \
			utils/string/reset.c                  \
			utils/string/contains.c               \
			utils/string/strchr_separator.c       \
			utils/env/get.c                       \
			utils/env/set.c                       \
			utils/env/checks.c                    \
			utils/env/free.c                      \
			utils/env/format.c                    \
			utils/array/length.c                  \
			utils/array/free.c                    \
			utils/array/sub.c                     \
			utils/array/add.c                     \
			utils/array/empty.c                   \
			utils/io/env.c                        \
			utils/io/exists.c                     \
			utils/io/paths.c                      \
			utils/io/read.c                       \
			utils/io/write.c                      \
			utils/map/sort.c                      \
			utils/map/length.c                    \
			utils/map/free.c                      \
			utils/map/add.c                       \
			utils/map/create.c                    \
			utils/map/init.c                      \
			utils/map/get.c                       \
			utils/map/remove.c                    \
			utils/redirections/new.c              \
			utils/redirections/free.c             \
			utils/redirections/add.c              \
			utils/redirections/length.c           \
			utils/delimiters/delimit.c

OBJ_NAME = $(SRC_NAME:.c=.o)

# Files
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

# Libft
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft -lreadline

# Flags
CC = gcc $(CFLAGS)
CFLAGS = -Wall -Wextra -Werror

all: obj $(FT_LIB) $(NAME)

obj:
	@echo "$(INFO)Creating objects folder... $(NOC)"
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/app
	@mkdir -p $(OBJ_PATH)/modules
	@mkdir -p $(OBJ_PATH)/builtins
	@mkdir -p $(OBJ_PATH)/utils
	@mkdir -p $(OBJ_PATH)/utils/io
	@mkdir -p $(OBJ_PATH)/utils/app
	@mkdir -p $(OBJ_PATH)/utils/string
	@mkdir -p $(OBJ_PATH)/utils/array
	@mkdir -p $(OBJ_PATH)/utils/delimiters
	@mkdir -p $(OBJ_PATH)/utils/env
	@mkdir -p $(OBJ_PATH)/utils/map
	@mkdir -p $(OBJ_PATH)/utils/commands
	@mkdir -p $(OBJ_PATH)/utils/redirections
	@mkdir -p $(OBJ_PATH)/utils/builtins
	@mkdir -p $(OBJ_PATH)/utils/modules
	@mkdir -p $(OBJ_PATH)/utils/modules/lexer
	@mkdir -p $(OBJ_PATH)/utils/modules/syntaxer
	@mkdir -p $(OBJ_PATH)/utils/modules/executor
	@mkdir -p $(OBJ_PATH)/utils/modules/expander
	@mkdir -p $(OBJ_PATH)/utils/modules/parser
	@echo "$(SUCCESS)Objects folder created successfully$(NOC)"

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	@echo "$(INFO)Building libft library...$(NOC)"
	@make -C $(FT)
	@echo "$(SUCCESS)Libft library built successfully!$(NOC)"

$(NAME): $(OBJ)
	@echo "$(INFO)Building $(NAME)...$(NOC)"
	@$(CC) $(OBJ) $(FT_LNK) -o $@
	@echo "$(SUCCESS)$(NAME) built successfully!$(NOC)"

clean:
	@echo "$(INFO)Deleting .o files...$(NOC)"
	@rm -rf $(OBJ_PATH)
	@echo "$(SUCCESS).o files deleted successfully!$(NOC)"
	@echo "$(INFO)Deleting libft files..."
	@make -C $(FT) clean
	@echo "$(SUCCESS)Libft files deleted successfully!$(NOC)"

fclean: clean
	@echo "$(INFO)Deleting $(NAME)...$(NOC)"
	@rm -rf $(NAME)
	@echo "$(SUCCESS)$(NAME) deleted successfully!$(NOC)"
	@make -C $(FT) fclean

leaks: $(NAME)
	$(LEAKS_CMD) ./$(NAME)

run: $(NAME)
	@./$(NAME)

re: fclean all

.PHONY:			all clean fclean re leaks run