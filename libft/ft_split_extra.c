/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:46:24 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/28 11:53:22 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**asg_2(char *s2, size_t *x, char c, char **pt)
{
	x[2] = 0;
	pt = checkmalloc_1(s2, x, c, pt);
	if (pt == 0)
	{
		ft_free_limit(pt);
		return (0);
	}
	return (pt);
}

char	**f_writ_2(char *s2, char **pt, size_t *x)
{
	x[0]++;
	if (s2[x[0]] == '\0')
	{
		pt[x[1]][x[2]] = '\0';
		x[1] = x[1] + 1;
	}
	return (pt);
}

char	**checkmalloc_2(char *s2, size_t *x, char **pt)
{
	x[0]++;
	if (s2[x[0]] == '\0')
		pt[x[1]] = (char *)malloc((x[2] + 1) * sizeof(char));
	if (pt == 0)
	{
		ft_free_limit(pt);
		return (0);
	}
	return (pt);
}

char	**error_malloc(char **pt)
{
	if (pt == 0)
	{
		ft_free_limit(pt);
		return (0);
	}
	return (pt);
}
