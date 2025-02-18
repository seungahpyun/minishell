/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 10:15:49 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/18 18:40:32 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "common.h"

//strace -f bash -c 
char	*gen_filename(int index)
{
	char	*filename;

	filename = mem_alloc(20);
	if (!filename)
		return (NULL);
	ft_strlcpy(filename, "/tmp/heredoc_", ft_strlen("/tmp/heredoc_"));
	ft_strlcat(filename, ft_itoa(index), ft_strlen(ft_itoa(index)));
	return (filename);
}


static t_heredoc	*heredoc_init(t_redir *redir, int index)
{
	t_heredoc	*heredoc;
	char		*tmp_name;
	int			fd;

	heredoc = (t_heredoc *)mem_alloc(sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	heredoc->delimiter = redir->file;
	tmp_name = gen_filename(index);
	if (!tmp_name)
	{
		error("Memory allocation failed", NULL);
		free(heredoc);
		return (NULL);
	}
	printf("heredoc->delimiter: %s\n", heredoc->delimiter);
	fd = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		error("heredoc_init open() failed", NULL);
		free(tmp_name);
		free(heredoc);
		return (NULL);
	}
	close(fd);
	heredoc->filename = tmp_name;
	return (heredoc);
}

void	handle_heredoc(t_redir *r, int index)
{
	int			heredoc_fd;
	char		*content;
	t_heredoc	*heredoc;

	signal(SIGINT, heredoc_signals);
	if (r->type != TOKEN_HEREDOC)
		return ;
	heredoc = heredoc_init(r, index);
	if (!heredoc || !heredoc->filename)
		return (error("heredoc init failed", NULL), exit(1));
	heredoc_fd = open(heredoc->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd == -1)
		return (error("open heredoc", NULL), free_alloc(heredoc->filename), exit(1));
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		content = get_next_line(STDIN_FILENO);
		if (!content) 
			break;
		if (ft_strncmp(content, heredoc->delimiter, ft_strlen(heredoc->delimiter)) == 0
			&& content[ft_strlen(heredoc->delimiter)] == '\n')
		{
			free_alloc(content);
			break;
		}
		write(heredoc_fd, content, ft_strlen(content));
		free_alloc(content);
	}
	close(heredoc_fd);
	r->file = heredoc->filename;  // Store the new file for execution
}



