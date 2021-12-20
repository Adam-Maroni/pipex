/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:51:22 by amaroni           #+#    #+#             */
/*   Updated: 2021/12/20 18:32:37 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_run_child_1(int fd, char **argv, int pipefd[2], char **envp)
{
	t_execve	*data;

	data = NULL;
	if (fd == -1)
	{
		perror(argv[1]);
		exit(127);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	data = ft_return_execve(argv[2], envp);
	if (!data || !data->cmd || !data->tab
		|| execve(data->cmd, data->tab, envp) == -1)
	{
		close(pipefd[1]);
		ft_free_execve(data);
		fprintf(stderr, "%s: command not found\n", argv[2]);
		exit(127);
	}
	close(pipefd[1]);
	ft_free_execve(data);
}

void	ft_run_child_2(int fd, char **argv, int pipefd[2], char **envp)
{
	t_execve	*data;

	data = NULL;
	if (fd == -1)
	{
		perror(argv[4]);
		close(pipefd[0]);
		ft_free_execve(data);
		exit(127);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(pipefd[0], STDIN_FILENO);
	data = ft_return_execve(argv[3], envp);
	if (!data || !data->cmd || !data->tab
		|| execve(data->cmd, data->tab, envp) == -1)
	{
		close(pipefd[0]);
		ft_free_execve(data);
		fprintf(stderr, "%s: command not found\n", argv[3]);
		exit(127);
	}
	close(pipefd[0]);
	ft_free_execve(data);
}

int	ft_pipex(char **argv, char **envp)
{
	int	pipefd[2];
	int	pid;
	int	pid2;

	if (pipe(pipefd) == -1)
		return (2);
	pid = fork();
	if (pid == -1)
		return (3);
	if (pid == 0)
		ft_run_child_1(open(argv[1], O_RDWR, 0777),
			argv, pipefd, envp);
	close(pipefd[1]);
	pid2 = fork();
	if (pid2 == -1)
		return (5);
	if (pid2 == 0)
		ft_run_child_2(open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777),
			argv, pipefd, envp);
	close(pipefd[0]);
	wait(&pid);
	wait(&pid2);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		printf("Error, not right number of arguments\n");
		return (127);
	}
	else
		return (ft_pipex(argv, envp));
	return (0);
}
