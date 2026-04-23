/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:07:13 by azaytsev          #+#    #+#             */
/*   Updated: 2026/04/29 12:43:30 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700
# define _DEFAULT_SOURCE
# define _POSIX_C_SOURCE 200809L
# include <stdio.h>
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_HEREDOC,
	TOK_APPEND,
}								t_token_type;

typedef struct s_gc
{
	void						*ptr;
	struct s_gc					*next;

}								t_gc;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	struct s_token				*next;
}								t_token;

typedef struct s_redir
{
	t_token_type				type;
	char						*file;
	int							heredoc_quoted;
	struct s_redir				*next;
}								t_redir;

typedef struct s_cmd
{
	char						**args;
	t_redir						*redirs;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct s_shell
{
	t_env						*env;
	int							exit_status;
	int							running;
	t_gc						*gc;
}								t_shell;

extern volatile sig_atomic_t	g_signal;

t_env							*env_new_node(const char *key,
									const char *value);
void							env_add_back(t_env **env, t_env *new_node);
t_env							*env_init(char **envp);
char							*env_get(t_env *env, const char *key);
int								env_set(t_env **env, const char *key,
									const char *value);
int								env_unset(t_env **env, const char *key);
char							**env_to_array(t_env *env);
int								env_size(t_env *env);
void							free_env(t_env *env);
void							free_str_array(char **arr);
void							free_tokens(t_token *tokens);
void							free_redirs(t_redir *redirs);
void							free_cmds(t_cmd *cmds);
void							print_error(const char *context,
									const char *message);
void							debug_print_tokens(t_token *tokens);
void							debug_print_cmds(t_cmd *cmds);
void							debug_print_env(t_env *env);
void							setup_signals_interactive(void);
int								token_size(char *str);
int		builtin_pwd(t_shell *shell, char **args);
int		builtin_env(t_shell *shell, char **args);
int		builtin_echo(t_shell *shell, char **args);
int		init_shell(t_shell *shell, int argc, char **argv, char **envp);
void	shell_loop(t_shell *shell);
void	cleanup_shell(t_shell *shell);

t_token							*lex(t_shell *shell, char *line);
#endif
