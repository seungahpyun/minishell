/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 10:14:48 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/11 10:18:18 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	pid;
	pid = fork();
	open("infile", O_RDONLY);
	while (1)
	{
		printf("Hello minishell %i\n", pid);
		sleep(1);
	}
	return (0);
}
