/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:51:22 by amaroni           #+#    #+#             */
/*   Updated: 2021/12/14 09:19:47 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int pipefd[2];
	int pid;
	int pid2;
	int fd;
	int fd2;
	t_execve_data *data;

	if (argc != 5)
	{
		printf("Error\n");
		return (1);
	}
	if (pipe(pipefd) == -1)
		return (2);
	pid = fork();
	if (pid == -1)
		return (3);
	if (pid == 0)
	{
		fd = open("inFile", O_RDWR, 0777);
		dup2(fd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		data = ft_return_execve(argv[2], envp);
		execve(data->cmd, data->tab, envp);
		close(fd);
		close(pipefd[1]);
		close(pipefd[0]);
		ft_free_execve_data(data);
	}
	close(pipefd[1]);
	pid2 = fork();
	if (pid2 == -1)
		return (4);
	if (pid2 == 0)
	{
		fd2 = open("outFile", O_RDWR, 0777);
		dup2(fd2, STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		data = ft_return_execve(argv[3], envp);
		execve(data->cmd, data->tab, envp);
		close(fd2);
		close(pipefd[1]);
		close(pipefd[0]);
		ft_free_execve_data(data);
	}
	close(pipefd[0]);
	wait(&pid);
	wait(&pid2);
	return (0);
}
