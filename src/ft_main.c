/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"
#include <unistd.h>
/*
int	main(void)
{
    char *term;
	printf("Dentro da main\n");

    term = ttyname(0);
    printf("This is terminal %s\n",term);
	return (0);
}
*/
/*
#include <stdio.h>
#include <unistd.h>

int main() {
    char *pathname = "file.txt";
    if (access(pathname, F_OK) == 0) {
        printf("File exists\n");
    } else {
        printf("File does not exist\n");
    }
    if (access(pathname, R_OK) == 0) {
        printf("File is readable\n");
    } else {
        printf("File is not readable\n");
    }
    if (access(pathname, W_OK) == 0) {
        printf("File is writable\n");
    } else {
        printf("File is not writable\n");
    }
}
*/

/*
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
int main() {
    char *cwd;
    char buff[1024];

    cwd = getcwd(buff, 1024 + 1);
    if (cwd != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }
    char *dir = "/Users/woliveir/Desktop/";
    opendir(dir);
    #include <sys/types.h>
    printf("slot do tty atual %i\n",ttyslot());
    return 0;
}
*/
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void new_line_handler() {
    printf("New Line created\n");
}


int main(void)
{
    char *line;

    printf("Dentro da main\n");
    while (1)
    {
        line = NULL;
        line = readline("minishell: ");
        if (!line)
            printf("readline retornou nulo\n");
        else
        {
            printf("radline retornou um ponteiro\n");
            add_history(line);
        }
        printf("readline capturou: %s\n", line);
//        rl_clear_history(); //limpa o histórico de comandos armazenados na memória. 
//        rl_on_new_line = new_line_handler;
//    (*rl_on_new_line)(void); //chama uma 
        free(line);
    }
    line = NULL;
//    exit(EXIT_SUCCESS);
    return (0);
}