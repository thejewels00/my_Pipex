#include "pipex.h"

void    env_path(t_data *vars, char  **env)
{
    int i;

    i = 0;
    (*vars).path = NULL;
    while (env[i] && (*vars).path == NULL)
	{
		(*vars).path = ft_strnstr(env[i], "PATH", 5);
		i++;
	}
    // tu peux ajouter la protection 
}