/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:26:22 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 12:00:49 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int g_exitno;

int	apply_redi(t_tok *d_token, t_pipe *d_pipe,int i)
{
	int j;
	int k;
	char **new;

	k = 0;
	j = 0;
	new = ft_calloc(ft_strlenlen(d_token->tokens[i]), sizeof(char *));
	while(d_token->tokens[i][j])
	{
		if (ft_strcmp(d_token->tokens[i][j], "<") == 0)
		{
			if (access(d_token->tokens[i][j + 1], F_OK | R_OK))
			{
				perror("minishell input:");
				d_pipe->t_cat  = 1;
				d_pipe->input = open("/dev/null", O_RDONLY);
				return(1);
			}
			if (d_pipe->input != -1)
				close(d_pipe->input);
			d_pipe->input = open(d_token->tokens[i][j + 1], O_RDONLY);
			j++;
		}
		else
			new[k++] = ft_strdup(d_token->tokens[i][j]);
		j++;
	}
	free_tab(d_token->tokens[i]);
	d_token->tokens[i] = new;
	dup2(d_pipe->input, STDIN_FILENO);
	return(0);
}

// void apply_redi(t_tok *d_token, t_pipe *d_pipe, int i) {
//     int j, k;
//     char **new;
//
//     j = 0;
//     k = 0;
//     new = ft_calloc(ft_strlenlen(d_token->tokens[i]), sizeof(char *));
//     while (d_token->tokens[i][j]) {
//         if (ft_strcmp(d_token->tokens[i][j], "<") == 0) {
//             j++; // Sautez le "<"
//             if (d_token->tokens[i][j] == NULL) {
//                 // Gérer l'erreur de syntaxe
//                 break;
//             }
//             if (access(d_token->tokens[i][j], F_OK | R_OK)) {
//                 perror("minishell input:");
//             } else {
//                 if (d_pipe->input != -1)
//                     close(d_pipe->input);
//                 d_pipe->input = open(d_token->tokens[i][j], O_RDONLY);
//                 if (d_pipe->input != -1) {
//                     dup2(d_pipe->input, STDIN_FILENO);
//                 }
//             }
//         } else {
//             new[k++] = ft_strdup(d_token->tokens[i][j]);
//         }
//         j++;
//     }
//     new[k] = NULL; // Terminaison NULL pour le tableau
//     free(d_token->tokens[i]);
//     d_token->tokens[i] = new;
//     if (d_pipe->input != -1) {
//         close(d_pipe->input); // Assurez-vous de fermer le descripteur de fichier
//     }
// }
