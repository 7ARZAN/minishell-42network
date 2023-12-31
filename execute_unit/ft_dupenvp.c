/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupenvp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:47:33 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/09/18 06:01:29 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

char	*ft_getenv(char *var, t_list *envp_list)
{
	int	len;

	if (!var)
		return (NULL);
	len = ft_strlen(var);
	while (envp_list)
	{
		if (!ft_strncmp(envp_list->content, var, len) && \
			((char *)envp_list->content)[len] == '=')
			return (envp_list->content);
		envp_list = envp_list->next;
	}
	return (NULL);
}

static int	ft_search_set(char *new, char *var, t_list *tmp_list)
{
	while (tmp_list)
	{
		if (!ft_strncmp(tmp_list->content, var, ft_strlen(var)))
		{
			if (((char *)tmp_list->content)[ft_strlen(var)] == '=')
			{
				free(tmp_list->content);
				tmp_list->content = new;
				return (0);
			}
			else if (((char *)tmp_list->content)[ft_strlen(var)] == '\0')
			{
				free(tmp_list->content);
				tmp_list->content = new;
				return (0);
			}
		}
		tmp_list = tmp_list->next;
	}
	return (1);
}

int	ft_setenv(char *var, char *value, t_list *envp)
{
	char	*tmp;
	char	*new;
	t_list	*tmp_list;

	if (!var)
		return (0);
	if (!value)
		new = ft_strdup(var);
	else
	{
		tmp = ft_strjoin(var, "=");
		new = ft_strjoin(tmp, value);
		free(tmp);
	}
	if (!ft_search_set(new, var, envp))
		return (0);
	tmp_list = ft_lstnew(new);
	ft_lstadd_back(&envp, tmp_list);
	return (0);
}

char	**ft_lst_to_char(t_list *envp_list)
{
	char	**envp;
	int		i;

	i = 0;
	if (!envp_list)
		return (NULL);
	envp = ft_calloc(sizeof(char *), (ft_lstsize(envp_list) + 1));
	if (!envp)
		return (NULL);
	while (envp_list)
	{
		if (ft_strchr(envp_list->content, '='))
		{
			envp[i] = ft_strdup(envp_list->content);
			i++;
		}
		envp_list = envp_list->next;
	}
	return (envp);
}

t_list	*ft_dupenvp(char **envp)
{
	t_list	*envp_list;
	t_list	*tmp;

	if (!envp)
		return (NULL);
	envp_list = NULL;
	while (*envp)
	{
		tmp = ft_lstnew(ft_strdup(*envp));
		ft_lstadd_back(&envp_list, tmp);
		envp++;
	}
	return (envp_list);
}
