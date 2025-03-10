/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/01 13:27:18 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/04 18:09:37 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*init_redir_node(t_token_type type, char *file, t_quote_type quote_type)
{
	t_redir	*new_redir;

	new_redir = ft_calloc(1, sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->quote_type = quote_type;
	new_redir->next = NULL;
	if (type == TOKEN_HEREDOC)
	{
		new_redir->delimiter = ft_strdup(file);
		new_redir->file = NULL;
		new_redir->heredoc_file = NULL;
	}
	else
	{
		new_redir->file = ft_strdup(file);
		new_redir->delimiter = NULL;
		new_redir->heredoc_file = NULL;
	}
	set_redir_flags_and_fd(new_redir, type);
	return (new_redir);
}
