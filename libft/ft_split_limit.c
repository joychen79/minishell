/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_limit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:19:52 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/28 11:26:36 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_limit(char **pt)
{
	int	i;

	i = 0;
	while (pt[i])
	{
		free(pt[i]);
		i++;
	}
	free(pt);
}

char	**checkmalloc_1(char *s2, size_t *x, char c, char **pt)
{
	int	qt;
	int	qtd;

	init_qt(&qt, &qtd);
	while (s2[x[0]])
	{
		if (s2[x[0]] == '"' && qt == 0)
			qtd = ft_quotes(qt, qtd, 0);
		else if (s2[x[0]] == '\'' && qtd == 0)
			qt = ft_quotes(qt, qtd, 1);
		if ((s2[x[0]] == c && s2[x[0] + 1] != c && qt == 0 && qtd == 0))
		{
			pt[x[1]] = (char *)malloc((x[2] + 1) * sizeof(char));
			error_malloc(pt);
			x[1]++;
			x[2] = 0;
		}
		else if (s2[x[0]] != c || qt == 1 || qtd == 1)
			x[2]++;
		pt = checkmalloc_2(s2, x, pt);
		if (pt == 0)
			break ;
	}
	return (pt);
}

static char	**f_writ(char *s2, char **pt, size_t *x, char c)
{
	int	qt;
	int	qtd;

	init_qt(&qt, &qtd);
	while (s2[x[0]])
	{
		if (s2[x[0]] == '"' && qt == 0)
			qtd = ft_quotes(qt, qtd, 0);
		else if (s2[x[0]] == '\'' && qtd == 0)
			qt = ft_quotes(qt, qtd, 1);
		if ((s2[x[0]] == c && s2[x[0] + 1] != c && qt == 0 && qtd == 0))
		{
			pt[x[1]][x[2]] = '\0';
			x[1] = x[1] + 1;
			x[2] = 0;
		}
		else if (s2[x[0]] != c || qt == 1 || qtd == 1)
		{
			pt[x[1]][x[2]] = s2[x[0]];
			x[2] = x[2] + 1;
		}
		pt = f_writ_2(s2, pt, x);
	}
	pt[x[1]] = 0;
	return (pt);
}

static char	**asg(char *s2, size_t *x, char c)
{
	char	**pt;
	int		qt;
	int		qtd;

	init_qt(&qt, &qtd);
	if (s2 == 0)
		return (0);
	while (s2[x[0]])
	{
		if (s2[x[0]] == '"' && qt == 0)
			qtd = ft_quotes(qt, qtd, 0);
		else if (s2[x[0]] == '\'' && qtd == 0)
			qt = ft_quotes(qt, qtd, 1);
		if (s2[x[0]] == c && s2[x[0] + 1] != c && qt == 0 && qtd == 0)
			x[2]++;
		x[0]++;
	}
	x[0] = 0;
	pt = (char **) malloc ((x[2] + 1) * sizeof(char *));
	if (pt == 0)
		return (pt);
	pt = asg_2(s2, x, c, pt);
	return (pt);
}

char	**ft_split_limit(char const *s, char c)
{
	char	**pt;
	char	*s2;
	char	ac[2];
	size_t	x[3];

	ft_bzero (&x, 3 * sizeof(size_t));
	x[2] = 1;
	ac[0] = ' ';
	ac[1] = '\0';
	s2 = ft_strtrim(s, ac);
	if (s2 == 0)
	{
		free(s2);
		return (0);
	}
	pt = asg(s2, x, c);
	if (pt != 0)
	{
		x[0] = 0;
		x[1] = 0;
		x[2] = 0;
		pt = f_writ(s2, pt, x, c);
	}
	free(s2);
	return (pt);
}
