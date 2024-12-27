/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 21:17:29 by ndonaire          #+#    #+#             */
/*   Updated: 2022/03/09 09:52:28 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*x;
	int		i;

	i = 0;
	while (s1[i] != '\0')
		i = i + 1;
	x = (char *)malloc(i * sizeof(char) + 1);
	if (!x)
		return (0);
	i = 0;
	while (*(s1 + i) != '\0')
	{
		x[i] = s1[i];
		i = i + 1;
	}
	*(x + i) = '\0';
	return ((char *)x);
}
