#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

int main() {
	char *input;

	while (1) {
		input = readline("shelloko> ");
		
		if (input == NULL) {
			break;
		}

		if (strcmp(input, "exit") == 0) {
			printf("exit\n");
			free(input);
			break;
		}

		printf("You entered: %s\n", input);
		free(input);
	}

	return 0;
}

// compile with -lreadline flag