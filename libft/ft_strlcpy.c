/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:22:39 by ndonaire          #+#    #+#             */
/*   Updated: 2022/03/22 10:09:29 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

static int	lens(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	char			*a;
	const char		*b;
	char			aux;

	i = 0;
	a = dst;
	b = src;
	if (dstsize == 0)
		return (lens(src));
	while (b[i] != '\0' && i < dstsize - 1)
	{
		aux = b[i];
		a[i] = aux;
		i = i + 1;
	}
	a[i] = '\0';
	i = 0;
	while (b[i] != '\0')
	{
		i = i + 1;
	}
	dst = a;
	return (i);
}
