#include <log.h>
#include <unistd.h>

int	write_on_error(char *s)
{
	int i = 0;

	while (s[i])
		write(2, &s[i++], 1);
	return (-1);
}

int	malcolm_log(char *s)
{
	int i = 0;

	while (s[i])
		write(1, &s[i++], 1);
	return (OK);
}

void	print_addr(uint8_t *addr)
{
	for (unsigned int i = 0; i < ADDR_LEN; i++)
	{
		if (i == FIVE)
			printf("%02x\n", addr[i]);
		else
			printf("%02x:", addr[i]);
	}
}



int error_log(int error, char **argv)
{
	switch (error)
	{
		case ERR_NPARAMS:
			write_on_error("Usage:\n./ft_malcolm <src_ip> <src_addr> <target_ip> <target_addr>\n");
			break;
		case ERR_IP_INVALID_ST:
			write_on_error("Unknown host or invalid IP address: ");
			write_on_error(argv[1]);
			write_on_error("\n");
			break;
		case ERR_IP_INVALID_ND:
			write_on_error("Unknown host or invalid IP address: ");
			write_on_error(argv[3]);
			write_on_error("\n");
			break;
		case ERR_MAC_INVALID_ST:
			write_on_error("Invalid mac address: ");
			write_on_error(argv[2]);
			write_on_error("\n");
			break;
		case ERR_MAC_INVALID_ND:
			write_on_error("Invalid mac address: ");
			write_on_error(argv[4]);
			write_on_error("\n");
			break;
		case ERR_SOCK:
			write_on_error("Fail when creating socket\n");
			break;
		case ERR_RECVPACKET:
			write_on_error("Error when receiving package. Too light\n");
			break;
		case ERR_PROTOCOL:
			write_on_error("Package received may not follow ARP protocol\n");
			break;

	}
	return (ERR);
}
