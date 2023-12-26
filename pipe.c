#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

//frankshell -> git checkout 9618ff1f548b86be2cceb6793baf719a6e470632
int main()
{
	int fd[2];
	int stdout2 = STDOUT_FILENO;
	int stdin2 = STDIN_FILENO;
	int file = open("teste.txt", O_WRONLY | O_CREAT, 0777);

	if (pipe(fd) < 0) return 1;

	// se nao tem |
	// stdout2 = -1; // para que o stdout nao seja alterado pelo dup2

	// se tem > || >>
	// close(fd[1]); fd[1] = file; //fechar para evitar leaks, e fd[1](writer do pipe) fique igual ao fd do arquivo recebido apos >>

	int pid1 = fork();
	if (pid1 < 0)
		return 1;
	if (pid1 == 0) {
		dup2(fd[1], stdout2); // cancelar o proprio stdout
		close(fd[0]);
		close(fd[1]);
		// execlp("echo", "echo", "-c", "2", "google.com", NULL);
		execlp("ping", "ping", "google.com", NULL);
	}

	// se nao tem |
	// close(fd[0]);close(fd[1]);waitpid(pid2, NULL, 0);waitpid(pid1, NULL, 0); return (0); // fechar tudo para evitar o pipe.

	
	// int fd2[2];
	// if (pipe(fd2) < 0)
	// 	return 1;

	int pid2 = fork();
	if (pid2 < 0)
		return 1;
	if (pid2 == 0) {
		dup2(fd[0], stdin2); // cancelar o proprio stdin e aceitar o do comando anterior
		// dup2(fd2[1], stdout2); // cancelar o proprio stdout

		close(fd[0]);
		close(fd[1]);

		// close(fd2[0]);
		// close(fd2[1]);

		execlp("echo", "echo", "rtt", NULL);
	}

	close(fd[0]);
	close(fd[1]);
	// se nao tem |
	// close(fd2[0]);close(fd2[1]);waitpid(pid1, NULL, 0);waitpid(pid2, NULL, 0); return (0); // fechar tudo para evitar o pipe.

	

	// int pid3 = fork();
	// if (pid3 < 0)
	// 	return 1;
	// if (pid3 == 0) {
	// 	dup2(fd2[0], stdin2); // cancelar o proprio stdin e aceitar o do comando anterior

	// 	close(fd2[0]);
	// 	close(fd2[1]);

	// 	printf("wc -l: \n");
	// 	execlp("wc", "wc", "-l", NULL);
	// }


	// close(fd2[0]);
	// close(fd2[1]);
// waitpid(pid1, NULL, 0);
waitpid(pid2, NULL, 0);
	
	return 0;
}
