/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:10:57 by ndonaire          #+#    #+#             */
/*   Updated: 2022/03/09 09:50:06 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			a;
	unsigned char	*t;
	unsigned char	*y;

	if (n == 0)
		return (0);
	t = (unsigned char *)s1;
	y = (unsigned char *)s2;
	a = 0;
	while (*(t + a) == *(y + a))
	{
		a = a + 1;
		if (a >= n)
			return (*(t + a - 1) - *(y + a - 1));
	}
	return (*(t + a) - *(y + a));
}
