
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define COMMAND_NOT_FOUND "command not found"

#include "pipex.h"

typedef struct s_pipex {
  int   process_count;
  int   pfd[2];
  int   prev_pfd;
  char  *infile;
  char  *outfile;
  char  **cmds_arg;
  char  *command_path;
  char  **envp;
  char  **env_path;
  pid_t *parent_pid;
} t_pipex;

/* parser.c */
void  parser(t_pipex *data, char *str);

/* getter.c */
void get_data(int argc, char *argv[], char *envp[], t_pipex *data_ptr);
char *get_full_command_path(t_pipex *data, char *cmd);
static char  **get_path(char **env);

/* child.c */
void  child_process(t_pipex data, char *argv_i, int i);
static int   dup_input_fd(t_pipex data, int i);
static int  dup_output_fd(t_pipex data, int i);

/* parent.c */
void  parent_process(t_pipex *data, int pid, int i);

/* error_msg.c */
void  handle_error(t_pipex *data, char *func_name);
static void free_struct(t_pipex *data);

/* ./pipex infile cmd1 cmd2 outfile */
int main(int argc, char *argv[], char *envp[])
{
  int i = 1;
  int pid;
  int status;
  t_pipex data;

  if (argc != 5)
    return (EXIT_FAILURE);
  get_data(argc, argv, envp, &data);
  while (i <= data.process_count)
  {
    if (pipe(data.pfd) == -1)
      handle_error(&data, "pipe");
    pid = fork();
    if (pid == -1)
      handle_error(&data, "fork");
    if (pid == 0)
      child_process(data, argv[i + 1], i - 1);
    else 
      parent_process(&data, pid, i);
    i++;
  }

  i = 0;
  while (i < data.process_count)
  {
    waitpid(data.parent_pid[i], &status, 0);
    i++;
  }
  free_struct(&data);
  return (WEXITSTATUS(status));
}

void  parser(t_pipex *data, char *str)
{
  char  *cmd_path;

  if (str[0] == 0)
    handle_error(data, "access");
  data -> cmds_arg = ft_split(str, ' ');
  if (data -> cmds_arg == NULL)
      handle_error(data, "malloc");
  if (ft_strchr(data -> cmds_arg[0], '/') == NULL)
      data -> command_path = get_full_command_path(data, data -> cmds_arg[0]);
  else
      data -> command_path = ft_strdup(data -> cmds_arg[0]);
  if (data -> command_path == NULL)
      handle_error(data, "malloc");
}

char *get_full_command_path(t_pipex *data, char *cmd)
{
  int   i;
  int   access_check;
  char  *tmp;
  char  *cmd_path;

  i = 0;

  while (data -> env_path[i] != NULL)
  {
    tmp = ft_strjoin(data -> env_path[i], "/");
    if (tmp == NULL)
      handle_error(data, "malloc");
    cmd_path = ft_strjoin(tmp, cmd);
    free(tmp);
    if (cmd_path == NULL)
      handle_error(data, "malloc");
    access_check = access(cmd_path, X_OK | F_OK);
    if (access_check == 0)
      return (cmd_path);
    i++;
    free(cmd_path);
  }
  handle_error(data, "access");
  return (NULL);
}

void get_data(int argc, char *argv[], char *envp[], t_pipex *data_ptr)
{
  data_ptr->process_count = argc - 3;
  data_ptr->infile = argv[1];
  data_ptr->outfile = argv[argc - 1];
  data_ptr->cmds_arg = NULL;
  data_ptr->command_path = NULL;
  data_ptr->envp = envp; 
  data_ptr->env_path = get_path(envp);
  data_ptr->parent_pid = (pid_t *)malloc(sizeof(pid_t) * (data_ptr->process_count));
  if (data_ptr->parent_pid == NULL)
    handle_error(data_ptr, "malloc");
}

static char **get_path(char **env)
{
  char  **paths;
  char  *trimmed_path;

  if (env == NULL)
    return (NULL);
  while (*env != NULL)
  {
    if (ft_strnstr(*env, "PATH=", 5) != NULL)
    {
      trimmed_path = ft_strtrim(*env, "PATH=");
      paths = ft_split(trimmed_path, ':');
      free(trimmed_path);
      return (paths);
    }
    env++;
  }
  return (NULL);
}

void  child_process(t_pipex data, char *argv_i, int i)
{
    dup_input_fd(data, i);
    dup_output_fd(data, i);
    parser(&data, argv_i);
    if (execve(data.command_path, data.cmds_arg, data.envp) == -1)
      handle_error(&data, "execve");
    handle_error(&data, "execve");
}

static int   dup_input_fd(t_pipex data, int i)
{
  int infile_fd;

  if (i == 0)
  {
    infile_fd = open(data.infile, O_RDONLY);
    if (infile_fd == -1)
      handle_error(&data, "open");
    if (dup2(infile_fd, STDIN_FILENO) == -1)
      handle_error(&data, "dup2");
    close(infile_fd);
  }
  else
  {
    if (dup2(data.prev_pfd, STDIN_FILENO) == -1)
      handle_error(&data, "dup2");
    close(data.prev_pfd);
  }
  close(data.pfd[0]);
  return (0);
}

static int  dup_output_fd(t_pipex data, int i)
{
  int outfile_fd;

  if (i == data.process_count - 1)
  {
    outfile_fd = open(data.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile_fd == -1)
      handle_error(&data, "open");
    if (dup2(outfile_fd, STDOUT_FILENO) == -1)
      handle_error(&data, "dup2");
    close(outfile_fd);
  }
  else
  {
    if (dup2(data.pfd[1], STDOUT_FILENO) == -1)
      handle_error(&data, "dup2");
  }
  close(data.pfd[1]);
  return (0);
}

void  parent_process(t_pipex *data, int pid, int i)
{
    if (i > 1)
      close(data -> prev_pfd);
    data -> parent_pid[i - 1] = pid;
    data -> prev_pfd = dup(data -> pfd[0]);
    if (data -> prev_pfd == -1)
      handle_error(data, "dup");
    close(data -> pfd[0]);
    close(data -> pfd[1]);
}

void  handle_error(t_pipex *data, char *func_name)
{
  if (ft_strncmp(func_name, "access", -1) == 0)
  {
    if (data -> cmds_arg == NULL)
      ft_putstr_fd(" ", STDERR_FILENO);
    else
      ft_putstr_fd(data -> cmds_arg[0], STDERR_FILENO);
    ft_putstr_fd(": command not found\n", STDERR_FILENO);
    free_struct(data);
    exit(127);
  }
  else
  {
    free_struct(data);
    perror(func_name);
    exit(EXIT_FAILURE);
  }
}

static void free_struct(t_pipex *data)
{
  int i;

  free(data -> parent_pid);
  i = 0;
  if (data -> env_path != NULL)
  {
    while (data -> env_path[i] != NULL)
    {
      free(data -> env_path[i]);
      i++;
    }
    free(data -> env_path);
  }
  i = 0;
  if (data -> cmds_arg != NULL)
  {
    while (data -> cmds_arg[i] != NULL)
    {
      free(data -> cmds_arg[i]);
      i++;
    }
   free(data -> cmds_arg);
  }
  if (data -> command_path != NULL)
    free(data -> command_path);
}

