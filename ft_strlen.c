#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	res = malloc(count * size);
	if (res == 0)
		return (0);
	ft_bzero(res, count * size);
	return (res);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp;
	size_t			i;

	temp = s;
	i = 0;
	while (i < n)
	{
		temp[i] = 0;
		i++;
	}
}