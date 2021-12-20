/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:28:26 by amaroni           #+#    #+#             */
/*   Updated: 2021/12/20 18:19:01 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "libft/libft.h"
# include <sys/wait.h>

typedef struct s_list_pipex{
	struct s_list_pipex	*next;
	char				*content;
}		t_list_pipex;

typedef struct s_execve{
	char	*cmd;
	char	**tab;
}	t_execve;

/* parser.c */
void		ft_free_2dtab(void **tab);
char		*ft_strcat_path_and_cmd(char *path, char *cmd);
char		*ft_return_cmd_absolute_path(char *cmd, char *path);

/* extract.c */
char		*ft_extract_envar_path(char **envp);
char		*ft_extract_cmd(char *arg);
char		*ft_extract_cmd_args(char *arg);

/* execve */
void		ft_init_execve(t_execve *data);
void		ft_free_execve(t_execve *data);
t_execve	*ft_return_execve(char *cmd_all, char **envp);

/* main.c */
void		ft_run_child_1(int fd, char **argv, int pipefd[2], char **envp);
void		ft_run_child_2(int fd, char **argv, int pipefd[2], char **envp);
int			ft_pipex(char **argv, char **envp);
int			main(int argc, char **argv, char **envp);
#endif
