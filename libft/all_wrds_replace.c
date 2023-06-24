/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_wrds_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 08:19:13 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/24 08:24:23 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	new_strlen(char *str, char *fword, char *sword)
{
	size_t	fword_len;
	size_t	sword_len;
	size_t	str_len;
	size_t	matchin;

	fword_len = ft_strlen(fword);
	sword_len = ft_strlen(sword);
	str_len = ft_strlen(str);
	matchin = 0;
	while (str[matchin] && ft_strncmp(str + matchin, fword, fword_len) != 0)
		matchin++;
	if (matchin == str_len)
		return (str_len);
	return (str_len - fword_len + sword_len);
}

static char	*replaced_str(char *str, char *fword, char *sword)
{
	char	*new_str;
	size_t	fword_len;
	size_t	sword_len;
	size_t	str_len;
	size_t	matchin;

	fword_len = ft_strlen(fword);
	sword_len = ft_strlen(sword);
	str_len = ft_strlen(str);
	matchin = 0;
	while (str[matchin] && ft_strncmp(str + matchin, fword, fword_len) != 0)
		matchin++;
	if (matchin == str_len)
		return (str);
	new_str = (char *)malloc(sizeof(char) * (str_len - fword_len + sword_len
				+ 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, matchin + 1);
	ft_strlcpy(new_str + matchin, sword, sword_len + 1);
	ft_strlcpy(new_str + matchin + sword_len, str + matchin + fword_len,
		str_len - matchin - fword_len + 1);
	return (new_str);
}

static char	*ft_strstr(char *str, char *fword)
{
	size_t	fword_len;
	size_t	str_len;
	size_t	matchin;

	fword_len = ft_strlen(fword);
	str_len = ft_strlen(str);
	matchin = 0;
	while (str[matchin] && ft_strncmp(str + matchin, fword, fword_len) != 0)
		matchin++;
	if (matchin == str_len)
		return (NULL);
	return (str + matchin);
}

char		*all_wrds_replace(char *str, char *fword, char *sword)
{
	char	*new_str;
	char	*tmp;

	if (!str || !fword || !sword)
		return (NULL);
	new_str = replaced_str(str, fword, sword);
	if (!new_str)
		return (NULL);
	tmp = new_str;
	while (ft_strstr(tmp, fword))
	{
		new_str = replaced_str(tmp, fword, sword);
		free(tmp);
		if (!new_str)
			return (NULL);
		tmp = new_str;
	}
	return (new_str);
}
