#include <general.h>
#include <log.h>
#include <utils.h>
#include <global.h>
#include <eth_header.h>
#include <parser.h>
#include <send_packet.h>

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

	data.addrlen = sizeof(data.comminfo);
	data.go_on = 1;
	if ((data.raw_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0)
		return (ERR_SOCK);

	ft_memset(etharp, 0, sizeof(struct arp_packet));
	ft_memset(ethdata, 0, sizeof(struct eth_header));
	ft_memset(&data.comminfo, 0, sizeof(struct sockaddr_ll));
	ft_memset(buf, 0, sizeof(buf));

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
		n_bytes_ridden = recvfrom(data.raw_socket, buf, ARP_PACKET_SIZE, 0, (struct sockaddr *)&data.comminfo, &data.addrlen);

		if (!data.go_on)
			return (0);

		if (n_bytes_ridden < ETH_HEADER_SIZE)
			return (error_log(ERR_RECVPACKET, argv));
		else
		{
			parse_eth_header(buf, &ethdata);
			if ((!protocol_cmp(ethdata.protocol, ARP_PROTOCOL)))
				return (error_log(ERR_PROTOCOL, argv));
			//printf("EEEEEEEEEEEE: %d\n", macaddr_cmp(ethdata.sender_ethaddr, data.target_addr));
			if (!macaddr_cmp(ethdata.sender_ethaddr, data.target_addr))
			{
				n_bytes_ridden = ONE;
				malcolm_log("Got packet from a different MAC address than requested: ", ethdata.sender_ethaddr, ZERO, &n_bytes_ridden, buf);
			}
			else if (!is_broadcast(ethdata.dest_ethaddr))
			{
				n_bytes_ridden = ONE;
				malcolm_log("Beware, the packet was not send on broadcast. Sender is focusing: ", ethdata.sender_ethaddr, ZERO, &n_bytes_ridden, buf);
			}
			else
			{
				print_eth_header(ethdata);
				printf("\n\n\n");
				parse_arp_packet(buf + ETH_HEADER_SIZE, &etharp);

				if (!check_request(etharp, data.src_ip))
				{
					n_bytes_ridden = TWO;
					malcolm_log("Got packet from desired target but it is requesting other IP address: ", NULL, etharp.target_pro_address, &n_bytes_ridden, buf);
				}
				else
				{
					//printf("CHECK REQUEST: %d\n", check_request(etharp, data.src_ip));
					print_arpdata(etharp);
					printf("\n\n\n");
					ft_memset(response, 0, sizeof(response));
					//printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeee :%s\n ", data.target_addr);
					printf("\n\n\n");
					generate_arp_packet(data.target_addr, data.target_ip, data.src_addr, data.src_ip, REPLY, response);
					//sleep(1);
					if (send_packet(response, data.src_ip, data.raw_socket, &data) != OK)
						return (error_log(ERR_SEND, argv));
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
