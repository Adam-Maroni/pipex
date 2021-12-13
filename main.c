/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:51:22 by amaroni           #+#    #+#             */
/*   Updated: 2021/12/13 19:53:27 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_list_pipex	*list;
	int pipefd[2];

	if (argc != 5)
	{
		printf("Error\n");
		return (1);
	}
	list = ft_init_pipex_list(argc, argv);

	int pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
	{
		int fd1 = open(argv[1], O_RDWR, 0777);
		if (fd1 < 0)
			return (3);
		t_execve_data *data = ft_return_execve(list->content, envp);
		dup2(fd1, STDIN_FILENO);
		close (fd1);
		dup2(pipefd[1], STDOUT_FILENO);
		execve(data->cmd, data->tab, envp);
		ft_free_execve_data(data);
	}
	int pid2 = fork();
	if (pid2 == -1)
		return (4);
	if (pid2 == 0)
	{
		int fd2 = open(argv[argc - 1], O_RDWR);
		if (fd2 < 0)
			return (5);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		dup2(fd2, STDOUT_FILENO);
		t_execve_data *data = ft_return_execve(list->next->content, envp);
		execve(data->cmd, data->tab, envp);
		//ft_free_execve_data(data);
	}
	wait(&pid);
	wait(&pid2);
	ft_free_pipex_list(&list);
	return (0);
}
