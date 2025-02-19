/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:13:34 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/11 10:56:24 by spyun         ########   odam.nl         */
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
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_exit_status;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_VAR,
	TOKEN_WILDCARD,
	TOKEN_NEWLINE,
	TOKEN_EOF,
	TOKEN_SUBSHELL,
}	t_token_type;

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	t_token_type	type;
}	t_token;

// typedef struct s_cmd
// {
// 	char			**argv;
// 	char			*infile;
// 	char			*outfile;
// 	int				here_doc;
// 	int				append;
// 	struct s_cmd	*next;
// }	t_cmd;

void	print_banner(void);

#endif
