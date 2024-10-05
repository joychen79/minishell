/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 00:20:18 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/28 11:55:47 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validlen2(char *s, t_data *g_data, int len)
{
	if (s[g_data->i] == '\'')
	{
		g_data->i++;
		while (s[g_data->i] && s[g_data->i] != '\'')
		{
			len++;
			g_data->i++;
		}
	}
	else if (s[g_data->i] == '"')
	{
		g_data->i++;
		while (s[g_data->i] && s[g_data->i] != '"')
		{
			len++;
			g_data->i++;
		}
	}
	else
		len++;
	return (len);
}

int	validlen(char *s, t_data *g_data)
{
	int	len;

	len = 0;
	g_data->i = 0;
	while (s[g_data->i])
	{
		len = validlen2(s, g_data, len);
		g_data->i++;
	}
	return (len);
}

char	*malloc_word2(char *s, t_data *g_data, char *new)
{
	if (s[g_data->i] == '\'')
	{
		g_data->i++;
		while (s[g_data->i] && s[g_data->i] != '\'')
		{
			new[g_data->j++] = s[g_data->i++];
		}
	}
	else if (s[g_data->i] == '"')
	{
		g_data->i++;
		while (s[g_data->i] && s[g_data->i] != '"')
		{
			new[g_data->j++] = s[g_data->i++];
		}
	}
	return (new);
}

char	*malloc_word(char *s, t_data *g_data)
{
	char	*new;

	g_data->j = 0;
	new = (char *)malloc(sizeof(char) * (validlen(s, g_data) + 1));
	g_data->i = 0;
	if (!new)
		return (NULL);
	while (s[g_data->i])
	{
		while (s[g_data->i] && s[g_data->i] != '\'' && s[g_data->i] != '"')
			new[g_data->j++] = s[g_data->i++];
		if (s[g_data->i] && (s[g_data->i] == '\'' || s[g_data->i] == '"'))
		{
			new = malloc_word2(s, g_data, new);
			g_data->i++;
		}
	}
	new[g_data->j] = '\0';
	free(s);
	return (new);
}
