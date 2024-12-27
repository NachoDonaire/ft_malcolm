/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:27:14 by ndonaire          #+#    #+#             */
/*   Updated: 2024/12/27 08:47:49 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int	a;

	a = 0;
	while (*(s + a) != (unsigned char)c)
	{
		if (*(s + a) == '\0')
			return (0);
		a = a + 1;
	}
	return ((char *)(s + a));
}
