#include <global.h>
#include <general.h>
#include <utils.h>
#include <log.h>

int	is_hex(char e)
{
	if ((e >= '0' && e <= '9') || (e >= 'a' && e <= 'f') || (e >= 'A' && e <= 'F'))
	{
		return (OK);
	}
	return (-1);
}

int	check_mac_address(char *mac)
{
	int i;

	if (ft_strlen(mac) != MAC_LEN)
		return (-1);
	i = 0;
	while (i < MAC_LEN)
	{
		if ((i + ONE) % THREE == 0 && mac[i] != ':')
			return (-1);
		else if ((i + ONE) % 3 != 0)
		{
			if (is_hex(mac[i]) != OK)
			{
				return (-1);
			}
		}
		i++;
	}

	return (OK);
}

int parse_argv(char **argv, Global *data)
{
	char	ips[sizeof(struct in_addr)];
	int	status;

	status = 1;

	if ((status = inet_pton(AF_INET, argv[1], ips)) <= 0)
		return (ERR_IP_INVALID_ST);

	if ((status = check_mac_address(argv[2])) < 0)
		return (ERR_MAC_INVALID_ST);

	ft_memset(ips, 0, sizeof(struct in_addr));
	if ((status = inet_pton(AF_INET, argv[3], ips)) <= 0)
		return (ERR_IP_INVALID_ND);

	if ((status = check_mac_address(argv[4])) < 0)
		return (ERR_MAC_INVALID_ND);
	
	data->src_ip = ft_strdup(argv[1]);
	data->src_addr = ft_strdup(argv[2]);
	data->target_ip = ft_strdup(argv[3]);
	data->target_addr = ft_strdup(argv[4]);

	return (OK);
}
