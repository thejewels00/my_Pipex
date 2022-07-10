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
        //system("pipex");
        // ********* preparation des outils *****
        vars.cmd1 = ft_split(argv[2], ' ');//leaks
		vars.cmd2 = ft_split(argv[3], ' ');//leaks
        env_path(&vars, env);
        vars.path = ft_substr(vars.path, 5, ft_strlen(vars.path) - 5);
        vars.env_p = ft_split(vars.path, ':');

        // printf("my split path\n");// remove
        // int i = 0;//rm
		// while (vars.env_p[i]) //  remove 
		// {
		// 	printf("%s\n", vars.env_p[i]); //rm
		// 	i++;//rm
		// } //rm
        //************************************************
        //printf("Pipex\n"); // rm
		if (pipe(vars.pip_fds) == -1)
			err("PIPE");
        vars.pid = fork();
        if (vars.pid == 0)
        {
            vars.infile = open(argv[1], O_RDONLY);// open file
            if (vars.infile == -1)
			    err("infile");
            //printf("cmd1\n");
            //printf("hna sedi Read ghire f child \n");
            //with errno :D RFM
            if (dup2(vars.infile, 0) == -1 || dup2(vars.pip_fds[1], 1) == -1)
				err("Dup2");
            close(vars.infile);
			close(vars.pip_fds[1]);
            close(vars.pip_fds[0]);//sedi read
            vars.cmd = ft_strjoin("/", vars.cmd1[0]);
			while (j == -1 && vars.env_p[i])
			{
				vars.jn = ft_strjoin(vars.env_p[i], vars.cmd);
				j = access(vars.jn, X_OK);
				i++;
			}
            //vars.cmd1[0] = ft_strdup(vars.jn);
			if (execve(vars.jn, vars.cmd1, env) == -1)  
				err("execve");
        }
        else 
        {
            wait(NULL);
            //printf("reviens au parents 1\n");
            close (vars.pip_fds[1]);// close write
            //printf("hna sedi l infile \n");
            vars.pid_2 = fork();
            if (vars.pid_2 == 0)
            {
                //printf("cmd2\n");
                vars.outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC,  0644);
                if (vars.outfile == -1)
			        err("outfile");
                if (dup2(vars.outfile, 1) == -1 || dup2(vars.pip_fds[0], 0) == -1)
				    err("Dup2"); // Dup 2 error
			    close(vars.pip_fds[0]);
			    close(vars.outfile);
                vars.cmd = ft_strjoin("/", vars.cmd2[0]);
			    while (j == -1 && vars.env_p[i])
			    {
				    vars.jn = ft_strjoin(vars.env_p[i], vars.cmd);
				    j = access(vars.jn, X_OK);
				    i++;
			    }
			    //fprintf(stderr,"commande path :%s \n",vars.jn); // rm
                //vars.cmd2[0] = ft_strdup(vars.jn);
			    if (execve(vars.jn, vars.cmd2, env) == -1)  
				    err("execve");
                //chid 2
            }
            else
            {
                wait(NULL);
                //printf("reviens au parents 2\n");
                close(vars.pip_fds[0]); //close read
                //printf("hna sedi l outfile\n");
            }
        }
             //printf("what about me ?\n");
    }
    else 
        write(2, "usage : infile \"cmd1 -options\" \"cmd2 - option\" outfile\n", 56);
    return (0);
}