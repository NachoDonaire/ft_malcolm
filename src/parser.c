#include <eth_header.h>
#include <arp_packet.h>
#include <global.h>
#include <general.h>
#include <utils.h>
#include <some_error.h>

int	is_hex(char e)
{
	if ((e >= '0' && e <= '9') || (e >= 'a' && e <= 'f') || (e >= 'A' && e <= 'F'))
	{
		return (OK);
	}
	return (ERR_MAC_INVALID);
}

int	check_mac_address(char *mac)
{
	int i;

	if (ft_strlen(mac) != MAC_LEN)
		return (ERR_MAC_INVALID);
	i = 0;
	while (i < MAC_LEN)
	{
		if ((i + ONE) % THREE == 0 && mac[i] != ':')
			return (ERR_MAC_INVALID);
		else if ((i + ONE) % 3 != 0)
		{
			if (is_hex(mac[i]) != OK)
			{
				return (ERR_MAC_INVALID);
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
		return (some_error(ERR_IP_INVALID));

	if ((status = check_mac_address(argv[2])) < 0)
		return (some_error(status));

	ft_memset(ips, 0, sizeof(struct in_addr));
	if ((status = inet_pton(AF_INET, argv[3], ips)) <= 0)
		return (some_error(ERR_IP_INVALID));

	if ((status = check_mac_address(argv[4])) < 0)
		return (some_error(status));
	
	data->src_ip = argv[1];
	data->src_addr = argv[2];
	data->target_ip = argv[3];
	data->target_addr = argv[4];

	return (OK);
}
