/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:07:37 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/02 16:30:53 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ms_count_word(char *input, int *j)
{
	int counter;
	int q[2];
	int trigger;

	counter = 0;
	trigger = 0;
    (void) trigger;
    (void) q;
	q[0] = 0;
	q[1] = 0;
	while (input[*j] && ms_wltoken(&input[*j]) == ERROR)
	{
        trigger = 0;
        while (input[(*j)] && ms_isws(input[*j]))
            (*j)++;
        while (input[(*j)] && ((!ms_isws(input[*j]) && ms_wlcmdtok(&input[*j]) == ERROR && ms_wltoken(&input[(*j)]) == ERROR)
            || (q[0] || q[1])))
        {
            q[0] ^= (input[*j] == '\"');
            while (input[*j] && q[0])
            {
                (*j)++;
                q[0] ^= (input[*j] == '\"');
            }
            q[1] ^= (input[*j] == '\'');
            while (input[*j] && q[1])
            {
                (*j)++;
                q[1] ^= (input[*j] == '\'');
            }
            trigger = 1;
            (*j)++;
        }
        counter += (trigger == 1);
        if (input[*j] && ms_wlcmdtok(&input[(*j)]) == TRUE)
        {
            (*j) += ms_tiktok(&input[*j]).len;
            counter += 1;
        }
        else if (input[(*j)] && ms_wltoken(&input[*j]) == ERROR)
            (*j)++;
	}
	return (counter);
}

void ms_fill_cmd(char **split, char *input, int *j, int *type)
{
	int q[2];
	int len;
    int start;
    int i;

	len = 0;
	q[0] = 0;
	q[1] = 0;
    i = 0;
	while (input[*j] && ms_wltoken(&input[*j]) == ERROR)
	{
        len = 0;
        while (input[(*j)] && ms_isws(input[*j]))
            (*j)++;
        start = *j;
        while (input[(*j)] && ((!ms_isws(input[*j]) && ms_wlcmdtok(&input[*j]) == ERROR && ms_wltoken(&input[(*j)]) == ERROR)
            || (q[0] || q[1])))
        {
            q[0] ^= (input[*j] == '\"');
            while (input[*j] && q[0])
            {
                (*j)++;
                len++;
                q[0] ^= (input[*j] == '\"');
            }
            q[1] ^= (input[*j] == '\'');
            while (input[*j] && q[1])
            {
                (*j)++;
                len++;
                q[1] ^= (input[*j] == '\'');
            }
            len++;
            (*j)++;
        }
        if (len > 0)
        {
            split[i] = ft_substr(input, start, len);
            type[i] = CMD;
            i++;
        }
        if (input[*j] && ms_wlcmdtok(&input[(*j)]) == TRUE)
        {
            split[i] = ft_strdup(ms_tiktok(&input[*j]).str);
            type[i] = ms_tiktok(&input[*j]).type;
            i++;
            (*j) += ms_tiktok(&input[*j]).len;
        }
        else if (input[(*j)] && ms_wltoken(&input[*j]) == ERROR)
            (*j)++;
	}
}

void ms_fill_token(char **split, char *input, int *j, int *type)
{
    split[0] = ft_strdup(ms_tiktok(&input[*j]).str);
    type[0] = ms_tiktok(&input[*j]).type;
}


char ***ms_split(t_tok *tdata, t_env *denv, char *input)
{
	char ***split;
	int i;
    int j;
    int j_save;
	int wc;
    int d_value;

	(void) denv;
	i = 0;
    j = 0;
	wc = 0;
    ft_printf("----------------------------------------------\n");
	split = (char ***) ft_calloc(tdata->t_size + 1, sizeof(char **));
	tdata->type = (int **) ft_calloc(tdata->t_size + 1, sizeof(int *));
	while (i < tdata->t_size)
	{
        d_value = 0;
        j_save = j;
		ft_printf("&input[%d] = %fs\n", j, &input[j]);
		wc = ms_count_word(input, &j);
        if (!wc)
        {
            d_value = 1;
            j += ms_tiktok(&input[j]).len;
        }
		split[i] = (char **) ft_calloc(wc + d_value + 1, sizeof(char *));
		tdata->type[i] = (int *) ft_calloc(wc + d_value + 1, sizeof(int));
        if (wc)
            ms_fill_cmd(split[i], input, &j_save, tdata->type[i]);
        else
            ms_fill_token(split[i], input, &j_save, tdata->type[i]);
        while(ms_isws(input[j]))
            j++;
        ft_printf("__--__--__--__--__--__--__--__--__\n");
        ft_printf("ALLOCATED SPLIT[%d] | R_SIZE = %d\n", i, wc + d_value);
        ft_printf("__--__--__--__--__--__--__--__--__\n");
		i++;
	}
    ft_printf("----------------------------------------------\n");
	return (split);
}
