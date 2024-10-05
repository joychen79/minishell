/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:08:36 by rrimonte          #+#    #+#             */
/*   Updated: 2024/05/10 23:06:03 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_build_cmd(t_data *g_data, char *tmp)
{
	int	i;

	i = 0;
	if (g_data->cmd_lst->infile_tag == 1
		|| g_data->cmd_lst->outfile_tag == 1
		|| g_data->cmd_lst->infile_tag == 2
		|| g_data->cmd_lst->outfile_tag == 2)
	{
		tmp = ft_erase_quotes(g_data, 0, 0, 0);
		free(g_data->cmd_lst->cmdaux);
		g_data->cmd_lst->cmdaux = tmp;
	}
	if (g_data->cmd_lst->infile_tag == 0 && g_data->cmd_lst->outfile_tag == 0)
	{
		g_data->cmd_lst->cmd = ft_split_limit(g_data->cmd_lst->cmdaux, ' ');
		while (g_data->cmd_lst->cmd[i])
		{
			g_data->cmd_lst->cmd[i] = malloc_word(g_data->cmd_lst->cmd[i],
					g_data);
			i++;
		}
	}
}

void	ft_init_count_builtins(t_data *g_data)
{
	g_data->i = 0;
	g_data->x = 0;
	g_data->z = 0;
	g_data->len = 0;
	g_data->lenaux = 0;
	g_data->lenaux2 = 0;
	g_data->lentotal = 0;
	g_data->len = ft_strlen(g_data->cmd_lst->cmdaux);
	g_data->cmdtemp = NULL;
}

void	ft_count_builtins2(t_data *g_data, char *tmp, int position)
{
	int	j;

	j = 0;
	while (g_data->len > g_data->x)
	{
		if (g_data->x == position)
		{
			g_data->x = g_data->x + g_data->lenaux2;
			if (tmp != NULL)
			{
				while (tmp[j])
				{
					g_data->cmdtemp[g_data->z] = tmp[j];
					g_data->z++;
					j++;
				}
			}
			if (g_data->len + g_data->lentotal == g_data->z)
				g_data->z--;
		}
		if (g_data->cmd_lst->cmdaux[g_data->x])
			g_data->cmdtemp[g_data->z] = g_data->cmd_lst->cmdaux[g_data->x];
		g_data->z++;
		g_data->x++;
	}
}

char	*ft_count_builtins3(t_data *g_data, t_env *envp, char *tmp, int pst)
{
	tmp = ft_obtain_global_value(g_data, envp, tmp);
	if (g_data->lenaux2 == 0)
		tmp = ft_exist_value(g_data, envp, tmp, pst);
	g_data->lentotal = g_data->lenaux - g_data->lenaux2;
	g_data->cmdtemp = (char *)malloc (sizeof(char) * g_data->len
			+ g_data->lentotal + 1);
	g_data->x = 0;
	g_data->z = 0;
	ft_count_builtins2(g_data, tmp, pst);
	g_data->cmdtemp[g_data->z] = '\0';
	free(g_data->cmd_lst->cmdaux);
	g_data->len = ft_strlen(g_data->cmdtemp);
	g_data->cmd_lst->cmdaux = (char *)malloc (sizeof(char) * g_data->len + 1);
	g_data->z = 0;
	while (g_data->cmdtemp[g_data->z])
	{
		g_data->cmd_lst->cmdaux[g_data->z] = g_data->cmdtemp[g_data->z];
		g_data->z++;
	}
	g_data->cmd_lst->cmdaux[g_data->z] = '\0';
	free(tmp);
	free(g_data->cmdtemp);
	g_data->i = -1;
	return (tmp);
}

void	ft_count_builtins(t_data *g_data, t_env *envp)
{
	char	*tmp;
	int		position;

	position = 0;
	tmp = NULL;
	g_data->i = 0;
	ft_init_count_builtins(g_data);
	if (g_data->cmd_lst->infile_tag == 0)
	{
		while (g_data->len > g_data->i)
		{
			g_data->lenaux2 = 0;
			ft_compare_marks(g_data, g_data->i);
			if (g_data->cmd_lst->cmdaux[g_data->i] == '$'
				&& g_data->cmd_lst->bcomillas2 == 0)
			{
				if (g_data->cmd_lst->cmdaux[g_data->i + 1] == '\0')
					break ;
				position = g_data->i;
				tmp = ft_count_builtins3(g_data, envp, tmp, position);
			}
			g_data->i++;
		}
	}
	ft_build_cmd(g_data, tmp);
}
