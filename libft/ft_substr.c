/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 09:41:07 by ndonaire          #+#    #+#             */
/*   Updated: 2024/12/27 08:48:22 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

static char	*subs(char const *s, unsigned int start, size_t len, char *x)
{
	unsigned int	i;
	unsigned int	y;

	i = 0;
	y = 0;
	while (s[i])
	{
		if (i >= start && y < len)
		{
			x[y] = s[i];
			y++;
		}
		i = i + 1;
	}
	x[y] = '\0';
	return (x);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*x;

	if (!s)
		return (0);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	x = malloc(len + 1);
	if (!x)
		return (0);
	x = subs(s, start, len, x);
	return (x);
}
