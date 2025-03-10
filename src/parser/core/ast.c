/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:54:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/10 16:28:37 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Get the length of the argument array */
static int	get_args_length(char **args)
{
	int	len;

	len = 0;
	if (args)
	{
		while (args[len])
			len++;
	}
	return (len);
}

/* Create and initialise AST nodes */
t_ast_node	*create_ast_node(t_token_type type)
{
	t_ast_node	*node;

	node = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->arg_quote_types = NULL;
	node->argc = 0;
	node->redirections = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/* Copy existing args and add new arg */
static int	copy_args_and_add(t_ast_node *node, t_arg_data *data, char *arg)
{
	int	i;

	i = 0;
	while (i < data->args_len)
	{
		data->new_args[i] = node->args[i];
		if (node->arg_quote_types)
			data->new_quote_types[i] = node->arg_quote_types[i];
		else
			data->new_quote_types[i] = QUOTE_NONE;
		i++;
	}
	data->new_args[data->args_len] = ft_strdup(arg);
	if (!data->new_args[data->args_len])
	{
		free(data->new_args);
		free(data->new_quote_types);
		return (0);
	}
	return (1);
}

/* Complete the argument addition process */
static void	complete_arg_addition(t_ast_node *node, t_arg_data *data)
{
	data->new_quote_types[data->args_len] = data->quote_type;
	data->new_args[data->args_len + 1] = NULL;
	data->new_quote_types[data->args_len + 1] = QUOTE_NONE;
	free(node->args);
	free(node->arg_quote_types);
	node->args = data->new_args;
	node->arg_quote_types = data->new_quote_types;
	node->argc++;
}

/* Add an argument to the node */
void	add_arg_to_node(t_ast_node *node, char *arg, t_quote_type quote_type)
{
	t_arg_data	data;

     printf("Adding argument: '%s' (address: %p) to node %p\n", arg, (void*)arg, (void*)node);
	if (!node || !arg)
		return ;
	data.args_len = get_args_length(node->args);
	data.new_args = (char **)ft_calloc((data.args_len + 2), sizeof(char *));
	if (!data.new_args)
		return ;
	data.new_quote_types = ft_calloc((data.args_len + 2), sizeof(t_quote_type));
	if (!data.new_quote_types)
	{
		free(data.new_args);
		return ;
	}
	data.quote_type = quote_type;
	if (!copy_args_and_add(node, &data, arg))
		return ;
	complete_arg_addition(node, &data);
}
