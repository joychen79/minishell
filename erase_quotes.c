/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:29:55 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/28 12:15:19 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_erase_quotes3(t_data *g_data, char *tmp, int i, int op)
{
	check_marks(g_data, op);
	tmp[g_data->j] = g_data->cmd_lst->cmdaux[i];
	g_data->j++;
	return (tmp);
}

char	*ft_erase_quotes2(t_data *g_data, char *tmp, int i, int j)
{
	g_data->j = j;
	while (g_data->cmd_lst->cmdaux[i])
	{
		ft_compare_marks(g_data, i);
		if (g_data->cmd_lst->cmdaux[i] == '"'
			&& g_data->cmd_lst->bcomillas2 == 1)
			tmp = ft_erase_quotes3(g_data, tmp, i, 0);
		else if (g_data->cmd_lst->cmdaux[i] == '\''
			&& g_data->cmd_lst->bcomillas == 1)
			tmp = ft_erase_quotes3(g_data, tmp, i, 1);
		else if (g_data->cmd_lst->cmdaux[i] != '"'
			&& g_data->cmd_lst->cmdaux[i] != '\'')
		{
			tmp[g_data->j] = g_data->cmd_lst->cmdaux[i];
			g_data->j++;
		}
		i++;
	}
	tmp[g_data->j] = '\0';
	return (tmp);
}

char	*ft_erase_quotes(t_data *g_data, int i, int j, int quotes)
{
	char	*tmp;

	g_data->cmd_lst->bcomillas = 0;
	g_data->cmd_lst->bcomillas2 = 0;
	while (g_data->cmd_lst->cmdaux[i])
	{
		if (g_data->cmd_lst->cmdaux[i] == '"'
			&& g_data->cmd_lst->bcomillas2 == 0)
		{
			check_marks(g_data, 0);
			quotes++;
		}
		if (g_data->cmd_lst->cmdaux[i] == '\''
			&& g_data->cmd_lst->bcomillas == 0)
		{
			check_marks(g_data, 1);
			quotes++;
		}
		i++;
	}
	tmp = (char *)malloc (sizeof(char) * (i - quotes + 1));
	i = 0;
	tmp = ft_erase_quotes2(g_data, tmp, j, i);
	return (tmp);
}
