/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:22:29 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/12/26 15:23:57 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *get_pwd(t_env *data)
{
	size_t	i;

	data->pwd = NULL;
	free(data->pwd);
	i = 0;
	while (ft_strncmp(data->f_env[i], "PWD=", 4) != 0)
		i++;
	data->pwd = ft_substr(data->f_env[i], 4, ft_strlen(data->f_env[i]) - 4);
	return (data->pwd);
}

char *get_path(t_env *data)
{
	size_t	i;

	data->path = NULL;
	free(data->path);
	i = 0;
	while (ft_strncmp(data->f_env[i], "PATH=", 5) != 0)
		i++;
	data->path = ft_substr(data->f_env[i], 5, ft_strlen(data->f_env[i]) - 5);
	return (data->path);
}

char *get_usr(t_env *data)
{
	size_t	i;

	data->usr = NULL;
	free(data->usr);
	i = 0;
	while (ft_strncmp(data->f_env[i], "USER=", 5) != 0)
		i++;
	data->usr = ft_substr(data->f_env[i], 5, ft_strlen(data->f_env[i]) - 5);
	return (data->usr);
}

char **ms_dupdup(char **environ)
{
	size_t	i;
	char **new;

	i = 0;
	while (environ[i])
		i++;
	new = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (environ[++i])
		new[i] = environ[i];
	return (new);
}

void update_env(t_env *data)
{
	extern char **environ;

	free_tab(data->f_env);	
	data->f_env = ms_dupdup(environ);
	get_usr(data);
	get_pwd(data);
	get_path(data);
}
