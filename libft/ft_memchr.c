/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:09:33 by ndonaire          #+#    #+#             */
/*   Updated: 2022/03/09 09:49:55 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			a;
	unsigned char	*t;

	t = (unsigned char *)s;
	a = 0;
	while (a < n)
	{
		if (*(t + a) == (unsigned char)c)
			return ((void *)(t + a));
		a = a + 1;
	}
	return (0);
}
