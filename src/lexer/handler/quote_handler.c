/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:30:29 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/20 11:20:54 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Handle nested quotes */
static int	handle_nested_quote(t_tokenizer *tokenizer, char quote)
{
	if (!is_valid_position(tokenizer))
		return (0);
	if (!tokenizer->in_quote)
	{
		tokenizer->quote_char = quote;
		tokenizer->in_quote = 1;
		return (1);
	}
	if (tokenizer->quote_char == quote)
	{
		tokenizer->in_quote = 0;
		tokenizer->quote_char = 0;
		return (1);
	}
	return (0);
}

/* Quote handling logic */
void	handle_quote(t_tokenizer *tokenizer)
{
	char	current;

	if (!is_valid_position(tokenizer))
	{
		tokenizer->position = -1;
		return ;
	}
	current = tokenizer->input[tokenizer->position];
	if (!handle_nested_quote(tokenizer, current))
		tokenizer->position++;
}

/* Return the current quote state */
t_quote_state	get_quote_state(t_tokenizer *tokenizer)
{
	t_quote_state	state;

	state.in_quote = tokenizer->in_quote;
	state.quote_char = tokenizer->quote_char;
	return (state);
}
