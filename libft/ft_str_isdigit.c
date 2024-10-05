/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:56:35 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/22 18:09:11 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isdigit(char *str)
{
	int	n;

	n = 0;
	if (str[n] == '-' || str[n] == '+')
		n++;
	while (str[n])
	{
		if (!ft_isdigit(str[n]))
			return (0);
		n++;
	}
	return (1);
}
