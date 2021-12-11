/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:53:56 by amaroni           #+#    #+#             */
/*   Updated: 2021/12/11 14:52:20 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Prend entree la commande et la string PATH,
 * supprime "PATH=" de cette string,
 * split la chaine obtenue,
 * concatene chaque chemin avec la commande
 * et determine le chemin absolue.
 */
void	ft_free_2dtab(void **tab)
{
	size_t	i;

	if (!tab)
		return ;
	if (!*tab)
		free(tab);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/*
 * Return the concatenation of path and cmd
 * with '/' as separator.
 */
char	*ft_strcat_path_and_cmd(char *path, char *cmd)
{
	size_t	len;
	char	*rt;

	if (!cmd || !path)
		return (NULL);
	len = ft_strlen(path) + ft_strlen(cmd) + 2;
	rt = (char *)ft_calloc(sizeof(char), len);
	if (!rt)
		return (NULL);
	ft_strlcpy(rt, path, ft_strlen(path) + 1);
	ft_strlcat(rt, "/", ft_strlen(rt) + 2);
	ft_strlcat(rt, cmd, ft_strlen(rt) + ft_strlen(cmd) + 1);
	return (rt);
}

/*
 * Return the binary path of a given command.
 */
char	*ft_return_cmd_absolute_path(char *cmd, char *path)
{
	char	**absolute_path;
	char	*pathless;
	size_t	i;
	char	*rt;

	if (!cmd || !path)
		return (NULL);
	rt = NULL;
	pathless = ft_substr(path, 5, ft_strlen(path) - 5 + 1);
	absolute_path = ft_split(pathless, ':');
	free(pathless);
	i = 0;
	while (absolute_path[i])
	{
		rt = ft_strcat_path_and_cmd(absolute_path[i], cmd);
		if (access(rt, F_OK) == 0)
			break ;
		if (rt)
			free(rt);
		i++;
	}
	ft_free_2dtab((void **)absolute_path);
	return (rt);
}
