/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zof <zof@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:07:20 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/14 18:28:34 by zof              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// volatile sig_atomic_t	g_signal = 0;

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell	shell;

// 	if (!init_shell(&shell, argc, argv, envp))
// 		return (1);
// 	setup_signals_interactive();
// 	shell_loop(&shell);
// 	cleanup_shell(&shell);
// 	return (shell.exit_status);
// }


#include "minishell.h"
#include <string.h>

volatile sig_atomic_t	g_signal = 0;

static t_cmd	*mk_cmd(char **args, t_redir *redirs)
{
	t_cmd	*c = calloc(1, sizeof(t_cmd));
	c->args = args;
	c->redirs = redirs;
	c->next = NULL;
	c->pid = 0;
	return (c);
}

static t_redir	*mk_redir(t_token_type type, char *file, t_redir *next)
{
	t_redir	*r = calloc(1, sizeof(t_redir));
	r->type = type;
	r->file = strdup(file);
	r->heredoc_quoted = 0;
	r->next = next;
	return (r);
}

static char	**mk_args(char *a0, char *a1, char *a2, char *a3)
{
	char	**t = calloc(5, sizeof(char *));
	int		i = 0;
	if (a0) t[i++] = strdup(a0);
	if (a1) t[i++] = strdup(a1);
	if (a2) t[i++] = strdup(a2);
	if (a3) t[i++] = strdup(a3);
	t[i] = NULL;
	return (t);
}

static void	link_cmd(t_cmd *a, t_cmd *b) { a->next = b; }

static void	banner(const char *title)
{
	printf("\n=== %s ===\n", title);
	fflush(stdout);
}

static void	report(t_shell *sh)
{
	printf("[exit_status = %d]\n", sh->exit_status);
	fflush(stdout);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_cmd	*a, *b, *c, *d, *e;
	t_redir	*r;

	(void)argc; (void)argv;
	shell.env = env_init(envp);
	shell.exit_status = 0;
	shell.running = 1;
	shell.gc = NULL;
	if (!shell.env)
		return (fprintf(stderr, "env_init failed\n"), 1);

	banner("1 : commande introuvable");
	shell.exit_status = -1;
	c = mk_cmd(mk_args("commande_qui_existe_pas", NULL, NULL, NULL), NULL);
	handle_executor(&shell, c);
	report(&shell);

	banner("2 : fichier non executable (/etc/passwd)");
	shell.exit_status = -1;
	c = mk_cmd(mk_args("/etc/passwd", NULL, NULL, NULL), NULL);
	handle_executor(&shell, c);
	report(&shell);

	banner("3 : chemin absolu inexistant");
	shell.exit_status = -1;
	c = mk_cmd(mk_args("/usr/bin/zof_nimporte_quoi", NULL, NULL, NULL), NULL);
	handle_executor(&shell, c);
	report(&shell);

	banner("4 : redir input sur fichier inexistant");
	shell.exit_status = -1;
	r = mk_redir(TOK_REDIR_IN, "/tmp/__zof_inexistant__", NULL);
	c = mk_cmd(mk_args("cat", NULL, NULL, NULL), r);
	handle_executor(&shell, c);
	report(&shell);

	banner("5 : redir output dans /root (interdit)");
	shell.exit_status = -1;
	r = mk_redir(TOK_REDIR_OUT, "/root/zof_forbidden.txt", NULL);
	c = mk_cmd(mk_args("echo", "hi", NULL, NULL), r);
	handle_executor(&shell, c);
	report(&shell);

	banner("6 : ls sur dossier inexistant");
	shell.exit_status = -1;
	c = mk_cmd(mk_args("ls", "/dossier_inexistant_xyz", NULL, NULL), NULL);
	handle_executor(&shell, c);
	report(&shell);

	banner("7 : pipe avec commande introuvable au debut");
	shell.exit_status = -1;
	a = mk_cmd(mk_args("commande_inexistante", NULL, NULL, NULL), NULL);
	b = mk_cmd(mk_args("wc", "-l", NULL, NULL), NULL);
	link_cmd(a, b);
	handle_executor(&shell, a);
	report(&shell);

	banner("8 : pipeline 5 etages (echo abc | cat | cat | cat | wc -c)");
	shell.exit_status = -1;
	a = mk_cmd(mk_args("echo", "abc", NULL, NULL), NULL);
	b = mk_cmd(mk_args("cat", NULL, NULL, NULL), NULL);
	c = mk_cmd(mk_args("cat", NULL, NULL, NULL), NULL);
	d = mk_cmd(mk_args("cat", NULL, NULL, NULL), NULL);
	e = mk_cmd(mk_args("wc", "-c", NULL, NULL), NULL);
	link_cmd(a, b); link_cmd(b, c); link_cmd(c, d); link_cmd(d, e);
	handle_executor(&shell, a);
	report(&shell);

	banner("9 : echo sans argument");
	shell.exit_status = -1;
	c = mk_cmd(mk_args("echo", NULL, NULL, NULL), NULL);
	handle_executor(&shell, c);
	report(&shell);

	banner("10 : false | true (exit du DERNIER doit gagner)");
	shell.exit_status = -1;
	a = mk_cmd(mk_args("false", NULL, NULL, NULL), NULL);
	b = mk_cmd(mk_args("true", NULL, NULL, NULL), NULL);
	link_cmd(a, b);
	handle_executor(&shell, a);
	report(&shell);

	return (0);
}