*This project has been created as part of the 42 curriculum by azaytsev, schouite.*

---

# Minishell

A simplified reimplementation of `bash`. The binary prints a prompt, reads a line through `readline`, parses it into a pipeline of commands, runs them, and waits for the next line until `exit` or `Ctrl-D`.

---

## Description

The shell supports external commands resolved through `PATH`, built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`), input and output redirections (`<`, `>`, `>>`), heredocs (`<<`), pipes (`|`), expansion of environment variables and of `$?`, as well as single and double quotes. Unquoted expansions are field-split on whitespace, redirection targets that expand to zero or multiple words are rejected as ambiguous, and non-interactive input (pipes or files into stdin) is read without prompt pollution.

Written in C with the 42 norm. A single global variable is used, only to record the latest signal caught inside the handler.

The codebase is organized in pipeline stages.

| Stage | Files |
|---|---|
| Lexer | `src/lexer/` |
| Parser | `src/parser/` |
| Expander | `src/expander/` |
| Heredoc | `src/heredoc/` |
| Executor | `src/execution/` |
| Built-ins | `src/builtins/` |
| Garbage collector | `src/gc/` |
| Signals | `src/signals/` |
| Environment | `src/env/` |

Memory is managed by a per-line garbage collector. Every allocation registered through `gc_malloc` family is released by `gc_free` at the end of each line, so a leaking branch in one stage never escapes into the next prompt.

---

## Instructions

### Requirements

- `gcc` or `clang`
- GNU `make`
- `libreadline` with headers, `libreadline-dev` on Debian and Ubuntu, `readline` on macOS via Homebrew

### Compile

```bash
make
```

The default target builds the libft, then produces the `minishell` binary at the root of the repository.

Other targets.

```bash
make clean   # remove object files
make fclean  # remove objects and binary
make re      # full rebuild
```

### Run

```bash
./minishell
```

Examples.

```
minishell> echo hello | cat -e
hello$
minishell> echo $USER
azaytsev
minishell> cat << EOF > /tmp/note.txt
> contenu du heredoc
> EOF
minishell> echo $?
0
minishell> exit
```

`Ctrl-D` on an empty line exits the shell. `Ctrl-C` interrupts the current line and redraws the prompt. `Ctrl-\` is ignored at the prompt.

---

## Resources

### References

- [Bash manual, *GNU Bash Reference Manual*](https://www.gnu.org/software/bash/manual/) sections Shell Grammar, Redirections, Shell Expansions
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [GNU Readline documentation](https://tiswww.case.edu/php/chet/readline/readline.html)
- *Advanced Programming in the UNIX Environment*, W. Richard Stevens, chapters on process control, signals and I/O
- Manual pages `readline`, `signal`, `sigaction`, `fork`, `execve`, `pipe`, `dup2`, `wait`, `waitpid`, `getcwd`, `chdir`

### Reference implementations

- [mcombeau, minishell](https://github.com/mcombeau/minishell)
- [LucasKuhn, 42-minishell](https://github.com/LucasKuhn/42-minishell)
- [kichkiro, 42-minishell-tester](https://github.com/kichkiro/42-minishell-tester)

### AI usage

- **Design review**, validating the pipeline split (lexer, parser, expander, executor), the GC ownership boundary at `process_line`, and the redirection list model attached per command.
- **Defense preparation**, drafting walkthrough and Notion-ready handbook chapters, building scripts to normalize 42 headers and rename misspelled files, automating norminette cleanup against a long list of small violations.
- **Code review**, line-by-line review of pull requests before merge, used to flag missing NULL checks, leaks of GC chains across error paths, and norminette violations.
- **Drafting helper functions**, scaffolding small utilities like `gc_strjoin`, `gc_itoa`, the env sort for `export`, and the identifier validation rules. Every generated piece was rechecked against `norminette` and tested locally before commit.
- **README**, drafting and reviewing the structure of this file against the subject requirements.
