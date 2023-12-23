/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:22:29 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/12/23 15:08:53 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *get_pwd(t_env *data)
{
	size_t	i;

	if (data->pwd)
		free(data->pwd);
	i = 0;
	while (ft_strncmp(data->f_env[i], "PWD=", 4) != 0)
		i++;
	data->pwd = ft_strdup(data->f_env[i]);
	return (data->pwd);
}

char *get_path(t_env *data)
{
	size_t	i;

	if (data->path)
		free(data->path);
	i = 0;
	while (ft_strncmp(data->f_env[i], "PATH=", 5) != 0)
		i++;
	data->path = ft_strdup(data->f_env[i]);
	return (data->path);
}




int	main(int ac, char *av[], char *env[])
{
	t_env data;

	if (!env)
		perror("Env is null");
	data.f_env = env;
	data.pwd = get_pwd(&data);
	data.path = get_path(&data);
	printf("%s\n", data.pwd);
	printf("%s\n", data.path);
}
