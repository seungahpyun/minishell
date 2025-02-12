/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipeline_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:20 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/10 15:16:32 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*pipe_node;

	pipe_node = create_ast_node(TOKEN_PIPE);
	if (!pipe_node)
	{
		free_ast(left);
		return (NULL);
	}
	pipe_node->left = left;
	pipe_node->right = right;
	return (pipe_node);
}

static t_ast_node	*handle_redirection_in_pipe(t_ast_node *left,
											t_token **token)
{
	t_ast_node	*redir;

	redir = parse_redirection(token);
	if (!redir)
	{
		free_ast(left);
		return (NULL);
	}
	redir->left = left;
	return (redir);
}

static t_ast_node	*parse_pipe_sequence(t_token **token)
{
	t_ast_node	*left;
	t_ast_node	*right;

	if (!token || !*token)
		return (NULL);
	if ((*token)->type == TOKEN_WORD)
	{
		left = parse_command(token);
		if (!left)
			return (NULL);
		if (*token && is_redirection(*token))
		{
			t_ast_node *redir = handle_redirection_in_pipe(left, token);
			if (!redir)
			{
				free_ast(left);
				return (NULL);
			}
			left = redir;
		}
	}
	else
		return (NULL);
	if (!*token || (*token)->type != TOKEN_PIPE)
		return (left);
	*token = (*token)->next;
	right = parse_pipe_sequence(token);
	if (!right)
	{
		free_ast(left);
		return (NULL);
	}
	t_ast_node *pipe_node = create_pipe_node(left, right);
	if (!pipe_node)
	{
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	return (pipe_node);
}

t_ast_node	*parse_pipeline(t_token **token)
{
	t_ast_node	*root;
	t_ast_node	*current;

	if (!token || !*token)
		return (NULL);
	root = parse_pipe_sequence(token);
	if (!root)
		return (NULL);
	current = root;
	while (current)
	{
		if (current->type == TOKEN_PIPE && (!current->left || !current->right))
		{
			ft_putendl_fd("minishell: syntax error near unexpected token '|'",
				STDERR_FILENO);
			free_ast(root);
			return (NULL);
		}
		current = current->right;
	}
	return (root);
}
