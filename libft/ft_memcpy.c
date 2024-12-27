/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:19:49 by ndonaire          #+#    #+#             */
/*   Updated: 2024/12/27 08:47:11 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*a;
	const char		*b;
	unsigned int	i;

	a = dst;
	i = 0;
	b = src;
	if (a == NULL && b == NULL)
		return (0);
	while (i < n)
	{
		a[i] = b[i];
		i = i + 1;
	}
	dst = a;
	return (dst);
}
