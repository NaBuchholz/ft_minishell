# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 10:00:00 by seu_login         #+#    #+#              #
#    Updated: 2025/06/01 17:25:58 by nbuchhol         ###   ########.fr        #
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
#		  $(INCDIR)/parser.h \
		  $(INCDIR)/executor.h \
		  $(INCDIR)/builtins.h

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
			 parser/ast.c \
			 parser/syntax_check.c \
			 parser/expansion.c \
			 parser/parser_utils.c

EXECUTOR_SRC = executor/executor.c \
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
			   builtins/exit.c

ENVIRONMENT_SRC = environment/env_manager.c \
				  environment/env_expansion.c \
				  environment/env_utils.c

HISTORY_SRC = history/history.c \
			  history/history_utils.c

TEST_SRCDIR = $(SRCDIR)/tests
TEST_OBJDIR = $(OBJDIR)/tests

SRC = $(MAIN_SRC) \
	  $(LEXER_SRC) \
	  $(PARSER_SRC) \
	  $(EXECUTOR_SRC) \
	  $(BUILTINS_SRC) \
	  $(ENVIRONMENT_SRC) \
	  $(HISTORY_SRC)

TEST_SRC = tests/test_utils.c \
		   tests/test_runners.c \
		   tests/test_token_creation.c \
		   tests/test_token_memory.c \
		   tests/test_lexer.c

LEXER_FOR_TEST = lexer/tokens.c \
				 lexer/lexer.c \
				 lexer/lexer_utils.c

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEPS = $(addprefix $(OBJDIR)/, $(SRC:.c=.d))
TEST_OBJ = $(addprefix $(OBJDIR)/, $(TEST_SRC:.c=.o)) \
		   $(addprefix $(OBJDIR)/, $(LEXER_FOR_TEST:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft $(READLINE_FLAGS) -o $(NAME)
	echo "$(GREEN)Minishell compiled successfully!$(RESET)"

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
#                                   TESTS                                      #
#******************************************************************************#

debug: CFLAGS += -fsanitize=address -DDEBUG
debug: re
	echo "$(PURPLE)Debug version compiled with Address Sanitizer$(RESET)"

test: $(LIBFT) $(OBJDIR) $(TEST_OBJ)
	@echo "$(YELLOW)Linking test runner...$(RESET)"
	$(CC) $(CFLAGS) $(TEST_OBJ) -L$(LIBFT_DIR) -lft -o test_runner
	@echo "$(GREEN)Running tests...$(RESET)"
	./test_runner
	@echo "$(CYAN)Tests completed!$(RESET)"

clean_test:
	rm -f ./test_runner
	rm -rf $(OBJDIR)/tests
	echo "$(RED)Test files removed$(RESET)"

norm:
	if command -v norminette >/dev/null 2>&1; then \
		echo "$(YELLOW)Checking norm...$(RESET)"; \
		norminette $(SRCDIR) $(INCDIR); \
	else \
		echo "$(YELLOW)Norminette not found$(RESET)"; \
	fi

help:
	echo "$(CYAN)Available commands:$(RESET)"
	echo "$(GREEN)  make           $(RESET)- Compile project"
	echo "$(GREEN)  make clean     $(RESET)- Remove objects"
	echo "$(GREEN)  make fclean    $(RESET)- Remove all"
	echo "$(GREEN)  make re        $(RESET)- Recompile all"
	echo "$(GREEN)  make debug     $(RESET)- Compile with debug"
	echo "$(GREEN)  make norm      $(RESET)- Check norm"

-include $(DEPS)
.PHONY: all clean fclean re debug norm help test clean_test
.SILENT:
