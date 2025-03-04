/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/22 11:08:40 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/22 11:08:40 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "executor.h"
#include "common.h"

static t_env	*env_int(char **key_value)
{
	t_env	*new;

	new = mem_alloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key_value[0];
	new->value = key_value[1];
	new->scope = BOTH;
	new->hide = false;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

/*
	OLDPWD: Initialized with NULL value and scope set to EXPORT.
	SHLVL: tracks how many nested shells are currently active
	_: Represents the last executed command; its scope is set to ENVE.
	?: Special variable representing the exit status of the last command.
*/
t_env	*create_env(char *env)
{
	t_env	*new;
	char	**key_value;

	key_value = mem_split(env, "=");
	if (!key_value)
		return (NULL);
	new = env_int(key_value);
	if (!new)
		return (free_tab(key_value), NULL);
	if (ft_strcmp(new->key, "OLDPWD") == 0)
	{
		new->value = NULL;
		new->scope = EXPORT;
	}
	else if (ft_strcmp(new->key, "SHLVL") == 0)
		setup_shlvl(new);
	else if (ft_strcmp(new->key, "_") == 0)
		new->scope = ENVE;
	else if (ft_strcmp(new->key, "?") == 0)
		new->scope = SPECIAL;
	return (new);
}

static void	add_empty_env(t_env **env)
{
	t_env	*new[5];
	char	pwd[PATH_MAX];
	char	*pwd2;
	int		i;

	i = 0;
	if (getcwd(pwd, PATH_MAX) == NULL)
		return ;
	new[0] = create_env("OLDPWD");
	pwd2 = mem_strjoin("PWD=", pwd);
	new[1] = create_env(pwd2);
	new[2] = create_env("SHLVL=0");
	new[3] = create_env("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	new[3]->scope = SPECIAL;
	new[4] = create_env("_=/usr/bin/env");
	new[4]->scope = ENVE;
	while (i < 5)
		add_env(env, new[i++]);
}

t_env	*build_env(char **env)
{
	t_env	*envs;
	t_env	*new;
	int		i;

	envs = NULL;
	i = -1;
	add_env(&envs, create_env("?=0"));
	if (!env[0])
		add_empty_env(&envs);
	while (env[++i])
	{
		new = create_env(env[i]);
		if (!new)
		{
			free_env(&envs);
			return (NULL);
		}
		add_env(&envs, new);
	}
	return (envs);
}

t_env	**get_env_list(void)
{
	static t_env	*env = NULL;

	return (&env);
}
