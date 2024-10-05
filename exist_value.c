/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exist_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:11:37 by rrimonte          #+#    #+#             */
/*   Updated: 2024/05/10 00:49:39 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_obtain_global_value(t_data *g_data, t_env *envp, char *tmp)
{
	if (g_data->cmd_lst->cmdaux[g_data->i + 1])
	{
		if (g_data->cmd_lst->cmdaux[g_data->i + 1] == '?')
		{
			g_data->lenaux2 = 2;
			tmp = var_expansion("$?", envp, &g_data->exit_status);
			g_data->lenaux = ft_strlen(tmp);
			g_data->i++;
		}
	}
	return (tmp);
}

void	ft_exist_value2(t_data *g_data)
{
	while (g_data->cmd_lst->cmdaux[g_data->i]
		&& ft_isalnum(g_data->cmd_lst->cmdaux[g_data->i]) == 1)
	{
		g_data->cmdtemp[g_data->z] = g_data->cmd_lst->cmdaux[g_data->i];
		g_data->i++;
		g_data->z++;
	}
}

char	*ft_exist_value(t_data *g_data, t_env *envp, char *tmp, int position)
{
	g_data->i++;
	g_data->lenaux2++;
	while (g_data->cmd_lst->cmdaux[g_data->i]
		&& ft_isalnum(g_data->cmd_lst->cmdaux[g_data->i]) == 1)
	{
		g_data->lenaux2++;
		g_data->i++;
	}
	g_data->i = position;
	g_data->cmdtemp = (char *)malloc (sizeof(char) * g_data->lenaux2 + 1);
	g_data->z = 0;
	g_data->cmdtemp[g_data->z] = g_data->cmd_lst->cmdaux[g_data->i];
	g_data->i++;
	g_data->z++;
	ft_exist_value2(g_data);
	g_data->cmdtemp[g_data->z] = '\0';
	tmp = var_expansion(g_data->cmdtemp, envp, &g_data->exit_status);
	free (g_data->cmdtemp);
	if (tmp != NULL)
		g_data->lenaux = ft_strlen(tmp);
	else
		g_data->lenaux = 0;
	return (tmp);
}
