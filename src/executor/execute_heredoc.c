/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 10:15:49 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/19 21:00:14 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "common.h"

//strace -f bash -c
static int	count_heredocs(t_redir *redir)
{
	int	count;

	count = 0;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
			count++;
		redir = redir->next;
	}
	return (count);
}
static char	*gen_filename(int index)
{
	char	*filename;
	char 	*index_str;

	index_str = ft_itoa(index);
	if (!index_str)
		return (NULL);
	filename = mem_strjoin("/tmp/heredoc_", index_str);
	free(index_str);
	return (filename);
}

static t_heredoc	*heredoc_init(t_redir *redir, int heredoc_counter)
{
	t_heredoc	*heredoc;

	heredoc = (t_heredoc *)mem_alloc(sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	heredoc->delimiter = redir->file;
	heredoc->delimiter_count = count_heredocs(redir);
	heredoc->filename = gen_filename(heredoc_counter);
	if (!heredoc->filename )
		return (error("Memory allocation failed", NULL), free(heredoc), NULL);
	heredoc->fd = open(heredoc->filename , O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc->fd == -1)
		return (error("heredoc_init open() failed", NULL), free(heredoc->filename), free(heredoc), NULL);
	return (heredoc);
}

static void	free_heredoc_on_failure(t_heredoc *heredoc, t_redir *r)
{
	if (!heredoc)
	{
		error("open heredoc", NULL);
		exit(1);
	}
	free_alloc(heredoc->filename);
	if (heredoc->delimiter != r->file)
		free_alloc(heredoc->delimiter);
	free_alloc(heredoc);
	exit(1);
}


static void	handle_heredoc(t_redir *r, int heredoc_counter)
{
	char	*content;
	t_heredoc	*heredoc;

	signal(SIGINT, heredoc_signals);
	heredoc = heredoc_init(r, heredoc_counter);
	if (!heredoc || !heredoc->filename)
		return (error("heredoc init failed", NULL), exit(1));
	heredoc->fd = open(heredoc->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc->fd == -1)
		return (free_heredoc_on_failure(heredoc, r));
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		content = get_next_line(STDIN_FILENO);
		if (!content)
			break ;
		if (ft_strncmp(content, heredoc->delimiter, ft_strlen(heredoc->delimiter)) == 0
			&& content[ft_strlen(heredoc->delimiter)] == '\n')
		{
			free_alloc(content);
			break;
		}
		write(heredoc->fd, content, ft_strlen(content));
		free_alloc(content);
	}
	close(heredoc->fd);
	r->file = heredoc->filename;
	free(heredoc->delimiter);
	free(heredoc);
	restore_stdin_after_heredoc();
}

void	handle_all_heredocs(t_redir *redir)
{
	int		heredoc_counter;
	t_redir	*current_redir;
	int		total_heredocs;

	heredoc_counter = 1;
	current_redir = redir;
	total_heredocs = count_heredocs(redir);
	printf("Total heredocs: %d\n", total_heredocs);
	while (current_redir  && heredoc_counter <= total_heredocs)
	{
		if (current_redir->type == TOKEN_HEREDOC)
		{
			handle_heredoc(current_redir, heredoc_counter);
			heredoc_counter++;
		}
		current_redir = current_redir->next;
	}
}
