// Simulate ping -c 5 google.com | grep rtt

/*
#include "pipex.h"

int main(int argc, char **argv , char **envp)
{
	int fd[2];
	if (pipe(fd) == -1)
		return (1);

	int pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		char *tab[5];
		tab[0] = "ping";
		tab[1] = "-c";
		tab[2] = "5";
		tab[3] = "google.com";
		tab[4] = NULL;

		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);//We don't use it.
		close(fd[1]);
		execve("/usr/bin/ping",tab,envp);
	}

	int pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}

	if (fd[0])
		close(fd[0]);
	if (fd[1])
		close(fd[1]);

	wait(&pid1);
	wait(&pid2);
	return (0);
}


*/
