/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logic_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:52 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/10 17:26:46 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Handle logic operation */
t_ast_node	*handle_logic_operation(t_token **token, t_ast_node *left)
{
	t_ast_node	*logic_node;
	t_ast_node	*right;

	logic_node = create_logic_node(token);
	if (!logic_node)
		return (NULL);
	if ((*token)->type == TOKEN_LPAREN)
		right = parse_group(token);
	else
		right = parse_pipeline(token);
	if (!right)
	{
		free_ast(logic_node);
		return (NULL);
	}
	logic_node->left = left;
	logic_node->right = right;
	return (logic_node);
}

/* Handle logic sequence */
t_ast_node	*handle_logic_sequence(t_token **token, t_ast_node *left)
{
	t_ast_node	*logic_node;
	t_ast_node	*right;

	if (!token || !*token || !is_logic_operator(*token))
		return (left);
	logic_node = create_logic_node(token);
	if (!logic_node)
	{
		free_ast(left);
		return (handle_logic_error());
	}
	right = parse_pipeline(token);
	if (!right)
	{
		free_ast(left);
		free_ast(logic_node);
		return (handle_logic_error());
	}
	logic_node->left = left;
	logic_node->right = right;
	return (logic_node);
}

/* Parse logic */
t_ast_node	*parse_logic(t_token **token)
{
	t_ast_node	*left;
	t_ast_node	*result;

	left = parse_pipeline(token);
	if (!left || !*token)
		return (left);
	while (*token && is_logic_operator(*token))
	{
		result = handle_logic_sequence(token, left);
		if (!result)
			return (NULL);
		left = result;
	}
	return (left);
}

/* Parse complete */
t_ast_node	*parse_complete_bonus(t_token **token)
{
	t_ast_node	*root;
	t_ast_node	*logic_node;

	if (!token || !*token)
		return (NULL);
	root = parse_group(token);
	if (!root)
		return (NULL);
	while (*token && is_logic_operator(*token))
	{
		logic_node = handle_logic_sequence(token, root);
		if (!logic_node)
			return (free_ast(root), NULL);
		root = logic_node;
	}
	return (root);
}
