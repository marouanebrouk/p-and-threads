#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>


size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}



char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char		*substr;
	size_t		slen;
	size_t		i;

	i = 0;
	slen = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start > slen)
		return (NULL);
	if (len > slen - start)
		len = slen - start;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}



char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;
	size_t	j;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = malloc(len1 + len2 + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

static int	count_words(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] != c && (str[i + 1] == c || !str[i + 1]))
			count++;
	return (count);
}

static void	free_all(char **p, int l)
{
	int i = 0;
	while (i <= l)
	{
		free(p[i]);
		i++;
	}
	free(p);
}

char	**ft_split(char *s, char c)
{
	char	**p;
	int		i;
	int		j;
	int		l;

	i = 0;
	l = -1;
	if (!s)
		return (NULL);
	p = (char **)malloc(sizeof (char *) * (count_words((char *)s, c) + 1));
	if (!p)
		return (NULL);
	while (++l < count_words((char *)s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] != c && s[i])
			i++;
		p[l] = ft_substr(s, j, i - j);
		if (!p[l])
			return (free_all(p, l), NULL);
	}
	return (p[l] = NULL, p);
}



int main(int ac, char **av, char *envp[])
{
    if (ac != 2)
        exit(printf("Enter a command\n"));
    int i = 0;
    while (envp[i])
    {
        if (strncmp(envp[i],"PATH=",5) == 0)
            break;
        i++;
    }
    char **splited;
    splited = ft_split((envp[i])+5,':');
    int j = 0;
    while (splited[j])
    {
        splited[j] =  ft_strjoin(splited[j],"/");
        splited[j] = ft_strjoin(splited[j],av[1]);
        j++;
    }
    j = 0;
    while (splited[j]) 
    {
        if (access(splited[j],F_OK | X_OK) == 0)
            break;
        j++;
    }
    if (splited[j] == NULL)
        exit(printf("'%s' command not found \n",av[1]));
    i = 0;
    char *args[2];
    args[i] = av[1];
    args[i+1] = NULL;
	printf("path is %s \n",splited[j]);
    execve(splited[j],args,envp);
	printf("hello execv\n");
}

