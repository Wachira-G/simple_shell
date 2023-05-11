# simple_shell
# **0x16. C - Simple Shell**
# **Background Context**
Write a simple UNIX command interpreter.

# **GitHub**
**There should be one project repository per group. If you and your partner have a repository with the same name in both your accounts, you risk a 0% score. Add your partner as a collaborator.*

# **More Info**
## Output
 * Unless specified otherwise, your program must have the exact same output as `sh (/bin/sh)` as well as the exact same error output.
 * The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]` (See below)

Example of error with `sh`:

``` C
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```

Same error with your program `hsh`:

```C
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```

## Compilation
Your shell will be compiled this way:

```C
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

# **Tasks**

# 0. Betty would be proud
Write a beautiful code that passes the Betty checks

# 1. Simple shell 0.1

Write a UNIX command line interpreter.

* Usage: simple_shell

Your Shell should:

* Display a prompt and wait for the user to type a command. A command line always ends with a new line.
* The prompt is displayed again each time a command has been executed.
* The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
* The command lines are made only of one word. No arguments will be passed to programs.
* If an executable cannot be found, print an error message and display the prompt again.
* Handle errors.
* You have to handle the “end of file” condition (Ctrl+D)

You don’t have to:

* use the PATH
* implement built-ins
* handle special characters : ", ', `, \, *, &, #
* be able to move the cursor
* handle commands with arguments

*`execve` will be the core part of your Shell, don’t forget to pass the environ to it…*
