/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast_optimizer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 16:40:36 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/27 15:41:04 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Optimize subshell */
static t_ast_node	*optimize_subshell(t_ast_node *node)
{
	if (!node->left)
	{
		free_ast(node);
		return (NULL);
	}
	node->left = optimize_ast(node->left);
	if (!node->left)
	{
		free_ast(node);
		return (NULL);
	}
	if (node->redirections)
		node->redirections = merge_redirections(node->redirections);
	if (node->left->type == TOKEN_PIPE)
		node->left = optimize_pipeline(node->left);
	return (node);
}

/* Optimize the AST */
t_ast_node	*optimize_ast(t_ast_node *root)
{
	if (!root)
		return (NULL);
	if (root->is_subshell)
		return (optimize_subshell(root));
	root = remove_empty_nodes(root);
	if (!root)
		return (NULL);
	root->left = optimize_ast(root->left);
	root->right = optimize_ast(root->right);
	return (root);
}
