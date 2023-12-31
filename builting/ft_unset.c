/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 08:39:16 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/10/13 02:37:49 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builting.h"

static int	ft_check_if_var(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (1);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (1);
		str++;
	}
	return (0);
}

static int	ft_varcmp(char *s1, char *s2)
{
	if (!ft_strncmp(s1, s2, ft_strlen(s2)) && (s1[ft_strlen(s2)] == '='
			|| !s1[ft_strlen(s2)]))
		return (0);
	return (1);
}

static int	ft_lstremove_if(t_list **head, void *data_ref, int (*cmp)())
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *head;
	prev = NULL;
	while (tmp)
	{
		if (!cmp(tmp->content, data_ref))
		{
			if (prev)
			{
				prev->next = tmp->next;
				ft_lstdelone(tmp, free);
			}
			else
				*head = tmp->next;
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	ft_unset(char **args, t_list **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_check_if_var(args[i]))
			ft_error("unset", "not a valid identifier");
		else
			ft_lstremove_if(env, args[i], ft_varcmp);
		i++;
	}
	return (0);
}
