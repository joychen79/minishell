/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:48:05 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/28 10:48:31 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_quotes(int qt, int qtd, int option)
{
	if (option == 0)
	{
		if (qtd == 0)
			qtd = 1;
		else
			qtd = 0;
		return (qtd);
	}
	if (option == 1)
	{
		if (qt == 0)
			qt = 1;
		else
			qt = 0;
		return (qt);
	}
	return (0);
}

void	init_qt(int *qt, int *qtd)
{
	*qt = 0;
	*qtd = 0;
}
