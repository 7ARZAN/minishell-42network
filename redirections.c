/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:17:38 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/16 11:30:21 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "parser.h" */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct s_redir
{
	char				*redir_files;
	int					redir_type;
	struct s_redir		*next;
}						t_redir;

t_redir	*files(char *file, int type)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	redir->redir_files = file;
	redir->redir_type = type;
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_redir **redir, t_redir *new)
{
	t_redir	*tmp;

	if (!*redir)
		*redir = new;
	else
	{
		tmp = *redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	print_redir(t_redir *redir)
{
	while (redir)
	{
		printf("redir_files: %s\n", redir->redir_files);
		printf("redir_type: %d\n", redir->redir_type);
		redir = redir->next;
	}
}

//function to create redirections files

int	create_redir_files(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->redir_type == 1)
			fd = open(redir->redir_files, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->redir_type == 2)
			fd = open(redir->redir_files, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->redir_type == 3)
			fd = open(redir->redir_files, O_RDONLY);
		if (fd == -1)
		{
			write(2, "Error in opening file\n", 22);
			return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_redir	*redir;

	redir = NULL;
	printf("ac: %d\n", ac);
	add_redir(&redir, files(av[1], 1));
	add_redir(&redir, files(av[2], 2));
	add_redir(&redir, files(av[3], 3));
	printf("redir: \n");
	print_redir(redir);
	create_redir_files(redir);
	return (0);
}
