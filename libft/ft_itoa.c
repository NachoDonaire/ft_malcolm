/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:12:39 by ndonaire          #+#    #+#             */
/*   Updated: 2022/03/31 14:17:27 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	lnnum(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i = i + 1;
		n = n * (-1);
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*transform(unsigned int nb, long int y, char *x)
{
	while (nb > 0)
	{
		x[y--] = 48 + (nb % 10);
		nb = nb / 10;
	}
	return (x);
}

char	*ft_itoa(int n)
{
	char			*x;
	long int		y;
	unsigned int	nb;

	y = lnnum(n);
	nb = n;
	x = (char *) malloc((y + 1) * sizeof(char));
	if (!x)
		return (NULL);
	x[y--] = '\0';
	if (n == 0)
	{
		x[0] = 0 + 48;
		return (x);
	}
	else if (n < 0)
	{
		nb = n * (-1);
		x[0] = '-';
	}
	x = transform(nb, y, x);
	return (x);
}
