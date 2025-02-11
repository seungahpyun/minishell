/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_handler.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:07 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/10 12:11:02 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Handling redirect syntax errors */
static t_ast_node	*handle_redirection_error(t_token **token)
{
	if (!*token || (*token)->type != TOKEN_WORD)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token",
			STDERR_FILENO);
		return (NULL);
	}
	return (create_ast_node(TOKEN_WORD));
}

/* Parse redirection */
t_ast_node	*parse_redirection(t_token **token)
{
	t_ast_node		*redir_node;
	t_token_type	redir_type;
	t_ast_node		*next_redir;

	if (!token || !*token || !is_redirection(*token))
		return (NULL);
	redir_type = (*token)->type;
	redir_node = create_ast_node(redir_type);
	if (!redir_node)
		return (NULL);
	*token = (*token)->next;
	if (!*token || (*token)->type != TOKEN_WORD)
		return (free_ast(redir_node), handle_redirection_error(token));
	add_arg_to_node(redir_node, (*token)->content);
	*token = (*token)->next;
	if (*token && is_redirection(*token))
	{
		next_redir = parse_redirection(token);
		if (!next_redir)
			return (free_ast(redir_node), NULL);
		redir_node->right = next_redir;
	}
	return (redir_node);
}
