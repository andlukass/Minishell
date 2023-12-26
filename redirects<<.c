#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <readline/readline.h>
#include <readline/history.h>

int	ft_strlen(const char *s)
{
	int	index;

	if (!s)
		return (0);
	index = 0;
	while ((s[index] != '\0'))
		index++;
	return (index);
}

char	*ft_strjoin(char *s1, char *s2, int is_free)
{
	char	*newstr;
	int		index;
	int		length;

	if (!s1 && is_free)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	newstr = (char *) malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1)
			* sizeof(char));
	if (newstr == (void *)0)
		return ((void *)0);
	index = 0;
	length = -1;
	while (s1[++length])
		newstr[length] = s1[length];
	while (s2 && s2[index])
		newstr[length++] = s2[index++];
	if (is_free)
		free(s1);
	newstr[length] = '\0';
	return (newstr);
}

static void	do_heredocs(void)
{
	const char *terminator = "EOF";
	char *input;
	char *text;

	while (1) {
		input = readline("> ");
		// Verifica se a entrada é nula (geralmente indica Ctrl+D)
		if (input == NULL) {
			printf("wanted terminador: '%s'.\n", terminator);
			break ;
		}
		if (strcmp(input, terminator) == 0) {
			free(input);
			break ;
		}
		text = ft_strjoin(text, input, 1);
		text = ft_strjoin(text, "\n", 1);
		free(input);
	}
	printf("\n%s\n", text);
	free(text);
}

int main() {

	do_heredocs();

	return 0;
}
