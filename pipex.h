/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:28:26 by amaroni           #+#    #+#             */
/*   Updated: 2021/12/11 14:52:27 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_list_pipex{
	struct s_list_pipex	*next;
	char				*content;
}		t_list_pipex;

typedef struct s_execve_date{
	char *cmd;
	char *tab[3];
} t_execve_data;

/* parser.c */
void	ft_free_2dtab(void **tab);
char	*ft_strcat_path_and_cmd(char *path, char *cmd);
char	*ft_return_cmd_absolute_path(char *cmd, char *path);

/* extract.c */
char	*ft_extract_envar_path(char **envp);
char	*ft_extract_cmd(char *arg);
char	*ft_extract_cmd_args(char *arg);

/* listpipex */
t_list_pipex	*ft_init_pipex_list(int argc, char **argv);
t_list_pipex	*ft_last_pipex_list(t_list_pipex *list);
t_list_pipex	*ft_new_pipex_list(char *content);
void			ft_delone_pipex_list(t_list_pipex *list);
void			ft_free_pipex_list(t_list_pipex **list);
void			ft_addback_pipex_list(t_list_pipex **alist, t_list_pipex *new);

/* execve */
void	ft_init_execve_data(t_execve_data *data);
t_execve_data	*ft_return_execve(char *cmd, char *cmd_args, char **envp);
void	ft_free_execve_data(t_execve_data *data);
#endif
