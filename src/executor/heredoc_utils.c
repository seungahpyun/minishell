/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 10:16:31 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/19 10:20:15 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"

static char	*get_literal(char *del, int *i)
{
	char	*tmp;
	char	c;
	int		j;

	c = del[(*i)++];
	j = *i;
	while (del[j] && del[j] != c)
		j++;
	tmp = mem_substr(del, *i, j - *i);
	*i = j + 1;
	return (tmp);
}

static char	*get_regular(char *del, int *i)
{
	char	*tmp;
	int		j;

	j = *i;
	while (del[j] && del[j] != '\'' && del[j] != '\"')
		j++;
	tmp = mem_substr(del, *i, j - *i);
	*i = j;
	return (tmp);
}

static char	*append_literal(char *appended, char *del, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = get_literal(del, i);
	if (appended)
	{
		tmp2 = mem_strjoin(appended, tmp);
		free_alloc(tmp);
		free_alloc(appended);
		appended = tmp2;
	}
	else
		appended = tmp;
	return (appended);
}

static char	*append_regular(char *appended, char *del, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = get_regular(del, i);
	if (appended)
	{
		tmp2 = mem_strjoin(appended, tmp);
		free_alloc(tmp);
		free_alloc(appended);
		appended = tmp2;
	}
	else
		appended = tmp;
	return (appended);
}

char	*remove_quotes(char *del, bool *expand)
{
	char	*appended;
	int		i;

	*expand = true;
	i = 0;
	appended = NULL;
	while (del[i])
	{
		if (del[i] == '\'' || del[i] == '\"')
		{
			*expand = false;
			appended = append_literal(appended, del, &i);
		}
		else
			appended = append_regular(appended, del, &i);
	}
	free_alloc(del);
	return (appended);
}

