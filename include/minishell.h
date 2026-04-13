/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:17:33 by codespace         #+#    #+#             */
/*   Updated: 2026/04/13 15:16:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700
# define _DEFAULT_SOURCE
# define _POSIX_C_SOURCE 200809L
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
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
}								t_shell;

extern volatile sig_atomic_t	g_signal;
void							set_signal(void);
bool							handler_sigint(char **line, int *last_statut);
int								minishell(int argc, char **argv, char **envp);
t_env							*env_node(char *key, char *value);
t_shell							*fill_shell(char **envp);
char							*find_pathname(char **tab_pahtname);
void							ft_env_lstadd_back(t_env **lst, t_env *new);
char							**make_pathname(t_env *lst_env, char *name);
bool							run_command(char *str_comnd, char **envp);
#endif