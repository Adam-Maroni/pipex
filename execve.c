/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:29:19 by amaroni           #+#    #+#             */
/*   Updated: 2021/12/11 14:50:26 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init_execve_data(t_execve_data *data)
{
	if (!data)
		return ;
	data->cmd = NULL;
	data->tab[0] = NULL;
	data->tab[1] = NULL;
	data->tab[2] = NULL;
}

t_execve_data	*ft_return_execve(char *cmd, char *cmd_args, char **envp)
{
	t_execve_data	*rt;
	size_t			i;

	if (!cmd || !envp)
		return (NULL);
	rt = (t_execve_data *)calloc(sizeof(*rt), 1);
	if (!rt)
		return (NULL);
	ft_init_execve_data(rt);
	rt->cmd = ft_return_cmd_absolute_path(cmd,
			ft_extract_envar_path(envp));
	rt->tab[0] = ft_strdup(cmd);
	i = 1;
	if (cmd_args)
	{
		rt->tab[i] = ft_strdup(cmd_args);
		i++;
	}
	return (rt);
}

void	ft_free_execve_data(t_execve_data *data)
{
	if (!data)
		return ;
	if (data->cmd)
		free(data->cmd);
	if (data->tab[0])
		free(data->tab[0]);
	if (data->tab[1])
		free(data->tab[1]);
	if (data->tab[2])
		free(data->tab[2]);
	free(data);
}
