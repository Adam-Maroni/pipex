/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:51:22 by amaroni           #+#    #+#             */
/*   Updated: 2021/12/13 18:48:35 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd1;
	int		fd2;
	t_list_pipex	*list;
	t_execve_data	*data;

	fd1 = open(argv[1], O_RDWR);
	fd2 = open(argv[argc - 1], O_RDWR);
	if (argc != 5 || fd1 == -1 || fd2 == -1)
	{
		printf("Error\n");
		return (-1);
	}
	list = ft_init_pipex_list(argc, argv);
	data = ft_return_execve(list->content, envp);
	ft_free_execve_data(data);
	ft_free_pipex_list(&list);
	close(fd1);
	close(fd2);
	return (0);
}
