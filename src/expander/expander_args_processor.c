/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_args_processor.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/26 14:27:42 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/14 09:15:28 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

static void	handle_regular_env_var(t_ast_node *node, t_env **env_list, int i)
{
	char	*var_name;
	char	*env_value;
	char	*result;
	char	*rest_of_arg;
	int		var_len;

	var_name = extract_var_name_expander(node->args[i] + 1, &var_len);
	rest_of_arg = ft_strdup(node->args[i] + 1 + var_len);
	env_value = get_env_value(*env_list, var_name);
	if (env_value)
		result = ft_strdup(env_value);
	else
		result = ft_strdup("");
	free(var_name);
	if (rest_of_arg && *rest_of_arg)
		result = join_and_free(result, rest_of_arg);
	free(rest_of_arg);
	free(node->args[i]);
	node->args[i] = result;
}

void	expand_env_var(t_ast_node *node, t_env **env_list, int i)
{
	if (node->args[i][1] == '?')
		handle_exit_status_expansion(node, i);
	else
		handle_regular_env_var(node, env_list, i);
}

void	handle_dollar_in_string(t_ast_node *node, t_tokenizer *tokenizer,
		int i)
{
	char	*expanded_arg;

	expanded_arg = handle_expansion(tokenizer, node->args[i]);
	if (expanded_arg)
	{
		free(node->args[i]);
		node->args[i] = expanded_arg;
	}
}

void	handle_wildcard_expansion(t_ast_node *node, int i)
{
	if (!node || !node->args || i < 0 || i >= node->argc)
		return ;
	if (should_skip_expansion(node, i, 0)
		&& !is_mixed_quote_wildcard(node->args[i],
		(node->arg_quote_types && i < node->argc) ?
		node->arg_quote_types[i] : QUOTE_NONE))
		return ;
	if (node->arg_quote_types && i < node->argc &&
		node->arg_quote_types[i] == QUOTE_MIXED)
	{
		process_mixed_wildcard(node, i);
		return ;
	}
	process_wildcard_arg(node, i);
}

void	handle_arg_expansion(t_ast_node *node, t_env **env_list,
		t_tokenizer *tokenizer, int i)
{
	int	had_env_expansion;
	int	repeat_expansion;

	repeat_expansion = 1;
	while (repeat_expansion)
	{
		had_env_expansion = 0;
		repeat_expansion = 0;

		handle_env_dollar_expansion(node, env_list, i, &had_env_expansion);
		if (!had_env_expansion)
			handle_dollar_expansion(node, tokenizer, i, &had_env_expansion);
		if (had_env_expansion)
		{
			if (strchr(node->args[i], '$') != NULL)
				repeat_expansion = 1;
		}
	}
	if (has_wildcard(node->args[i]))
	{
		if (had_env_expansion)
			handle_wildcard_with_expansion(node, i);
		else
			handle_wildcard_expansion(node, i);
	}
}
