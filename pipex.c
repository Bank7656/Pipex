/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:54:53 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/22 18:33:11 by thacharo         ###   ########.fr       */
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
void    ft_parent_process(t_data *data_ptr);
void    ft_child_process(t_data *data_ptr, char **cmd, char **envp);

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    char    *program_path;
    t_data      data;
    t_arg_lst   *cmd_trav;
    t_arg_lst   *lst;
    char    **env_path;

    if (argc != 5)
        return (1);
     
    lst = ft_check_argv(argv);
    env_path = ft_check_envp(envp);
    data.count = 0;
    data.infile_name = argv[1];
    data.outfile_name = argv[argc - 1];

    data.input_fd = open(data.infile_name, O_RDONLY);
    if (data.input_fd == -1)
    {
        printf("File does not exist\n");
        //free....
        return (1);
    }

    cmd_trav = lst;
    dup2(data.input_fd, STDIN_FILENO);
    while (data.count < PROCESS_NUM)
    {
        if (pipe(data.pipe_fd) == -1)    
            perror("Pipe()");
        data.program_path = ft_join_path(env_path, cmd_trav -> str[0]);
        pid = ft_fork();
        if (pid == 0)
            ft_child_process(&data, cmd_trav -> str, envp);
        wait(NULL);
        ft_parent_process(&data);
        cmd_trav = cmd_trav -> next;
        data.count++;  
    }
    return (0);
}

void    ft_parent_process(t_data *data_ptr)
{
    close((*data_ptr).pipe_fd[1]);
    if ((*data_ptr).count > 0)
        close((*data_ptr).old_read_fd);
    if ((*data_ptr).count < PROCESS_NUM - 1)
    {
        (*data_ptr).old_read_fd = dup((*data_ptr).pipe_fd[0]);
        close((*data_ptr).pipe_fd[0]);
    }
}

void    ft_child_process(t_data *data_ptr, char **cmd, char **envp)
{
    t_data  data;

    data = *data_ptr;
    if (data.count > 0)
    {
        if (dup2(data.old_read_fd, STDIN_FILENO) == -1)
            perror("dup2()");
        close(data.old_read_fd);
    }
    close(data.pipe_fd[0]);
    if (data.count == PROCESS_NUM -1)
    {
        data.output_fd = open(data.outfile_name, O_WRONLY | O_CREAT, 0644);
        if (data.output_fd == -1)
            perror("Open()");
        if (dup2(data.output_fd, STDOUT_FILENO) == -1)
            perror("dup2()");
        close(data.output_fd);
    }
    else
    {
        if (dup2(data.pipe_fd[1], STDOUT_FILENO) == -1)
            perror("dup2()");
    }
    close(data.pipe_fd[1]);
    if (execve(data.program_path, cmd, envp) == -1)
        perror("execve()");
}

char    *ft_join_path(char **path, char *prog)
{
    int     i;
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