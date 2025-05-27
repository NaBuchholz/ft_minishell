# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 10:00:00 by seu_login         #+#    #+#              #
#    Updated: 2025/05/27 11:05:20 by nbuchhol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
READLINE_FLAGS = -lreadline

SRCDIR = src
OBJDIR = obj
INCDIR = includes
LIBFT_DIR = libft

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

LIBFT = $(LIBFT_DIR)/libft.a

HEADERS = $(INCDIR)/minishell.h \
#		  $(INCDIR)/lexer.h \
		  $(INCDIR)/parser.h \
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

SRC = $(MAIN_SRC) \
	  $(LEXER_SRC) \
	  $(PARSER_SRC) \
	  $(EXECUTOR_SRC) \
	  $(BUILTINS_SRC) \
	  $(ENVIRONMENT_SRC) \
	  $(HISTORY_SRC)

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft $(READLINE_FLAGS) -o $(NAME)
	@echo -e "$(GREEN)Minishell compiled successfully!$(RESET)"

$(LIBFT):
	@echo -e "$(YELLOW)Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo -e "$(GREEN)Libft compiled!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFT_DIR) -c $< -o $@
	@echo -e "$(BLUE)Compiling: $(notdir $<)$(RESET)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/lexer
	@mkdir -p $(OBJDIR)/parser
	@mkdir -p $(OBJDIR)/executor
	@mkdir -p $(OBJDIR)/builtins
	@mkdir -p $(OBJDIR)/environment
	@mkdir -p $(OBJDIR)/history

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJDIR)
	@echo -e "$(RED)Objects removed$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo -e "$(RED)Executable $(NAME) removed$(RESET)"

re: fclean all
	@echo -e "$(CYAN)Project recompiled!$(RESET)"

debug: CFLAGS += -fsanitize=address -DDEBUG
debug: re
	@echo -e "$(PURPLE)Debug version compiled with Address Sanitizer$(RESET)"

norm:
	@if command -v norminette >/dev/null 2>&1; then \
		echo -e "$(YELLOW)Checking norm...$(RESET)"; \
		norminette $(SRCDIR) $(INCDIR); \
	else \
		echo -e "$(YELLOW)Norminette not found$(RESET)"; \
	fi

help:
	@echo -e "$(CYAN)Available commands:$(RESET)"
	@echo -e "$(GREEN)  make           $(RESET)- Compile project"
	@echo -e "$(GREEN)  make clean     $(RESET)- Remove objects"
	@echo -e "$(GREEN)  make fclean    $(RESET)- Remove all"
	@echo -e "$(GREEN)  make re        $(RESET)- Recompile all"
	@echo -e "$(GREEN)  make debug     $(RESET)- Compile with debug"
	@echo -e "$(GREEN)  make norm      $(RESET)- Check norm"

.PHONY: all clean fclean re debug norm help
