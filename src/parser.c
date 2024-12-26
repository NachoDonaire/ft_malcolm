#include <ft_malcolm.h>
#include <libft.h>
#include <parser.h>

int	copy_data(char *src, char *dst, int e)
{
	int i;
	int y;

	i = 0;
	y = 0;
	if (e == 0)
	{
		while (src[i])
		{
			dst[y++] = src[i++];
			if (src[i] == '.')
				i++;
			if (!src[i])
			{
				ft_bzero(dst, y);
				return (IP_ERR);
			}
		}
		return (OK);
	}
	while (src[i])
	{
		dst[y++] = src[i++];
		if (src[i] == ':')
		{
			i++;
			if (src[i] == ':')
				i++;
			else
			{
				ft_bzero(dst, y);
				return (MAC_ERR);
			}
		}
	}
	return (OK);
}




		

int is_str_num(char *s, int e)
{
	if (e == 0)
	{
		for (unsigned long i = 0; i < ft_strlen(s); i++)
		{
			if (!ft_isdigit(s[i]))
				return (-1);
		}
		return (1);
	}
	for (unsigned long i = 0; i < ft_strlen(s); i++)
	{
		if (!ft_isdigit(s[i]) && !ft_isalpha(s[i]))
			return (-1);
	}
	return (1);
}

unsigned long dp_len(char **dp)
{
	int i = 0;

	while (dp[i])
		i++;
	return (i);
}

int ip_checker(char *iprd, char *ipwr)
{
	char **octects = ft_split(iprd, '.');

	if (dp_len(octects) != 4)
		return (-1);
	for (unsigned long i = 0; i < 4; i++)
	{
		if (ft_strlen(octects[i]) > 3 || is_str_num(octects[i], 0) == -1)
			return (-1);
	}
	return (copy_data(iprd, ipwr, 0));
}

int parse_args(char **argv, struct  Target *t, struct Source *s)
{
	if (ip_checker(argv[0], &t->ip_addr[0]) == -1 || ip_checker(argv[2], &s->ip_addr[0]) == -1)
		return (IP_ERR);
	return (OK);
}
