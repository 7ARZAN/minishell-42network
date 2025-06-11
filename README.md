# TuringSenkuShell

![TuringSenkuShell Banner](https://img.shields.io/badge/TuringSenkuShell-v1.0-blueviolet?style=flat-square) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A lightweight, Norminette-compliant minishell written in C, inspired by the computational genius of **Alan Turing** and the scientific spirit of **Senku Ishigami** from *Dr. Stone*. TuringSenkuShell delivers a robust command-line interpreter with advanced features like command parsing, variable expansion, redirections, and heredoc support, all crafted with precision and efficiency.

## 🌟 Features

- **Command Parsing**: Splits complex input into commands and arguments, handling pipes (`|`) with error checking for invalid syntax.
- **Variable Expansion**: Supports environment variable expansion (e.g., `$VAR`) and exit status (`$?`), with proper heredoc delimiter handling.
- **Redirections**: Implements input (`<`), output (`>`), append (`>>`), and heredoc (`<<`) redirections with robust file management.
- **Quote Handling**: Strips single (`'`) and double (`"`) quotes accurately, preserving content within quoted strings.
- **Heredoc Support**: Processes heredoc input interactively, with optional variable expansion based on delimiter quoting.
- **Norminette Compliance**: Adheres to 42 school's strict coding standards, ensuring clean, maintainable, and well-structured code.
- **Error Handling**: Provides clear error messages for syntax errors, file access issues, and unclosed quotes.

## 🚀 Getting Started

### Prerequisites

- **C Compiler**: GCC or Clang
- **Make**: For building the project
- **Readline Library**: For interactive input (e.g., `libreadline-dev` on Debian-based systems)
- **Operating System**: Tested on Linux (Ubuntu/Debian) and macOS

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/7ARZAN/TuringSenkuShell.git
   cd TuringSenkuShell
   ```

2. Build the project:
   ```bash
   make
   ```

3. Run the shell:
   ```bash
   ./turingsenkushell
   ```

### Usage

Launch **TuringSenkuShell** and start typing commands:

```bash
$ ./turingsenkushell
> echo $USER
7ARZAN
> cat << EOF > output.txt
Hello, TuringSenkuShell!
EOF
> cat output.txt
Hello, TuringSenkuShell!
> ls | grep .c
variable_expansion.c  command_parser.c  argument_splitter.c
```

## 🛠️ Project Structure

```
TuringSenkuShell/
├── Makefile
├── README.md
├── builting
│   ├── ft_cd.c
│   ├── ft_echo.c
│   ├── ft_env.c
│   ├── ft_exit.c
│   ├── ft_export.c
│   ├── ft_pwd.c
│   └── ft_unset.c
├── execute_unit
│   ├── ft_dupenvp.c
│   ├── ft_execute.c
│   ├── ft_is_builting.c
│   ├── ft_pipe.c
│   ├── ft_redirection.c
│   ├── ft_search_path.c
│   └── ft_signal.c
├── include
│   ├── builting.h
│   ├── execute.h
│   ├── libft.h
│   ├── minishell.h
│   └── parser.h
├── main.c
└── parsing
    ├── argument_splitter.c
    ├── argument_utils.c
    ├── command_splitter.c
    ├── heredoc_handler.c
    ├── parser.c
    ├── quote_removal.c
    ├── redirection_utils.c
    ├── struct_cmd.c
    └── variable_expansion.c
```

## 💡 Inspiration

**TuringSenkuShell** is named after:
- **Alan Turing**, the pioneer of computer science, whose work on computation inspires the project's technical rigor.
- **Senku Ishigami** from *Dr. Stone*, a character who uses science to rebuild civilization, reflecting the project's innovative approach to shell design.

This fusion of computational legacy and anime energy captures the spirit of creating a powerful yet lightweight shell.

## 🧪 Testing

To test the shell, try these commands:

```bash
# Variable expansion
echo $HOME $?

# Redirection
ls -la > output.txt
cat < output.txt

# Heredoc
cat << END
Type multiple lines
END

# Pipes
ls -l | grep .c | wc -l
```

For automated testing, create a script with sample inputs and compare outputs to Bash.

## 📜 License

This project is licensed under the [MIT License](LICENSE).

## 🙌 Acknowledgments

- **42 School**: For the minishell project inspiration and Norminette standards.
- **Dr. Stone**: For Senku’s scientific passion that fueled the project’s creative naming.
- **Contributors**: Thanks to [yel-hadr](https://github.com/yel-hadr) and collaborators for building this shell.

## 📞 Contact

Have questions or suggestions? Reach out to [7ARZAN](mailto:elakhfif@student.1337.ma) or open an issue on GitHub.

---

*“The power of science—and a good shell—can change the world!”*  
— Inspired by Senku Ishigami, powered by TuringSenkuShell