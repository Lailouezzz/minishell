# Introduction

[Minishell](#minishell) is a project from the cursus of the school 42 (campus of Le Havre).

The goal of this project is to make a rather simple shell. See the list of [features](#features) down below.

---
# Dependencies

## List

- [Microparser](#microparser)

### Microparser

This project uses [microparser](https://github.com/Lailouezzz/microparser), a home made `LR` / `LALR` / `SLR` parser made by [ale-boud](https://github.com/lailouezzz).

---
# Minishell

## Build

Commands to build minishell :

```sh
git clone --recurse-submodules https://github.com/Lailouezzz/minishell
cd minishell
./configure.sh && make
```

## Features

- [ ] `Prompt` when waiting for a new command
- [ ] Working `history`
- [ ] Search and launch the right executable (based on the `PATH` variable or using a
relative or an absolute path).
- [ ] Not interpret unclosed quotes or special characters which are not required by the
subject such as `\` (backslash) or `;` (semicolon)
- [ ] `’` (single quote) should prevent the shell from interpreting the meta-
characters in the quoted sequence
- [ ] `"` (double quote) should prevent the shell from interpreting the meta-
characters in the quoted sequence except for `$` (dollar sign)
- [ ] Redirections
	- [ ] `<` redirects input
	- [ ] `>` redirects output
	- [ ] `<< [DELIMITER]` reads the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history
	- [ ] `>>` redirects output in append mode
- [ ] Pipes (`|` character). The output of each command in the pipeline is
connected to the input of the next command via a pipe
- [ ] Environment variables (`$` followed by a sequence of characters) which
should expand to their values
- [ ] `$?` which should expand to the exit status of the most recently executed
foreground pipeline
- [ ] `Ctrl-C`, `Ctrl-D` and `Ctrl-\` which should behave like in bash
- [ ] Interactive mode
	- [ ] `Ctrl-C` displays a new `prompt` on a new line
	- [ ] `Ctrl-D` exits the shell
	- [ ] `Ctrl-\` does nothing
- [ ] Builtins
	- `echo` with option -n
	- [ ] `cd` with only a relative or absolute path
	- [ ] `pwd` with no options
	- [ ] `export` with no options
	- [ ] `unset` with no options
	- [ ] `env` with no options or arguments
	- [ ] `exit` with no option
- [ ] Command chaining (`&&` and `||`)
- [ ] Subshell with `(COMMAND)`
- [ ] Wildcard (`*` character) for the current working directory

## Todo

- Pass the norminette
- Doxygen documentation
- Refactor the source tree
- A fully handled grammar and AST for minishell expressions
- A working lexer for minishell expressions
- AST execution

---
# Authors

<table>
	<tr>
		<td> <img style="width:80px;height:80px;" src="https://avatars.githubusercontent.com/u/25978607?v=4"> </td>
		<td> <img style="width:80px;height:80px;" src="https://avatars.githubusercontent.com/u/37182076?v=4"> </td>
	</tr>
	<tr>
		<td style="text-align:center"> <a href="https://github.com/lailouezzz">ale-boud</a> </td>
		<td style="text-align:center"> <a href="https://github.com/Dyamen1411">ale-boud</a> </td>
	</tr>
</table>
