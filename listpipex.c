/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listpipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:11:29 by amaroni           #+#    #+#             */
/*   Updated: 2021/12/13 18:35:09 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * This function initliaze the list
 * based on arguments inserted as program's input.
 */
t_list_pipex	*ft_init_pipex_list(int argc, char **argv)
{
	t_list_pipex	*list;
	size_t			i;

	if (!argv || argc < 2)
		return (NULL);
	list = NULL;
	i = 2;
	while ((int)i < argc - 1)
	{
		ft_addback_pipex_list(&list, ft_new_pipex_list(argv[i]));
		if ((int)i < argc - 2)
			ft_addback_pipex_list(&list, ft_new_pipex_list("|"));
		i++;
	}
	return (list);
}

void	ft_delone_pipex_list(t_list_pipex *list)
{
	free(list->content);
	free(list);
}

void	ft_free_pipex_list(t_list_pipex **list)
{
	t_list_pipex	*current;
	t_list_pipex	*previous;

	previous = (*list)->next;
	while (previous)
	{
		current = previous->next;
		ft_delone_pipex_list(previous);
		previous = current;
	}
	ft_delone_pipex_list(*list);
	(*list) = NULL;
}

void	ft_addback_pipex_list(t_list_pipex **alist, t_list_pipex *new)
{
	t_list_pipex	*list;

	list = ft_last_pipex_list(*alist);
	if (!list)
		*alist = new;
	else
		list->next = new;
	new->next = NULL;
}

t_list_pipex	*ft_last_pipex_list(t_list_pipex *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

t_list_pipex	*ft_new_pipex_list(char *content)
{
	t_list_pipex	*new;

	new = (t_list_pipex *)malloc(sizeof(t_list_pipex));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->next = NULL;
	return (new);
}
