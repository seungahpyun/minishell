/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 14:41:36 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/19 20:30:00 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "executor.h"
#include <signal.h>
#include <unistd.h>

/*
	Print a newline on Ctrl+C.
	rl_on_new_lin: Readline (if using) on a new line.
	rl_replace_line: Clear the current line.
	rl_redisplay: Redisplay the prompt.
	Set exit status for interrupt.
*/
static void	interrupt_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit_status(1);
}

void	interrupt_w_msg(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	set_exit_status(1);
}


void	interrput_silence(int sig)
{
	(void)sig;
	set_exit_status(1);
}

/*
	duplicates the current file descriptor 0 (standard input) into a static variable
	restore the file descriptor after the signal is caught.
*/
static int	*heredoc_error(void)
{
	static int	fd;

	fd = -1;
	return (&fd);
}

void	heredoc_signals(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	*heredoc_error() = dup(0);
	close(0);
}

void restore_stdin_after_heredoc(void)
{
	if (*heredoc_error() != -1)
	{
		close(0); // Close old fd
		dup2(*heredoc_error(), 0); // Restore saved fd
		close(*heredoc_error()); // Close the duplicate fd
		*heredoc_error() = -1; // Reset saved fd
	}
}

/* 
	Ignore SIGINT and SIGQUIT in the parent process while it’s managing a subshell,
	preventing it from being interrupted while waiting for the child to finish.
*/
void	signals_init(void)
{
	sig_t	error;

	error = signal(SIGINT, interrupt_handler);
	if (error == SIG_ERR)
		ft_putendl_fd("signal() error", STDERR_FILENO);
	error = signal(SIGQUIT, SIG_IGN);
	if (error == SIG_ERR)
		ft_putendl_fd("signal() error", STDERR_FILENO);
}
