/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils1.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/23 23:30:20 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/23 23:32:31 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "executor.h"
#include "common.h"

static int	count_visible_envs(t_env *envs)
{
	int	count;

	count = 0;
	while (envs)
	{
		if (envs->hide == 0)
			count++;
		envs = envs->next;
	}
	return (count);
}

static char	*create_env_entry(t_env *envs)
{
	char	*tmp;
	char	*full_entry;

	tmp = mem_strjoin(envs->key, "=");
	if (!tmp)
		return (NULL);
	if (!envs->value)
		return (tmp);
	full_entry = mem_strjoin(tmp, envs->value);
	free(tmp);
	return (full_entry);
}

// /*
// 	Convert env variables into an arrray of strings, formatted as
// 	"key=value" for execve() as executing a new process with execve(),
// 	we need to pass environment variables as a char ** array
// */
char	**env_to_arr(t_env *envs)
{
	char	**env;
	int		i;

	if (!envs)
		return (NULL);
	env = (char **)mem_alloc(sizeof(char *) * (count_visible_envs(envs) + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envs)
	{
		if (envs->hide == 0)
			env[i++] = create_env_entry(envs);
		envs = envs->next;
	}
	env[i] = NULL;
	return (env);
}
