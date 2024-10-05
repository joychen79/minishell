/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:50:56 by rrimonte          #+#    #+#             */
/*   Updated: 2024/05/10 21:38:59 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	utils_c(char **oldpwd, char *newpwd, char **tmp)
{
	if (newpwd == NULL)
	{
		free(*oldpwd);
		free(*tmp);
		return (1);
	}
	return (0);
}

int	utils2_c(char *oldpwd, char **tmp)
{
	if (oldpwd == NULL)
	{
		free(*tmp);
		return (1);
	}
	return (0);
}

void	free_cd(char **oldpwd, char **newpwd, char **tmp)
{
	free(*oldpwd);
	free(*newpwd);
	free(*tmp);
}
