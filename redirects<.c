#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

//frankshell -> git checkout 9618ff1f548b86be2cceb6793baf719a6e470632
int main()
{
	// int fd[2];
	int file = open("t.heredocs", O_RDONLY, 0777);
	int to_create = open("1", O_WRONLY | O_CREAT | O_TRUNC, 0777);

	// if (pipe(fd) < 0) return 1;

	int pid1 = fork();
	if (pid1 < 0)
		return 1;
	if (pid1 == 0) {
		// dup2(to_create, STDOUT_FILENO); // cancelar o proprio stdout
		dup2(file, STDIN_FILENO);
		// close(fd[0]);
		// close(fd[1]);
		execlp("cat", "cat", NULL);
	}

	waitpid(pid1, NULL, 0);
	return 0;
}
