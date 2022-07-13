/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:45:15 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/07/13 16:16:17 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	k;

	k.infile = NULL;
	k.outfile = NULL;
	k.envp = env;
	pipex(argc, argv, &k);
	return (0);
}
