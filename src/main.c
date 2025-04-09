#include <general.h>
#include <process_arp_packet.h>
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

		if (n_bytes_ridden < ZERO)
			return (error_log(ERR_RECVPACKET, argv));
		else if (n_bytes_ridden < ARP_PACKET_SIZE)
		{
				n_bytes_ridden = -1;
				malcolm_log("Packet size does not match with arp size", ethdata.sender_ethaddr, ZERO, &n_bytes_ridden, buf);
		}
		else
		{
			parse_eth_header(buf, &ethdata);
			if ((!protocol_cmp(ethdata.protocol, ARP_PROTOCOL)))
				return (error_log(ERR_PROTOCOL, argv));
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
				status = malcolm_process(buf, &data, &n_bytes_ridden, argv);
				if (status != OK)
					return (status);
			}
		}
		
	}

	return (0);
}
