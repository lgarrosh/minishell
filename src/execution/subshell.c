/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:05:16 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/13 16:01:25 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execsubshell(t_ll_elem *cmd, t_info *info, t_fd *fd)
{
	int		pid;

	if (info->envp_f)
	{
		ft_free_char2dem(info->envp, -1);
		info->envp = ft_compose_envp(info->envp_list);
		if (NULL == info->envp)
			return (ft_error(-1, "minishell: ft_execve: compose_envp", 1, 0));
		info->envp_f = 0;
	}
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid > 0)
		return (pid);
	if (remap_fds(fd->fds[0], fd->fds[1]))
		return (-1);
	close(fd->pfd[0]);
	parse(cmd->key, info);
	exit(g_exit);
}

int	ft_subshell(t_group *cmds, t_info *info)
{
	t_fd	fd;
	int		pid;

	fd.pfd[0] = -1;
	fd.fds[0] = get_in_fd(cmds->cmds->head->val);
	if (fd.fds[0] == -1)
		return (ft_error(-1, "minishell: subshell: get_in_fd", 1, 0));
	fd.fds[1] = get_out_fd(cmds->cmds->head->val);
	if (fd.fds[1] == -1)
		return (ft_error(-1, "minishell: subshell: get_out_fd", 1, 0));
	pid = ft_execsubshell(cmds->cmds->head, info, &fd);
	if (fd.fds[0] != STDIN_FILENO)
		close(fd.fds[0]);
	if (fd.fds[1] != STDOUT_FILENO)
		close(fd.fds[1]);
	return (pid);
}
