/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:44:17 by ndonaire          #+#    #+#             */
/*   Updated: 2024/12/27 08:49:23 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	lens(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static int	set_char(const char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	cmp(char const *s1, char const *set, int i)
{
	while (set_char(s1[i], set) && s1[i])
		i++;
	return (i);
}

static char	*value_x(const char *s1, int i, int y, char *x)
{
	int	z;

	z = 0;
	while (i < y)
	{
		x[z] = s1[i];
		i++;
		z++;
	}
	x[z] = '\0';
	return (x);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		y;
	char	*x;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	y = lens(s1);
	i = cmp(s1, set, i);
	if (i == y)
	{
		x = malloc((y - i + 1) * sizeof(char));
		x[0] = '\0';
		return ((char *)x);
	}
	while (set_char(s1[y - 1], set) && y > 0)
		y--;
	x = malloc((y - i + 1) * sizeof(char));
	if (!x)
		return (0);
	x = value_x(s1, i, y, x);
	return (x);
}
