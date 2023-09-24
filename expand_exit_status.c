#include "./include/parser.h"

// g_exit_status = 1;
//
// static char	*expand_exit_status(char *str, int *i, int *j)
// {
// 	char	*tmp;
// 	char	*tmp2;
// 	char	*tmp3;
//
// 	tmp = ft_itoa(g_exit_status);
// 	tmp2 = ft_strjoin(str, tmp);
// 	tmp3 = ft_strjoin(tmp2, &str[*i + 1]);
// 	free(tmp);
// 	free(tmp2);
// 	free(str);
// 	*i = *i + 1;
// 	*j = *j + 1;
// 	return (tmp3);
// }
//
// char	*expand_exit_status_in_str(char *str)
// {
// 	int		i;
// 	int		j;
//
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] == '?')
// 			str = expand_exit_status(str, &i, &j);
// 		else
// 		{
// 			str[j] = str[i];
// 			i++;
// 			j++;
// 		}
// 	}
// 	str[j] = '\0';
// 	return (str);
// }
//
// int	main(void)
// {
// 	char	*str;
//
// 	str = ft_strdup("echo $?");
// 	printf("%s\n", expand_exit_status_in_str(str));
// 	free(str);
// }
