/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_realloc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/20 19:45:56 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/20 20:15:37 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "common.h"
#include "env.h"

void	*mem_realloc(void *ptr, unsigned int old, unsigned int new)
{
	void			*p;
	char			*c;
	char			*k;
	unsigned int	i;

	if (new == old && ptr)
		return (ptr);
	if (!new && ptr)
		return (free_alloc(ptr), NULL);
	p = mem_alloc(new);
	if (!p)
		return (NULL);
	if (!ptr)
		return (p);
	c = (char *)p;
	k = (char *)ptr;
	i = 0;
	while (i < old && i < new)
	{
		*c++ = *k++;
		i++;
	}
	free_alloc(ptr);
	return (p);
}
