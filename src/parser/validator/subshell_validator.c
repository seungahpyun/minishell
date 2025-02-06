/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   subshell_validator.c                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <spyun@student.codam.nl>                +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/06 13:42:19 by spyun          #+#    #+#                */
/*   Updated: 2025/02/06 13:42:20 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_subshell_depth(t_ast_node *node)
{
	int	left_depth;
	int	right_depth;
	int	max_depth;

	if (!node)
		return (0);
	left_depth = get_subshell_depth(node->left);
	right_depth = get_subshell_depth(node->right);
	if (left_depth > right_depth)
		max_depth = left_depth;
	else
		max_depth = right_depth;
	return (1 + max_depth);
}

static int	validate_subshell_command(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == TOKEN_WORD)
		return (node->args && node->args[0]);
	if (node->type == TOKEN_PIPE)
		return (validate_subshell_command(node->left)
			&& validate_subshell_command(node->right));
	if (node->type == TOKEN_SUBSHELL)
		return (validate_subshell_command(node->left));
	return (1);
}

static t_syntax_error	validate_subshell_redirections(t_ast_node *node)
{
	t_redirection	*redir;

	if (!node || !node->redirections)
		return (SYNTAX_OK);
	redir = node->redirections;
	while (redir)
	{
		if (!redir->file)
			return (SYNTAX_MISSING_TOKEN);
		if (!is_valid_command_name(redir->file))
			return (SYNTAX_INVALID_COMBINATION);
		redir = redir->next;
	}
	return (SYNTAX_OK);
}

t_syntax_error	validate_subshell_syntax(t_ast_node *node)
{
	t_syntax_error	redir_status;

	if (!node)
		return (SYNTAX_INVALID_SUBSHELL);
	if (get_subshell_depth(node) > 42)
		return (SYNTAX_NESTED_TOO_DEEP);
	if (!node->left || !validate_subshell_command(node->left))
		return (SYNTAX_INVALID_COMMAND);
	redir_status = validate_subshell_redirections(node);
	if (redir_status != SYNTAX_OK)
		return (redir_status);
	return (SYNTAX_OK);
}
