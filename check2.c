/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:39:51 by rrimonte          #+#    #+#             */
/*   Updated: 2024/05/10 02:44:17 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_check_quotes(int *count, int *count2, int *qt, int *qtd)
{
	*count = 0;
	*count2 = 0;
	*qt = 0;
	*qtd = 0;
}

void	ft_end(t_data *g_data, t_env *envp)
{
	int	end;

	end = 0;
	if (g_data->bexit == 1)
	{
		end = g_data->exit_status;
		ft_free_end(g_data, envp);
		exit(end);
	}
}
