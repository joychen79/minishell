/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:19:22 by jingchen          #+#    #+#             */
/*   Updated: 2024/05/10 01:06:44 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int	empty_value(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '=')
		{
			return (1);
			break ;
		}
		i++;
	}
	return (0);
}

int	ft_env(t_env *env)
{
	if (!env)
		return (1);
	while (env)
	{
		if (empty_value(env->value) == 1)
			printf("%s\n", env->value);
		env = env->next;
	}
	return (0);
}
