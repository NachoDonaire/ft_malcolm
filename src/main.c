#include <general.h>
#include <log.h>
#include <utils.h>
#include <global.h>
#include <arp_packet.h>
#include <eth_header.h>
#include <parser.h>

struct GlobalData data;

void	program_interruption()
{
	data.go_on = 0;
	close(data.raw_socket);
	write_on_error("\nInterruption detected. Stopping execution just right now...\n");
	return ;
}

int	initialize_data(struct sigaction *sigact, struct arp_packet *etharp, struct eth_header *ethdata, int *n_bytes_ridden, unsigned char *buf)
{
	sigact->sa_flags = 0;
	sigact->sa_handler = program_interruption;
	sigaction(SIGINT, sigact, NULL);

	*n_bytes_ridden = 0;

	data.go_on = 1;
	if ((data.raw_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0)
		return (ERR_SOCK);

	ft_memset(etharp, 0, sizeof(struct arp_packet));
	ft_memset(ethdata, 0, sizeof(struct eth_header));
	ft_memset(buf, 0, sizeof(buf));

	return (OK);
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



int main(int argc, char **argv)
{
	struct	sigaction	sigact;
	unsigned char		buf[ARP_PACKET_SIZE];
	int			n_bytes_ridden;
	struct	arp_packet	etharp;
	struct	eth_header	ethdata;
	int			status;
	unsigned char		response[ARP_PACKET_SIZE];

	if (argc != 5)
		return (error_log(ERR_NPARAMS, argv));

	if ((status = parse_argv(argv, &data)) != OK)
		return (error_log(status, argv));

	if ((status = initialize_data(&sigact, &etharp, &ethdata, &n_bytes_ridden, buf)) <= 0)
		return (error_log(status, argv));
	
	while (data.go_on)
	{
		n_bytes_ridden = recvfrom(data.raw_socket, buf, ARP_PACKET_SIZE, 0, NULL, 0);

		if (!data.go_on)
			return (0);

		if (n_bytes_ridden < ETH_HEADER_SIZE)
			return (error_log(ERR_RECVPACKET, argv));
		else
		{
			parse_eth_header(buf, &ethdata);
			if ((!protocol_cmp(ethdata.protocol, ARP_PROTOCOL)))
				return (error_log(ERR_PROTOCOL, argv));
			if (!macaddr_cmp(ethdata.sender_ethaddr, data.target_addr))
			{
				malcolm_log("Got a packet from a different source than requested: ");
				print_addr(ethdata.sender_ethaddr);
				n_bytes_ridden = 0;
				ft_memset(buf, 0, sizeof(buf));
				ft_memset(&ethdata, 0, sizeof(struct eth_header));
			}
			else
			{
				print_eth_header(ethdata);
				printf("\n\n\n");
				parse_arp_packet(buf + ETH_HEADER_SIZE, &etharp);
				if (!check_request(etharp, data.src_ip))
				{
					malcolm_log("Got a packet from desired target but it is requesting other IP address: ");
					print_ip(etharp.target_pro_address);
					n_bytes_ridden = 0;
					ft_memset(buf, 0, sizeof(buf));
					ft_memset(&ethdata, 0, sizeof(struct eth_header));
					ft_memset(&etharp, 0, sizeof(struct arp_packet));
				}
				else
				{
					printf("CHECK REQUEST: %d\n", check_request(etharp, data.src_ip));
					print_arpdata(etharp);
					printf("\n\n\n");
					ft_memset(response, 0, sizeof(response));
					printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeee :%s\n ", data.target_addr);
					printf("\n\n\n");
					generate_arp_packet(data.target_addr, data.target_ip, data.src_addr, data.src_ip, REPLY, response);
					//malcolm_log((char *)response);
					//printf("%lu\n", ft_strlen((char *)response));
					struct	eth_header	response_header;
					parse_eth_header(response, &response_header);
					print_eth_header(response_header);
					struct	arp_packet	reply;
					parse_arp_packet(response + ETH_HEADER_SIZE, &reply);
					print_arpdata(reply);
					data.go_on = ZERO;
					close(data.raw_socket);
				}
			}
			

		}
	}

	return (0);
}
