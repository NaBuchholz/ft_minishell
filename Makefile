# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 10:00:00 by seu_login         #+#    #+#              #
#    Updated: 2025/07/13 15:19:50 by nbuchhol         ###   ########.fr        #
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
		  $(INCDIR)/parser.h \
		  $(INCDIR)/executor.h \
		  $(INCDIR)/environment.h \
		  $(INCDIR)/heredoc.h \

MAIN_SRC = main.c \
		   init.c \
		   signals.c \
		   signals_utils.c \
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
			 parser/exit_expand.c \
			 parser/exit_apply.c \
			 parser/exit_status.c \
			 parser/exit_token.c \
			 parser/exit_utils.c \
			 parser/token_expansion.c

EXECUTOR_SRC = executor/executor.c \
			   executor/executor_utils.c \
			   executor/pipeline.c \
			   executor/redir_utils.c \
			   executor/pipeline_utils.c \
			   executor/redirections.c \
			   executor/process.c \
			   executor/path_resolution.c \
			   executor/builtins_dispatcher.c \
			   executor/exit_dispatcher.c \
			   executor/pwd_dispatcher.c \


HEREDOC_SRC = heredoc/heredoc_utils.c \
			  heredoc/heredoc_parser.c \
			  heredoc/heredoc_reader.c \
			  heredoc/heredoc_reader_utils.c \
			  heredoc/heredoc_expansion.c \
			  heredoc/heredoc_pipes.c \
			  heredoc/heredoc_signals.c \
			  heredoc/heredoc_clear.c \
			  heredoc/heredoc_executor.c \
			  heredoc/heredoc_session.c

BUILTINS_SRC = builtins/builtin_manager.c \
			   builtins/echo.c \
			   builtins/cd.c \
			   builtins/pwd.c \
			   builtins/export.c \
			   builtins/env.c \
			   builtins/exit.c \
			   builtins/sort_utils.c \
			   builtins/unset.c \
			   builtins/cd_dispatcher.c

ENVIRONMENT_SRC = environment/env_manager.c \
				  environment/env_expansion.c \
				  environment/env_set.c \
				  environment/env_utils.c \
				  environment/env_modifiers.c \
				  environment/env_print.c

SRC = $(MAIN_SRC) \
	  $(LEXER_SRC) \
	  $(PARSER_SRC) \
	  $(EXECUTOR_SRC) \
	  $(BUILTINS_SRC) \
	  $(ENVIRONMENT_SRC) \
	  $(HEREDOC_SRC)

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEPS = $(addprefix $(OBJDIR)/, $(SRC:.c=.d))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft $(READLINE_FLAGS) -o $(NAME)
	echo "$(GREEN)Minishell compiled!$(RESET)"

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
	mkdir -p $(OBJDIR)/heredoc

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
	echo "$(GREEN)  make valgrind  $(RESET)- Run with valgrind"
	echo "$(GREEN)  make gdb       $(RESET)- Debug with gdb"
	echo "$(GREEN)  make clean     $(RESET)- Remove objects"
	echo "$(GREEN)  make fclean    $(RESET)- Remove all"
	echo "$(GREEN)  make re        $(RESET)- Recompile all"
	echo "$(GREEN)  make norm      $(RESET)- Check norm"

-include $(DEPS)
.PHONY: all clean fclean re valgrind gdb  norm help
.SILENT:
