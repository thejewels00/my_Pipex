#include "pipex.h"

void    env_path(t_data *vars, char  **env)
{
    int i;

    i = 0;
    vars->path = NULL;
    while (env[i] && vars->path == NULL)
	{
		vars->path = ft_strnstr(env[i], "PATH", 5);
		i++;
	}
    // tu peux ajouter la protection 
}

void    env_paths(t_data *vars, char **env)
{
    env_path(vars, env);
    vars->path = ft_substr(vars->path, 5, ft_strlen(vars->path) - 5);//
    vars->env_p = ft_split(vars->path, ':');//
}

void    cmd1(t_data *vars, char **argv)
{
    int i;
    int j;

    i = 0;
    j = -1;
    vars->cmd1 = ft_split(argv[2], ' ');
    close(vars->pip_fds[0]);
    vars->infile = open(argv[1], O_RDONLY);
    if (vars->infile == -1)
		err("infile");
    if (dup2(vars->infile, 0) == -1 || dup2(vars->pip_fds[1], 1) == -1)
		err("Dup2");
    close(vars->infile);
	close(vars->pip_fds[1]);
    vars->cmd = ft_strjoin("/", vars->cmd1[0]);
	while (j == -1 && vars->env_p[i])
	{
		vars->jn = ft_strjoin(vars->env_p[i], vars->cmd);
		j = access(vars->jn, X_OK);
		i++;
	}
}

void    cmd2(t_data *vars, char **argv)
{
    int i;
    int j;

    i = 0;
    j = -1;
    vars->cmd2 = ft_split(argv[3], ' ');
    close (vars->pip_fds[1]);
    vars->outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC,  0644);
    if (vars->outfile == -1)
		err("outfile");
    if (dup2(vars->outfile, 1) == -1 || dup2(vars->pip_fds[0], 0) == -1)
		err("Dup2");
	close(vars->pip_fds[0]);
	close(vars->outfile);
    vars->cmd = ft_strjoin("/", vars->cmd2[0]);
	while (j == -1 && vars->env_p[i])
	{
		vars->jn = ft_strjoin(vars->env_p[i], vars->cmd);
		j = access(vars->jn, X_OK);
		i++;
	}
}

void    exe_cmd1(t_data *vars, char **argv, char **env)
{
    cmd1(vars, argv);
    free(vars->cmd);
    free(vars->env_p);
	if (execve(vars->jn, vars->cmd1, env) == -1)  
	    err("execve");
}

void    exe_cmd2(t_data *vars, char **argv, char **env)
{
    if (vars->pid_2 == 0)
    {
        cmd2(vars, argv);
        free(vars->cmd);
        free(vars->env_p);
		if (execve(vars->jn, vars->cmd2, env) == -1)  
			err("execve");
    }
    else
    {
        close(vars->pip_fds[0]); 
        close(vars->pip_fds[1]);
        wait(NULL);
        wait(NULL);
        free(vars->env_p);//
    }
}