/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 09:52:20 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/15 08:36:14 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "parser.h"

static int    next_variable(char *str, int i) 
{
    while (!ft_strchr(" $", str[i]) && str[i] != '\0')
        i++;
    return (i);
}
static char    *get_variable_name(char *str, int index)
{
    int        i;
    int        j;
    char    *name;

    i = index + 1;
    j = 0;
    while (str[i] && !ft_strchr(" $", str[i]))
    {
        i++;
        j++;
    }
    name = ft_substr(str, index + 1, j);
    return (name);
}

char    *replace_variable(char *str, int index)
{
    int    i;

    i = 0;
    while (str[i] && !ft_strchr(" $", str[i]))
        i++;
    if (str[i] == '\0' || str[i] == ' ')
        return (str);
    if (str[i] == '$')
    {
        if (str[i + 1] == '?')
            return (ft_strjoin(ft_substr(str, 0, i), ft_itoa(errno)));
        else
            return (ft_strjoin(ft_substr(str, 0, i), getenv(get_variable_name(str, i))));
    }
    return (str);
}
// int    main(int ac, char **av)
// {
//     char    *str;
//     int    i;
//
//     i = 0;
//     str = ft_strdup(av[1]);
//     while (1)
//     {
//         if (str[i] == '$')
//             str = replace_variable(str, i);
//         if (str[i] == '\0')
//             break ;
//         i++;
//     }
//     printf("%s\n", str);
// }
