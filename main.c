/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:51:22 by amaroni           #+#    #+#             */
/*   Updated: 2021/12/17 11:32:37 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_input_okay(int argc, char **argv, char **envp)
{
	int		i;
	int		rt;
	char	*cmd;
	char	*cmd_full_path;

	i = 2;
	cmd = NULL;
	cmd_full_path = NULL;
	rt = 1;
	if (argc != 5 || access(argv[1], F_OK) == -1)
		return (0);
	while (i < argc - 1)
	{
		cmd = ft_extract_cmd(argv[i]);
		cmd_full_path = ft_return_cmd_absolute_path(cmd,
				ft_extract_envar_path(envp));
		if (access(cmd_full_path, F_OK) == -1)
			rt = 0;
		free(cmd);
		free(cmd_full_path);
		i++;
	}
	return (rt);
}

void	ft_run_child_1(int fd, char **argv, int pipefd[2], char **envp)
{
	t_execve_data	*data;

	data = NULL;
	if (fd == -1)
		exit(1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	data = ft_return_execve(argv[2], envp);
	execve(data->cmd, data->tab, envp);
	close(pipefd[1]);
	ft_free_execve_data(data);
}

void	ft_run_child_2(int fd, char **argv, int pipefd[2], char **envp)
{
	t_execve_data	*data;

	data = NULL;
	if (fd == -1)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(pipefd[0], STDIN_FILENO);
	data = ft_return_execve(argv[3], envp);
	execve(data->cmd, data->tab, envp);
	close(pipefd[0]);
	ft_free_execve_data(data);
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
		ft_run_child_1(open(argv[1], O_CREAT | O_RDWR, 0777),
			argv, pipefd, envp);
	close(pipefd[1]);
	pid2 = fork();
	if (pid2 == -1)
		return (5);
	if (pid2 == 0)
		ft_run_child_2(open(argv[4], O_CREAT | O_RDWR, 0777),
			argv, pipefd, envp);
	close(pipefd[0]);
	wait(&pid);
	wait(&pid2);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	rt;

	if (ft_is_input_okay(argc, argv, envp) == 0)
		rt = 1;
	else
		rt = ft_pipex(argv, envp);
	if (rt != 0)
		printf("Error\n");
	return (rt);
}
