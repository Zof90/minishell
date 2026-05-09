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
              src/env/env_init.c \
              src/env/env_access.c \
              src/env/env_utils.c \
              src/env/env_free.c \
              src/utils/free.c \
              src/utils/error.c \
              src/debug/debug_print.c \
              src/signals/signals.c \
              src/gc/gc_free.c \
              src/gc/gc_malloc.c \
              src/gc/gc_split.c \
              src/gc/gc_utile.c \
              src/lexer/lexer.c \
              src/builtins/builtin_pwd.c \
              src/builtins/builtin_env.c \
              src/builtins/builtin_echo.c \
              src/lexer/lexer_word.c \
              src/lexer/lexer_opperator.c \
              src/parser/syntax.c \
              src/parser/parser.c \
              src/parser/parser_utils.c \
              src/parser/parser_redir.c

OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re