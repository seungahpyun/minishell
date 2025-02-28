/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_handler.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:07 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/28 10:08:57 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast_node	*handle_redirection_error(t_token **token)
{
	if (!*token || !is_valid_filename_token(*token))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token",
			STDERR_FILENO);
		return (NULL);
	}
	return (create_ast_node(TOKEN_WORD));
}

static void	set_redir_flags_and_fd(t_redir *redir, t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
	{
		redir->flags = O_RDONLY;
		redir->fd = 0;
	}
	else if (type == TOKEN_REDIR_OUT)
	{
		redir->flags = O_WRONLY | O_CREAT | O_TRUNC;
		redir->fd = 1;
	}
	else if (type == TOKEN_APPEND)
	{
		redir->flags = O_WRONLY | O_CREAT | O_APPEND;
		redir->fd = 1;
	}
	else if (type == TOKEN_HEREDOC)
	{
		redir->flags = O_RDONLY;
		redir->fd = 0;
	}
}

void	add_redirection(t_ast_node *node, t_token_type type, char *file)
{
	t_redir	*new_redir;
	t_redir	*curr;

	if (!file)
		return ;
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	new_redir->next = NULL;
	set_redir_flags_and_fd(new_redir, type);
	if (!node->redirections)
		node->redirections = new_redir;
	else
	{
		curr = node->redirections;
		while (curr->next)
			curr = curr->next;
		curr->next = new_redir;
	}
}

static void	add_args_to_cmd_node(t_ast_node *cmd_node, t_token **current)
{
	t_token	*temp;

	temp = *current;
	while (temp && (temp->type == TOKEN_WORD
			|| temp->type == TOKEN_WILDCARD))
	{
		add_arg_to_node(cmd_node, temp->content, temp->quote_type);
		temp = temp->next;
	}
	*current = temp;
}

t_ast_node	*parse_redirection(t_token **token)
{
	t_ast_node	*cmd_node;
	t_token		*current;

	if (!token || !*token || !is_redirection(*token))
		return (NULL);
	cmd_node = create_ast_node(TOKEN_WORD);
	if (!cmd_node)
		return (NULL);
	current = *token;
	while (current && is_redirection(current))
	{
		if (!current->next || !is_valid_filename_token(current->next))
		{
			free_ast(cmd_node);
			return (handle_redirection_error(token));
		}
		add_redirection(cmd_node, current->type, current->next->content);
		current = current->next->next;
	}
	if (current && (current->type == TOKEN_WORD
			|| current->type == TOKEN_WILDCARD))
		add_args_to_cmd_node(cmd_node, &current);
	*token = current;
	return (cmd_node);
}
