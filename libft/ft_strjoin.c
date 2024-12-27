/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 09:43:25 by ndonaire          #+#    #+#             */
/*   Updated: 2024/12/27 08:49:00 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	lens(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i = i + 1;
	return (i);
}

static char	*copy(const char *s1, const char *s2, char *x)
{
	int		i;
	int		y;
	char	aux;

	i = 0;
	y = 0;
	while (s1[i])
	{
		aux = s1[i];
		x[i] = aux;
		i++;
	}
	while (s2[y])
	{
		aux = s2[y];
		x[i] = aux;
		y++;
		i++;
	}
	x[i] = '\0';
	return (x);
}

static char	*cncat(const char *s1, const char *s2)
{
	char	*x;

	if (s1 && s2)
	{
		x = malloc((lens(s1) + lens(s2) + 1) * sizeof(char));
		if (!x)
			return (0);
		x = copy(s1, s2, x);
		return (x);
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*x;

	if (s1 && s2)
	{
		x = cncat(s1, s2);
		return (x);
	}
	return (0);
}
