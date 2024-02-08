/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:40:00 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/08 11:52:35 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

int *ms_intab(int *w_pos, int *w_size, int p_a, int p_b)
{
    int *new;
    int new_size;
    int i;

    if (!w_size)
        new_size = 3;
    else
        new_size = *w_size + 2;
    new = ft_calloc(new_size, sizeof(int));
    i = 0;
    while (i < *w_size)
    {
        new[i] = w_pos[i];
        i++;
    }
    new[i++] = p_a;
    new[i] = p_b;
    *w_size += 2;
    return (free(w_pos), new);
}


void print_tab(int *w_pos, int w_size)
{
    for (int i = 0; i < w_size; i++)
        ft_printf("W_pos[%d] = %d\n", i, w_pos[i]);
}

char **ms_delindex(char **split, int i)
{
	char **new;
	int	j;
	int k;

	j = 0;
	k = 0;
	new  = ft_calloc(ft_strlenlen(split) + 1, sizeof(char *));
	// ft_printf("LEN = %d\n", ft_strlenlen(split) + 1);
	while (split[j] && j != i)
	{
		// ft_printf("avant i\n");
		new[k++] = ft_strdup(split[j]);
		j++;
	}
	j++;
	while (split[j])
	{
		new[k++] = ft_strdup(split[j]);
		// ft_printf("apres i, new[%d] = %fs\n", k - 1, new[k - 1]);
		j++;
	}
	if (!new[0])
    {
		// ft_printf("ICI\n");
		new[0] = ft_strdup("WRONG");
    }
	free_tab(split);
	return (new);
}

char *ms_delimiter(char *delimiter)
{
	char *new;
	int start;
	int end;
	int i;

	start = 0;
	end = ft_strlen(delimiter) - 1;
	while (((delimiter[start] == '\"' && delimiter[end] == '\"') || (delimiter[start] == '\'' && delimiter[end] == '\'')) && end > start)
	{
		start += 1;
		end -= 1;
	}
	new = ft_calloc(end - start + 1, sizeof(char));
	i = 0;
	new = ft_substr(delimiter, start, end - start + 1);
	return (free(delimiter), new);
}


char	**transform_split(char **split, t_env *denv, t_tok *tdata, int index)
{
	t_starlist	*strl;
	int			x[2];

    (void) tdata;
	x[I] = 0;
	strl = NULL;
    int p_a;
    int p_b;
    char *tmp;
    // int off;

    // off = 0;
	while (ms_setint(&x[J], ZERO), split[x[I]])
	{
		if (tdata->type[index][x[I]] == DELIMITER)
        {
			split[x[I]] = ms_delimiter(split[x[I]]);
			x[I]++;
			if (!split[x[I]])
				break;
        }
        tdata->w_size = 0;
        tdata->w_pos = NULL;
        p_a = 0;
        p_b = 0;
		split[x[I]] = tild_expand(split[x[I]], denv);
        // ft_printf("----------------\n");
		while (split[x[I]][x[J]])
		{
			if (split[x[I]][x[J]] != '\'' && split[x[I]][x[J]] != '\"')
            {
                tmp = r_env(ms_xt(split[x[I]], &x[J], ZERO), denv);
				ms_sab(&strl, ms_snew(tmp, 0));
                p_b += (p_b != 0);
                p_a = p_b;
                p_b += ft_strlen(tmp) - 1;
                // ft_printf("|_| p_a = %d, p_b = %d\n", p_a, p_b);
            }
			else if (split[x[I]][x[J]] == '\"')
            {
                tmp = r_env(ms_xt(split[x[I]], &x[J], '\"'), denv);
                ms_sab(&strl, ms_snew(tmp, 0));
                p_b += (p_b != 0);
                p_a = p_b;
                p_b += ft_strlen(tmp) - 1;
                tdata->w_pos = ms_intab(tdata->w_pos, &tdata->w_size, p_a, p_b);
                // ft_printf("|\"| p_a = %d, p_b = %d\n", p_a, p_b);
            }
			else if (split[x[I]][x[J]] == '\'')
            {
                tmp = ms_xt(split[x[I]], &x[J], '\'');
				ms_sab(&strl, ms_snew(tmp, 0));
                p_b += (p_b != 0);
                p_a = p_b;
                p_b += ft_strlen(tmp) - 1;
                tdata->w_pos = ms_intab(tdata->w_pos, &tdata->w_size, p_a, p_b);
                // ft_printf("|\'| p_a = %d, p_b = %d\n", p_a, p_b);
            }
		}
        // print_tab(tdata->w_pos, tdata->w_size);
		free(split[x[I]]);
		split[x[I]] = w_expand(ms_starjoin(&strl), denv, tdata);
		ms_starclear(&strl);
		free(tdata->w_pos);
		x[I]++;
	}
	int i = 0;
	while (split[i])
    {
		if (ft_strlen(split[i]) == 0)
        {
			// ft_printf("I = %d\n", i);
			split = ms_delindex(split, i);
			// ft_printf("split[0] = %fs\n", split[0]);
        }
		else
			i++;
    }
	return (split);
}
