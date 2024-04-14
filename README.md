# Minishell
Minishell is a 42 project designed to mimic Bash, the Unix shell. The goal is to provide a simplified version of a shell, introducing the internal mechanisms of a command-line interface (CLI). In this project, we apply our knowledge of the C programming language to implement various features of a shell, such as command execution, input/output redirection, and support for pipelines. Minishell serves as a comprehensive exercise, requiring extensive testing due to its numerous potential variations and edge cases.

We divided our shell implementation into four parts:
## Lexer
The lexer is where we make all the modifications to the input string needed by our program. For example, change all the '|' characters that are not quoted, to the special character '\3'. This allows us to  differentiate a '|' that is part of a string, from a real pipe used to separete commands. Last but not least, we do all the verifications, looking for invalid redirections, double '|', or any other invalid command. 

## Expander
Now that we have an input without invalid comands, and correctly modified, we search for the characther '$', which in shells, is used to access system variables. In this part, we verify if it is a valid variable name, and replace occurrences of "$someting" with the value of the variable.

## Parser
In the parser, we are going to create our structure, which end up being a linked list, allowing us to store different variables in each node easly. Here we separate the input into commands using the '\3' character. Then, for each command, we use the others specials characters left by the lexer, to identify all the redirections, heredocs and file names passed in the input. After this part, we have a linked list, with all the details of a command in each node, making it easy to navigate through all the commands and access their information when needed.

## Executer
With all the preprocessing done, we proceed to execute our commands. For each command, we search for it in the PATH, to determine wether it is a valid command or not. If it is valid, we fork a proccess, to run a instance of the exceve function executing the program passed in the command. We also manage the file descriptors, using a PIPE, to redirect the output of this proccess to a file, to the terminal interface, or even to the next command.

### More
Despite all that, there are a few more things: We have to setup a prompt line, which have a history of the commands already runned; we modified the SIGNAL  handling so that when the user presses CTRL+C, for example, they are prompted again rather than abruptly ending the program; we need to implement our own built-in functions, that should run natively within our shell. For example, we should handle commands like cd and pwd, besides that, all the export and unset calls should be handled within our shell.

### Cool feature
You can change the color of the prompt by running the program with the flag "--color <color>". You can run it with: pink, green, red, blue, yellow and white, fell free to test it :).
