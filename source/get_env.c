/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:22:29 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/12 10:18:23 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *get_pwd(t_env *denv)
{
	size_t	i;

	denv->pwd = NULL;
	free(denv->pwd);
	i = 0;
	while (ft_strncmp(denv->f_env[i], "PWD=", 4) != 0)
		i++;
	denv->pwd = ft_substr(denv->f_env[i], 4, ft_strlen(denv->f_env[i]) - 4);
	return (denv->pwd);
}

char *get_path(t_env *denv)
{
	size_t	i;

	denv->path = NULL;
	free(denv->path);
	i = 0;
	while (ft_strncmp(denv->f_env[i], "PATH=", 5) != 0)
		i++;
	denv->path = ft_substr(denv->f_env[i], 5, ft_strlen(denv->f_env[i]) - 5);
	return (denv->path);
}

char *get_usr(t_env *denv)
{
	size_t	i;

	denv->usr = NULL;
	free(denv->usr);
	i = 0;
	while (ft_strncmp(denv->f_env[i], "USER=", 5) != 0)
		i++;
	denv->usr = ft_substr(denv->f_env[i], 5, ft_strlen(denv->f_env[i]) - 5);
	return (denv->usr);
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
		new[i] = ft_strdup(environ[i]);
	return (new);
}

void update_env(t_env *denv)
{
	extern char **environ;

	free_tab(denv->f_env);	
	denv->f_env = ms_dupdup(environ);
	get_usr(denv);
	get_pwd(denv);
	get_path(denv);
}

int	tab_len(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char **join_tab(char **tab, char *entry)
{
	char **new;
	int i;

	i = -1;
	new = ft_calloc(tab_len(tab) + 2, sizeof(char *));
	while(tab[++i])
		new[i] = ft_strdup(tab[i]);
	new[i] = ft_strdup(entry);
	free_tab(tab);
	return (new);
}

char **get_flist(t_env *denv)
{
	struct dirent	*entry;
    DIR				*dir;
	char			**tab = ft_calloc(2, sizeof(char *));

	dir = opendir(denv->pwd);
	if (dir == NULL)
	{
        perror("opendir");
        exit(EXIT_FAILURE);
	}
	entry = readdir(dir);
	tab = join_tab(tab, entry->d_name);
    while (entry != NULL)
	{
		entry = readdir(dir);
		if (entry)
			tab = join_tab(tab, entry->d_name);
    }
	// for(int i = 0; tab[i]; i++)
	// 	printf("tab[%d] = %s\n", i, tab[i]);
    closedir(dir);
    return (tab);
}
