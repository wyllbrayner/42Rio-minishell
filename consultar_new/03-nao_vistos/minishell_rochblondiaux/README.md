## TODO:
* Handle ’ (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.
* Handle " (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign).
* << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!

## BUGS:
Redirection & Appender
```bash
➜ >> a cat LICENSE.md
Command not found!
➜ cat >> a LICENSE.md
➜ cat > a LICENSE.md
```

ENV var
```bash
➜  minishell git:(main) ✗ unset truc
➜  minishell git:(main) ✗ 12=machin
➜  minishell git:(main) ✗ echo $&é
[1] 6602
$
[1]  + 6602 done       echo $
zsh: command not found: é
➜  minishell git:(main) ✗ echo $12
machin
➜  minishell git:(main) ✗ export 12
export: not an identifier: 12
➜  minishell git:(main) ✗ unset 12
➜  minishell git:(main) ✗ test=aaa
➜  minishell git:(main) ✗ echo %test%
%test%
➜  minishell git:(main) ✗ echo %HOME%
%HOME%
➜  minishell git:(main) ✗ export 12=machin
export: not an identifier: 12
➜  minishell git:(main) ✗ echo $12
machin
➜  minishell git:(main) ✗ unset 12
➜  minishell git:(main) ✗ 

```


## IN PROGRESS:

## DONE
* Implement pipes (| character). The output of each command in the pipeline is
  connected to the input of the next command via a pipe.
* Handle $? which should expand to the exit status of the most recently executed
  foreground pipeline.
* < should redirect input.
* Display a prompt when waiting for a new command.
* Have a working history.
* Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).
* Not use more than one global variable. Think about it. You will have to explain
its purpose. (I used it in controls/controls_handler.c)
* Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
  * In interactive mode:
  * ctrl-C displays a new prompt on a new line.
  * ctrl-D exits the shell.
  * ctrl-\ does nothing.
* echo with option -n
* cd with only a relative or absolute path
* pwd with no options
* exit with no options
* Handle environment variables ($ followed by a sequence of characters) which
    should expand to their values.
* Not interpret unclosed quotes or special characters which are not required by the
  subject such as \ (backslash) or ; (semicolon).
* Parser don't support duplicated commands in a single line. (example: cat License.md && cat License.txt)
* export with no options
* unset with no options
* env with no options or arguments
* FIX cd command, it doesn't work properly, example:
```bash
➜ cd /var/www
➜ pwd
/var/www/
➜ cd .git
➜ pwd
.git/
```
* \>> should redirect output in append mode.
* \> should redirect output.
