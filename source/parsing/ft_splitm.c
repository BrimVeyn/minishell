/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:40:00 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/02 09:44:27 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

int	check_dollar(char **split, t_env *denv)
{
	char	*tmp;

	tmp = NULL;
	if (split[0] && split[0][0] == '$')
		tmp = r_env(split[0], denv);
	if (tmp && ft_strlen(tmp) == 0)
		return (free(tmp), ERROR);
	return (TRUE);
}

void	move_split_index(char **split, int *flag)
{
	int	i;

	i = 1;
	if (split[i] && *flag == 1)
	{
		while (split[i])
		{
			split[i - 1] = split[i];
			i++;
		}
		split[i - 1] = NULL;
	}
}

void	empty_var_setter(t_env *denv, char **split, int *x)
{
	int	flag;

	flag = 0;
	if (check_dollar(split, denv) == ERROR)
	{
		flag = 1;
		free(split[x[I]]);
		split[x[I]] = ft_strdup_char(-19);
		move_split_index(split, &flag);
		if (split[1] == NULL)
			return ;
	}
}

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



void	transform_split(char **split, t_env *denv, t_tok *tdata)
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
	empty_var_setter(denv, split, x);
	while (ms_setint(&x[J], ZERO), split[x[I]])
	{
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
		x[I]++;
	}
}
