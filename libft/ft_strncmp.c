/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:08:22 by ndonaire          #+#    #+#             */
/*   Updated: 2022/03/09 09:51:14 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((unsigned char)*(s1 + i) == (unsigned char)*(s2 + i))
	{
		i = i + 1;
		if (i >= n)
			return ((unsigned char)*(s1 + i - 1)
				- (unsigned char)*(s2 + i - 1));
		if ((unsigned char)*(s1 + i) == '\0'
			|| (unsigned char)*(s2 + i) == '\0')
			return ((unsigned char)*(s1 + i) - (unsigned char)*(s2 + i));
	}
	return ((unsigned char)*(s1 + i) - (unsigned char)*(s2 + i));
}
