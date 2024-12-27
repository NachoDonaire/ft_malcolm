/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:07:29 by ndonaire          #+#    #+#             */
/*   Updated: 2022/03/09 09:50:25 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

static int	len(const char *s)
{
	int	i;

	i = 0;
	while ((unsigned char )*(s + i))
		i = i + 1;
	return (i);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = len(s);
	while (i >= 0)
	{
		if (*(s + i) == (char)c)
			return ((char *)(s + i));
		i = i - 1;
	}
	return (0);
}
