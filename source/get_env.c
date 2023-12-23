/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:22:29 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/12/23 19:31:43 by nbardavi         ###   ########.fr       */
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
	data->pwd = ft_substr(data->f_env[i], 4, ft_strlen(data->f_env[i]) - 4);
	return (data->pwd);
}

char *get_path(t_env *data)
{
	size_t	i;

	if (data->path)
	{
		data->path = NULL;
		free(data->path);
	}
	i = 0;
	while (ft_strncmp(data->f_env[i], "PATH=", 5) != 0)
		i++;
	data->path = ft_substr(data->f_env[i], 5, ft_strlen(data->f_env[i]) - 5);
	return (data->path);
}

char *get_usr(t_env *data)
{
	size_t	i;

	if (data->usr)
		free(data->usr);
	i = 0;
	while (ft_strncmp(data->f_env[i], "USER=", 5) != 0)
		i++;
	data->usr = ft_substr(data->f_env[i], 5, ft_strlen(data->f_env[i]) - 5);
	return (data->usr);
}
// int	main(int ac, char *av[], char *env[])
// {
// 	t_env data;
//
// 	if (!env)
// 		perror("Env is null");
// 	data.f_env = env;
// 	data.pwd = get_pwd(&data);
// 	data.path = get_path(&data);
// 	printf("%s\n", data.pwd);
// 	printf("%s\n", data.path);
// }
