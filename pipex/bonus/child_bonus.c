/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:14:12 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/06/25 17:14:15 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static void	sub_dup2(int zero, int first)
{
	if (zero >= 0)
		dup2(zero, 0);
	if (first >= 0)
		dup2(first, 1);
}

void	child(t_ppxb p, char **argv, char **envp)
{
	p.pid = fork();
	if (!p.pid)
	{
		if (p.idx == 0)
			sub_dup2(p.infile, p.pipe[1]);
		else if (p.idx == p.cmd_nmbs - 1)
			sub_dup2(p.pipe[2 * p.idx - 2], p.outfile);
		else
			sub_dup2(p.pipe[2 * p.idx - 2], p.pipe[2 * p.idx + 1]);
		close_pipes(&p);
		p.cmd_args = ft_split(argv[1 + p.here_doc + p.idx], ' ');
		p.cmd = get_cmd(p.cmd_paths, p.cmd_args[0]);
		if (!p.cmd)
		{
			msg_pipe(p.cmd_args[0]);
			child_free(&p);
			exit(1);
		}
		execve(p.cmd, p.cmd_args, envp);
	}
}