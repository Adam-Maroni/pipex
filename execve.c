/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:29:19 by amaroni           #+#    #+#             */
/*   Updated: 2021/12/17 12:53:26 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init_execve(t_execve *data)
{
	if (!data)
		return ;
	data->cmd = NULL;
	data->tab = NULL;
}

/*
 * cmd_all = cmd + cmd_args
 */
t_execve	*ft_return_execve(char *cmd_all, char **envp)
{
	t_execve	*rt;
	char		*cmd;
	char		*envar_path;

	if (!cmd_all || !envp)
		return (NULL);
	rt = (t_execve *)calloc(sizeof(*rt), 1);
	if (!rt)
		return (NULL);
	ft_init_execve(rt);
	cmd = ft_extract_cmd(cmd_all);
	envar_path = ft_extract_envar_path(envp);
	rt->cmd = ft_return_cmd_absolute_path(cmd, envar_path);
	free(cmd);
	rt->tab = ft_split(cmd_all, ' ');
	return (rt);
}

void	ft_free_execve(t_execve *data)
{
	size_t	i;

	if (!data)
		return ;
	i = 0;
	while (data->tab[i])
	{
		free(data->tab[i]);
		i++;
	}
	free(data->tab);
	free(data->cmd);
	free(data);
}
