#include<stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	s1_len = strlen((char*)s1);
	s2_len = strlen((char*)s2);
	res = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	else
	{
		while (i < s1_len)
			res[j++] = s1[i++];
		i = 0;
		while (i < s2_len)
			res[j++] = s2[i++];
	}
	res[j] = '\0';
	return (res);
}





int ft_cd(char *path, char *home)
{
	char		*tmp;
	int			ret;
	char		*path_absolute;
	char		*curent_path;
	static char	*old_path = NULL;

	curent_path = (char *)malloc(sizeof(char) * 100);
	if (!curent_path)
		return (-1);
	curent_path = getcwd(curent_path, 100);
	if (!old_path)
		old_path = curent_path;
	if (!ft_strcmp(path, "~"))
		ret = chdir(home);
	else if (!ft_strcmp(path, "-"))
		ret = chdir(old_path);
	else
	{
		if(*path != '/')
		{
			tmp = ft_strjoin(curent_path, '/');
			path_absolute = ft_strjoin(tmp, path);
			free(tmp);
		}
		ret = chdir(path);
		if (ret == -1)
			printf("cd: no such file or directory: %s\n", path);
			
		free(path);
	}
	return (ret);
}

#include<unistd.h>
int main()
{

	char s[100];
	// int n;
	// printf("%s\n", s);÷
	printf("%s\n", getcwd(s, 100));
	ft_cd(".","/Users/mochegri");
	// n = chdir("-");
	// printf("\n{%d}\n", n);
	// printf("%s\n", getcwd(s, 100));
	// printf("%s\n", getcwd());

	return 0;
}
