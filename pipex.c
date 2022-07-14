#include "pipex.h"

void	err(char *str)
{
	perror(str);
	exit(0);
}

int main(int argc, char **argv, char **env)
{
    t_data vars;

    if (argc == 5)
    {
        env_paths(&vars, env);  
		if (pipe(vars.pip_fds) == -1)
			err("PIPE");
        vars.pid = fork();
        if (vars.pid == 0)
            exe_cmd1(&vars, argv, env);
        else 
        {
            vars.pid_2 = fork();
            exe_cmd2(&vars, argv, env);
        }
    }
    else 
        write(2, "usage : infile \"cmd1 -options\" \"cmd2 - option\" outfile\n", 56);
    return (0);
}