/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 17:21:08 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/31 17:21:08 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "minishell.h"

/*
** Logical path = current $PWD + "/" + arg (or arg if absolute), WITHOUT
** resolving "." / ".." against the filesystem. Used as the new $PWD when
** getcwd() fails (deleted working directory), matching bash's behavior.
*/
char	*cd_curpath(t_shell *sh, const char *target)
{
	char	*base;
	char	*tmp;

	if (target && target[0] == '/')
		return (gc_strdup(sh, target));
	base = env_get(sh->env, "PWD");
	if (!base || !base[0])
		return (gc_strdup(sh, target));
	tmp = gc_strjoin(sh, base, "/");
	return (gc_strjoin(sh, tmp, target));
}
