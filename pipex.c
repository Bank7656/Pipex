/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:54:53 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/22 14:56:28 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

pid_t    ft_fork(void);
char    *ft_join_path(char **path, char *prog);
t_arg_lst *ft_check_argv(char **argv);
void    create_lst(t_arg_lst **lst, char *str);
char **ft_check_envp(char **envp);

int main(int argc, char *argv[], char *envp[])
{
    t_arg_lst   *lst;
    char    **env_path;

    if (argc != 5)
        return (1);
     
    lst = ft_check_argv(argv);
    env_path = ft_check_envp(envp);
    
    /* Print Env */
    // while (env_path[i] != NULL)
    // {
    //     printf("%s\n", env_path[i]);
    //     i++;
    // }
    int input_fd;

    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1)
    {
        printf("File does not exist\n");
        //free....
        return (1);
    }

    int i;
    pid_t pid;
    int previous_output;
    char    *program_path;
    int pipe_fd[PIPE_NUM];
    t_arg_lst   *cmd_trav;

    cmd_trav = lst;
    
    dup2(input_fd, STDIN_FILENO);

    i = 0;
    while (i < PROCESS_NUM)
    {   
        if (pipe(pipe_fd) == -1)    
            perror("Pipe()");

        pid = ft_fork();
        if (pid == 0) // Child process
        {
            if (i > 0)
            {
                if (dup2(previous_output, STDIN_FILENO) == -1)
                    perror("dup2()");
            }
            close(pipe_fd[0]);
            program_path = ft_join_path(env_path, cmd_trav -> str[0]);
            if (i == PROCESS_NUM -1)
            {
                int output_fd = open(argv[4], O_WRONLY | O_CREAT, 0644);
                if (output_fd == -1)
                    perror("Open()");
                if (dup2(output_fd, STDOUT_FILENO) == -1)
                    perror("dup2()");
                close(output_fd);
            }
            else
            {
                if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
                    perror("dup2()");
            }
            close(pipe_fd[1]);
            // close(previous_output);
            if (execve(program_path, cmd_trav -> str, envp) == -1)
                perror("execve()");
        }
        else// Parent process
        {
            wait(NULL);
            close(pipe_fd[1]);
            if (i > 0)
                close(previous_output);
            if (i < PROCESS_NUM - 1)
            {
                previous_output = dup(pipe_fd[0]);
                close(pipe_fd[0]);
            }
            cmd_trav = cmd_trav -> next;
            i++;  
        }
    }
    return (0);
    

    // int     count = 1;
    // char    *program_path;
    // pid_t   pid;
    // int     wait_return;
    // int     status;
    // t_arg_lst   *cmd_trav;

    // int u[PROCESS_NUM][PIPE_NUM];

    // cmd_trav = lst;

    // dup2(lst -> input_fd, STDIN_FILENO);
    
    // int i;
    
    // i = 0;
    // while (cmd_trav != NULL)
    // {
    //     if (pipe(lst -> pfd) == -1)
    //     {
    //         printf("Pipe failed\n");
    //         exit(0);
    //     }
    //     pid = ft_fork();
    //     if (pid == 0)
    //     {
    //         dup2(lst -> pfd[0], lst -> input_fd);
    //         printf("Child process %i start\n", count++);
    //         program_path = ft_join_path(env_path, cmd_trav -> str[0]);
    //         printf("Correct path: %s\n", program_path);
    //         // ft_execution();
    //         if (cmd_trav -> next != NULL)
    //             cmd_trav -> next -> input_fd = lst -> pfd[0];
    //         if (dup2(lst -> pfd[1], STDOUT_FILENO) == -1)
    //                 printf("Dup2 error");          
    //         close(lst -> pfd[0]);
    //         if (execve(program_path, cmd_trav -> str, envp) == -1)
    //             perror("execve()");
    //     }
    //     wait(NULL);
    //     // break;
    //     // cmd_trav = cmd_trav -> next;
    //     //break;
    // }
    // lst -> output_fd = open(argv[4], O_WRONLY | O_CREAT, 0644);
    // if (lst -> output_fd == -1)
    //     printf("Create Error\n");
    // printf("Create outfile\n");
    // dup2(lst -> output_fd, STDOUT_FILENO);
    
    /* Print command argv */
    // t_arg_lst *tmp;
    // tmp = lst;
    // while (tmp != NULL)
    // {
    //     i = 0;
    //     while (tmp -> str[i] != NULL)
    //     {
    //         printf("%s\n", tmp -> str[i]);
    //         i++;
    //     }
    //     tmp = tmp -> next;
    // }
}

// void    ft_execution(t_arg_lst *arg, int pfd[], char **envp)
// {
    
// }

char    *ft_join_path(char **path, char *prog)
{
    int  i;
    char    *tmp;
    char    *full_path;

    i = 0;
    while (path[i] != NULL)
    {
        tmp = ft_strjoin(path[i], "/");
        full_path = ft_strjoin(tmp, prog);
        if (full_path == NULL)
        {
            //free lst
            exit(0);
        }
        if (access(full_path, X_OK | F_OK) == 0)
            return (full_path);
        i++;
    } 
    // Not found path case
    // ....
    return (NULL);
}

pid_t    ft_fork(void)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork()");
        exit(0);
    }
    return (pid);
}

t_arg_lst *ft_check_argv(char **argv)
{
    int i;
    int j;
    t_arg_lst   *lst;
    char    **words;

    i = 2;
    lst = (t_arg_lst *)malloc(sizeof(t_arg_lst));
    if (lst == NULL)
        exit(0);
    lst -> str = NULL;
    lst -> next = NULL;
    while (argv[i + 1] != NULL)
    {
        create_lst(&lst, argv[i]);
        i++;
    }
    return (lst);
}

void    create_lst(t_arg_lst **lst, char *str)
{
    t_arg_lst *tmp;
    t_arg_lst *trav;
    char    **words;

    words = ft_split(str, ' ');
    if (words == NULL)
    {
        // free lst
        exit(0);
    }
    trav = (*lst);
    if (trav -> str == NULL)
        trav -> str = words;
    else
    {    
        tmp = (t_arg_lst *)malloc(sizeof(t_arg_lst));
        if (tmp == NULL)
        {
            // free lst
            exit(0);
        }
        tmp -> str = words;
        while (trav -> next != NULL)
            trav = trav -> next;
        trav -> next = tmp;
    }
}

char **ft_check_envp(char **envp)
{
    int i;
    char *str;

    i = 0;
    while (envp[i] != NULL)
    {
        if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
        {
            str = ft_strtrim(envp[i], "PATH=");
            if (str == NULL)
                exit(0);
            return (ft_split(str, ':'));
        }
        i++;
    }
    return (NULL);
}