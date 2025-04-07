#include <utils.h>

void	free_double_pointer(char **s)
{
	int i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

uint32_t	get_ippos(unsigned int pos, uint32_t rawson)
{
	uint32_t	dikie_wilkinson;
	uint8_t		the_chosen_one;

	dikie_wilkinson = rawson;
	if (pos == 0)
		the_chosen_one = dikie_wilkinson >> 24;
	else if (pos == 1)
		the_chosen_one = dikie_wilkinson >> 16;
	else if (pos == 2)
		the_chosen_one = dikie_wilkinson >> 8;
	else
		the_chosen_one = dikie_wilkinson;
	
	return the_chosen_one;
}

int	protocol_cmp(uint16_t p1, uint16_t p2)
{
	if (p1 == p2)
		return (OK);
	return (ERR);
}

int	macaddr_cmp(uint8_t *a, char *b)
{
	int		y;
	char		byte[THREE];

	y = 0;
	ft_memset(byte, 0, sizeof(byte));

	for (int i = 0; i < ADDR_LEN; i++)
	{
		if (b[y] == ':')
			y++;
		sprintf(byte, "%02x", a[i]);
		if (byte[ZERO] != b[y] || byte[ONE] != b[y + ONE])
			return (ERR);
		ft_memset(byte, 0, sizeof(byte));
		y += 2;
	}
	
	return (OK);
}

int	is_broadcast(uint8_t *mac)
{
	for (int i = 0; i < ADDR_LEN; i++)
		if (mac[i] != 255)
			return (ERR);
	return (OK);
}

int	check_request(struct arp_packet etharp, char *ip)
{
	unsigned char	raw_arg_ip[FOUR];
	unsigned char	raw_pack_ip[FOUR];

	ft_memset(raw_arg_ip, 0, FOUR);
	ft_memset(raw_pack_ip, 0, FOUR);
	for (int i = 0; i < FOUR; i++)
		raw_pack_ip[i] = get_ippos(i, etharp.target_pro_address);
	cpy_ip(raw_arg_ip, ip);
	for (int i = 0; i < FOUR; i++)
		if (raw_arg_ip[i] != raw_pack_ip[i])
			return (ERR);
	return (OK);
}





void	onetotwo(uint8_t wolfgang, uint8_t amadeus, uint16_t *m)
{
	*m = (wolfgang << 8) | amadeus;
}

void	onetofour(uint8_t *wolfgangs, uint32_t *m)
{
	*m = (((wolfgangs[0] << 24) | (wolfgangs[1] << 16)) | wolfgangs[2] << 8) | wolfgangs[3];
}

void	packet_address(uint8_t *filled, uint8_t *msg)
{
	for (int i = 0; i < ADDR_LEN; i++)
	{
		filled[i] = msg[i];
	}
}

void	fillfourbytes(uint8_t *laquesis, uint8_t *msg)
{
	for (int i = 0; i < FOUR; i++)
	{
		laquesis[i] = msg[i];
	}
}
