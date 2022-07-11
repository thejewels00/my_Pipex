#include "pipex.h"

void	err(char *str)
{
	perror(str);
	exit(0);
}

int main(int argc, char **argv, char **env)
{
    t_data vars;
    int     i;
    int     j;

    i = 0;
    j = -1;
    (void)env;
    if (argc == 5)
    {
        
        vars.cmd1 = ft_split(argv[2], ' ');
		vars.cmd2 = ft_split(argv[3], ' ');
        env_path(&vars, env);
        vars.path = ft_substr(vars.path, 5, ft_strlen(vars.path) - 5);
        vars.env_p = ft_split(vars.path, ':');
		if (pipe(vars.pip_fds) == -1)
			err("PIPE");
        vars.pid = fork();
        if (vars.pid == 0)
        {
            close(vars.pip_fds[0]);
            vars.infile = open(argv[1], O_RDONLY);
            if (vars.infile == -1)
			    err("infile");
            if (dup2(vars.infile, 0) == -1 || dup2(vars.pip_fds[1], 1) == -1)
				err("Dup2");
            close(vars.infile);
			close(vars.pip_fds[1]);
            vars.cmd = ft_strjoin("/", vars.cmd1[0]);
			while (j == -1 && vars.env_p[i])
			{
				vars.jn = ft_strjoin(vars.env_p[i], vars.cmd);
				j = access(vars.jn, X_OK);
				i++;
			}
			if (execve(vars.jn, vars.cmd1, env) == -1)  
				err("execve");
        }
        else 
        {
            vars.pid_2 = fork();
            if (vars.pid_2 == 0)
            {
                close (vars.pip_fds[1]);
                vars.outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC,  0644);
                if (vars.outfile == -1)
			        err("outfile");
                if (dup2(vars.outfile, 1) == -1 || dup2(vars.pip_fds[0], 0) == -1)
				    err("Dup2");
			    close(vars.pip_fds[0]);
			    close(vars.outfile);
                vars.cmd = ft_strjoin("/", vars.cmd2[0]);
			    while (j == -1 && vars.env_p[i])
			    {
				    vars.jn = ft_strjoin(vars.env_p[i], vars.cmd);
				    j = access(vars.jn, X_OK);
				    i++;
			    }
			    if (execve(vars.jn, vars.cmd2, env) == -1)  
				    err("execve");

            }
            else
            {
                close(vars.pip_fds[0]); 
                close(vars.pip_fds[1]);
                wait(NULL);
                wait(NULL);
            }
        }
    }
    else 
        write(2, "usage : infile \"cmd1 -options\" \"cmd2 - option\" outfile\n", 56);
    return (0);
}