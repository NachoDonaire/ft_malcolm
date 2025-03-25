#include <ft_malcolm.h>
#include <libft.h>
#include <parser.h>

int ft_ishex(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))
		return (1);
	return (0);
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
		if (!ft_isdigit(s[i]) && !ft_ishex(s[i]))
			return (-1);
	}
	return (1);
}

void	dp_free(char **dp)
{
	int i;

	i = 0;
	while (dp[i])
	{
		free(dp[i++]);
	}
	free(dp);
}

unsigned long dp_len(char **dp)
{
	int i = 0;

	while (dp[i])
		i++;
	return (i);
}

int ip_checker(char *iprd, char **ipwr)
{
	if  (iprd[0] == '.' || iprd[ft_strlen(iprd) - 1] == '.')
		return (-1);
	char **octects = ft_split(iprd, '.');

	ft_bzero(ipwr, 0);
	if (dp_len(octects) != 4)
		return (-1);
	for (unsigned long i = 0; i < 4; i++)
	{
		if (ft_strlen(octects[i]) > 3 || is_str_num(octects[i], 0) == -1)
			return (-1);
	}
	dp_free(octects);
	*ipwr = iprd;
	return (OK);
}

int mac_checker(char *macrd, char **macwr)
{
	if  (macrd[0] == ':' || macrd[ft_strlen(macrd) - 1] == ':')
		return (-1);
	char **hex_addr = ft_split(macrd, ':');

	ft_bzero(macwr, 0);
	if (dp_len(hex_addr) != 6)
		return (-1);
	for (unsigned long i = 0; i < 6; i++)
	{
		if (ft_strlen(hex_addr[i]) > 2 || is_str_num(hex_addr[i], 1) == -1)
			return (-1);
	}
	dp_free(hex_addr);
	*macwr = macrd;
	return (OK);
}

int parse_args(char **argv, struct  Target *t, struct Source *s)
{
	t->ip_addr = NULL;
	s->ip_addr = NULL;
	t->mac_addr = NULL;
	s->mac_addr = NULL;
	if (ip_checker(argv[0], &t->ip_addr) == -1 || ip_checker(argv[2], &s->ip_addr) == -1)
		return (IP_ERR);
	if (mac_checker(argv[1], &t->mac_addr) == -1 || mac_checker(argv[3], &s->mac_addr) == -1)
		return (MAC_ERR);
	return (OK);
}
