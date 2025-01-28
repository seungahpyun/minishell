/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:13:34 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/28 18:03:53 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/include/libft.h"
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SHELL_ERROR "minishell: "
# define MANY_ARGS_ERROR "Too many argument!"
# define PATH_MAX 4096
# define DECLARE "declare -x "

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define RESET "\033[0m"

extern int	g_exit_status;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_ENV,
	TOKEN_EXEC,
	TOKEN_BLOCK,
	TOKEN_APPEND,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_NEWLINE,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}	t_token;


#endif
