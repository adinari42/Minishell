# Minishell

Minishell is a simple shell implementation that serves as your own little bash. This project provides an opportunity to learn about processes and file descriptors while creating a functional shell. With Minishell, you'll be able to execute commands, handle redirections, implement pipes, work with environment variables, and more.

## Features

Minishell offers the following features:

- **Command Prompt**: The shell displays a prompt where you can enter commands and receive output.

- **Command History**: Minishell keeps track of previously entered commands, allowing you to easily access and execute them again.

- **Executable Search**: The shell can search for and launch the appropriate executable file based on the PATH variable or by using a relative or absolute path.

- **Minimal Global Variables**: Minishell is designed to minimize the use of global variables. This approach encourages a cleaner and more modular code structure.

- **Quoting**: Unclosed quotes and special characters that are not required by the subject, such as backslashes or semicolons, are not interpreted by the shell.

- **Handling Single Quotes**: Minishell properly handles single quotes ('), preventing the interpretation of metacharacters within the quoted sequence.

- **Handling Double Quotes**: Double quotes (") are handled by the shell, preventing the interpretation of metacharacters within the quoted sequence, except for the dollar sign ($).

- **Redirections**: Minishell supports input and output redirection using the following symbols:
  - `<` redirects input.
  - `>` redirects output.
  - `<<` followed by a delimiter reads input until a line containing the delimiter is encountered (history is not updated).
  - `>>` redirects output in append mode.

- **Pipes**: The shell supports pipes (|) to connect the output of one command to the input of the next command in a pipeline.

- **Environment Variables**: Minishell handles environment variables, allowing you to use the $ symbol followed by a sequence of characters to expand them to their corresponding values.

- **$? Expansion**: The shell handles the `$?` expansion, which represents the exit status of the most recently executed foreground pipeline.

- **Signal Handling**: Minishell handles the following signals, replicating their behavior in bash:
  - `ctrl-C`: Displays a new prompt on a new line.
  - `ctrl-D`: Exits the shell.
  - `ctrl-\`: No specific action.

- **Built-in Commands**: The shell implements the following built-in commands:
  - `echo`: Supports the `-n` option.
  - `cd`: Handles relative or absolute paths.
  - `pwd`: Displays the current working directory.
  - `export`: Allows you to set environment variables.
  - `unset`: Allows you to unset environment variables.
  - `env`: Displays the environment variables.
  - `exit`: Exits the shell.

## Getting Started

To get started with Minishell, follow these steps:

1. Clone the repository: `git clone <repository_url>`
2. Compile the code: `make`
3. Run Minishell: `./minishell`

## Contributions

Contributions to Minishell are welcome! If you have any improvements, bug fixes, or new features to contribute, please do so!

