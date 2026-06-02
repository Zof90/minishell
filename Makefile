NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
INCLUDES    = -Iinclude -Ilibft

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRC_DIR     = src
OBJ_DIR     = obj

SRCS        = src/main.c \
              src/main/shell_init.c \
              src/main/shell_loop.c \
              src/main/shell_cleanup.c \
              src/main/read_line.c \
              src/env/env_init.c \
              src/env/env_access.c \
              src/env/env_utils.c \
              src/env/env_free.c \
              src/utils/error.c \
              src/utils/error_msg.c \
              src/debug/debug_print.c \
              src/signals/signals.c \
              src/signals/signals_heredoc.c \
              src/gc/gc_free.c \
              src/gc/gc_malloc.c \
              src/gc/gc_split.c \
              src/gc/gc_utile.c \
              src/gc/gc_utile2.c \
              src/lexer/lexer.c \
              src/lexer/lexer_word.c \
              src/lexer/lexer_operator.c \
              src/builtins/builtin_pwd.c \
              src/builtins/builtin_env.c \
              src/builtins/builtin_echo.c \
              src/builtins/builtin_exit.c \
              src/builtins/builtin_unset.c \
              src/builtins/builtin_cd.c \
              src/builtins/cd_path.c \
              src/builtins/builtin_export.c \
              src/builtins/builtin_export_print.c \
              src/parser/syntax.c \
              src/parser/parser.c \
              src/parser/parser_utils.c \
              src/parser/parser_redir.c \
              src/execution/executor.c \
              src/execution/executor_util.c \
              src/execution/executor_builtin.c \
              src/execution/executor_noargs.c \
              src/execution/handle_path.c \
              src/expander/expander.c \
              src/expander/expand_fields.c \
              src/expander/expand_split.c \
              src/expander/expand_str.c \
              src/expander/expand_dollar.c \
              src/expander/expand_buf.c \
              src/heredoc/heredoc_collect.c \
              src/heredoc/heredoc_expand.c \
              src/heredoc/heredoc_utils.c

OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(LIBFT): force
	$(MAKE) -C $(LIBFT_DIR)

force:

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/minishell.h include/gc.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re force
