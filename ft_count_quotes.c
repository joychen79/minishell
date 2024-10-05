/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 00:20:28 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/28 11:54:06 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*count_quotes3(t_data *g_data, char *end)
{
	const char	delimiters[] = "<|>";

	while ((*end != '\0' && ft_strchr(delimiters, *end) == NULL
			&& ft_strchr(" ", *end) == NULL)
		|| (g_data->cmd_lst->bcomillas == 1
			|| g_data->cmd_lst->bcomillas2 == 1))
	{
		g_data->bspaces++;
		if (*end != ' ' && ft_strchr(delimiters, *end) == NULL)
			g_data->bspaces = 0;
		if (*end == '"')
			check_marks(g_data, 0);
		if (*end == '\'')
			check_marks(g_data, 1);
		end++;
		if (*end == '\0')
			break ;
		if (*end != '\0' && ft_strchr(delimiters, *end) != NULL
			&& ft_strchr(" ", *end) != NULL
			&& (g_data->cmd_lst->bcomillas == 1
				|| g_data->cmd_lst->bcomillas2 == 1))
			end++;
	}
	return (end);
}

char	*count_quotes1(t_data *g_data, char *end)
{
	const char	delimiters[] = "<|>";

	while (*end != '\0' && (ft_strchr(" ", *end) == NULL
			&& ft_strchr(delimiters, *end) == NULL))
	{
		if (*end == '"')
			check_marks(g_data, 0);
		if (*end == '\'')
			check_marks(g_data, 1);
		end++;
	}
	return (end);
}

char	*count_quotes(t_data *g_data, char *end)
{
	if (g_data->cmd_lst != NULL && (g_data->cmd_lst->bcomillas == 1
			|| g_data->cmd_lst->bcomillas2 == 1))
	{
		g_data->cmd_lst->bcomillas = 0;
		g_data->cmd_lst->bcomillas2 = 0;
	}
	if (g_data->cmd_lst != NULL && (g_data->cmd_lst->infile_tag == 1
			|| g_data->cmd_lst->infile_tag == 2
			|| g_data->cmd_lst->outfile_tag == 1
			|| g_data->cmd_lst->outfile_tag == 2))
		end = count_quotes1(g_data, end);
	end = count_quotes3(g_data, end);
	return (end);
}
