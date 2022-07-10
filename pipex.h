/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 21:02:52 by jchennak          #+#    #+#             */
/*   Updated: 2022/07/06 00:35:12 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
#define PIPEX_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>


typedef struct s_data
{
	int		pip_fds[2]; 
	pid_t	pid;
	pid_t	pid_2;
	int		infile;
	int		outfile;
	char	**cmd1;
	char	**cmd2;
	char	*path;
	char	**env_p;
	char	*cmd;
	char	*jn;
	
}	t_data;

void		err(char *str);
char		**ft_split(char const *s, char c);
void		env_path(t_data	*vars, char **env);
char		*ft_strnstr(const char *str, const char *to_find, size_t len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
// char		*ft_strdup(const char *s1);


# endif