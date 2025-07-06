# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 10:00:00 by seu_login         #+#    #+#              #
#    Updated: 2025/07/06 18:02:07 by vinda-si         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -MMD -MP
READLINE_FLAGS = -lreadline
MAKEFLAGS += --no-print-directory

#******************************************************************************#
#                                   PATH                                       #
#******************************************************************************#

SRCDIR = src
OBJDIR = build
INCDIR = includes
LIBFT_DIR = libft

#******************************************************************************#
#                                   COLOR                                      #
#******************************************************************************#

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

#******************************************************************************#
#                                   FILES                                      #
#******************************************************************************#

LIBFT = $(LIBFT_DIR)/libft.a

HEADERS = $(INCDIR)/minishell.h \
		  $(INCDIR)/lexer.h \
		  $(INCDIR)/test_utils.h \
		  $(INCDIR)/parser.h \
		  $(INCDIR)/executor.h \
		  $(INCDIR)/environment.h \
#		  $(INCDIR)/builtins.h

MAIN_SRC = main.c \
		   init.c \
		   signals.c \
		   cleanup.c \
		   utils.c

LEXER_SRC = lexer/lexer.c \
			lexer/tokens.c \
			lexer/quotes.c \
			lexer/operators.c \
			lexer/lexer_utils.c

PARSER_SRC = parser/parser.c \
			 parser/syntax_check.c \
			 parser/redirections.c \
			 parser/command_list.c \
			 parser/redir_utils.c \
			 parser/arguments.c \
			 parser/simple_cmd_parse.c \
			 parser/expansion_basic.c \
			 parser/expansion_main.c \
			 parser/expansion_process.c \
			 parser/parser_utils.c \
			 parser/exit_apply.c \
			 parser/exit_status.c \
			 parser/exit_token.c \
			 parser/exit_utils.c \
			 parser/token_expansion.c

EXECUTOR_SRC = executor/executor.c \
			   executor/executor_utils.c \
			   executor/pipeline.c \
			   executor/redirections.c \
			   executor/process.c \
			   executor/path_resolution.c

BUILTINS_SRC = builtins/builtin_manager.c \
			   builtins/echo.c \
			   builtins/cd.c \
			   builtins/pwd.c \
			   builtins/export.c \
			   builtins/unset.c \
			   builtins/env.c \
			   builtins/exit.c \
			   builtins/sort_utils.c \
			   builtins/unset.c

ENVIRONMENT_SRC = environment/env_manager.c \
				  environment/env_expansion.c \
				  environment/env_set.c \
				  environment/env_utils.c \
				  environment/env_modifiers.c

HISTORY_SRC = history/history.c \
			  history/history_utils.c

TEST_SRC = tests/test_token_utils.c \
		   tests/test_token_type_append.c \
		   tests/test_heredoc.c \
		   tests/test_cleanup_utils.c \
		   tests/test_runners.c \
		   tests/test_token_creation.c \
		   tests/test_token_memory.c \
		   tests/test_lexer.c \
		   tests/test_parser.c \
		   tests/test_arg_utils.c \
		   tests/test_command.c \
		   tests/test_args_runners.c \
		   tests/test_argument.c \
		   tests/test_redirections.c \
		   tests/test_env.c \
		   tests/test_env_runner.c \
		   tests/test_parser_syntax.c

SRC = $(MAIN_SRC) \
	  $(LEXER_SRC) \
	  $(PARSER_SRC) \
	  $(EXECUTOR_SRC) \
	  $(BUILTINS_SRC) \
	  $(ENVIRONMENT_SRC) \
	  $(HISTORY_SRC) \
	  $(TEST_SRC)

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEPS = $(addprefix $(OBJDIR)/, $(SRC:.c=.d))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft $(READLINE_FLAGS) -o $(NAME)
	echo "$(GREEN)Minishell compiled with debug and tests!$(RESET)"

$(LIBFT):
	echo "$(YELLOW)Compiling libft...$(RESET)"
	$(MAKE) -C $(LIBFT_DIR)
	echo "$(GREEN)Libft compiled!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFT_DIR) -c $< -o $@
	echo "$(BLUE)Compiling: $(notdir $<)$(RESET)"

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/lexer
	mkdir -p $(OBJDIR)/parser
	mkdir -p $(OBJDIR)/executor
	mkdir -p $(OBJDIR)/builtins
	mkdir -p $(OBJDIR)/environment
	mkdir -p $(OBJDIR)/history
	mkdir -p $(OBJDIR)/tests

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJDIR)
	echo "$(RED)Objects and Deps removed$(RESET)"

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	echo "$(RED)Executable $(NAME) removed$(RESET)"

re: fclean all
	echo "$(CYAN)Project recompiled!$(RESET)"

#******************************************************************************#
#                              MODO DEBUG                                      #
#******************************************************************************#

test: $(NAME)
	echo "$(CYAN)Running tests...$(RESET)"
	./$(NAME) --test

test-valgrind: $(NAME)
	echo "$(PURPLE)Running tests with Valgrind...$(RESET)"
	valgrind --leak-check=full ./$(NAME) --test

valgrind: $(NAME)
	echo "$(PURPLE)Running with Valgrind...$(RESET)"
	valgrind --suppressions=readline.sup --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

gdb: debug
	echo "$(PURPLE)Starting GDB...$(RESET)"
	gdb ./$(NAME)

#******************************************************************************#
#                              BUILD TYPES                                     #
#******************************************************************************#

norm:
	if command -v norminette >/dev/null 2>&1; then \
		echo "$(YELLOW)Checking norm...$(RESET)"; \
		norminette $(SRCDIR) $(INCDIR); \
	else \
		echo "$(YELLOW)Norminette not found$(RESET)"; \
	fi

help:
	echo "$(CYAN)Available commands:$(RESET)"
	echo "$(GREEN)  make           $(RESET)- Compile with debug & tests"
	echo "$(GREEN)  make test      $(RESET)- Run tests"
	echo "$(GREEN)  make test-valgrind $(RESET)- Run tests with valgrind"
	echo "$(GREEN)  make valgrind  $(RESET)- Run with valgrind"
	echo "$(GREEN)  make gdb       $(RESET)- Debug with gdb"
	echo "$(GREEN)  make clean     $(RESET)- Remove objects"
	echo "$(GREEN)  make fclean    $(RESET)- Remove all"
	echo "$(GREEN)  make re        $(RESET)- Recompile all"
	echo "$(GREEN)  make norm      $(RESET)- Check norm"

-include $(DEPS)
.PHONY: all clean fclean re valgrind gdb  norm help
.SILENT:
