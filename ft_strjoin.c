# include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(len);
	if (!str)
		return (0);
	(void)ft_strlcpy(str, s1, len);
	(void)ft_strlcat(str, s2, len);
	return (str);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	k;
	size_t	i;

	k = ft_strlen(src);
	if (!dstsize)
		return (ft_strlen(src));
	j = ft_strlen(dst);
	i = 0;
	if (j > dstsize)
		return (k + dstsize);
	while (j + i < dstsize - 1 && src[i])
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (j + k);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = ((char *)src)[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}