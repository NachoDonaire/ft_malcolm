#include <general.h>
#include <process_arp_packet.h>
#include <parser.h>
#include <eth_header.h>
#include <arp_packet.h>
#include <utils.h>
#include <log.h>
#include <send_packet.h>

int	malcolm_process(unsigned char *buf,  struct GlobalData *data, int *n_bytes_ridden, char **argv)
{

	struct	arp_packet	etharp;
	struct	eth_header	ethdata;
	unsigned char		response[ARP_PACKET_SIZE];

	printf("Packet received from target. Its header: \n");
	print_eth_header(ethdata);
	printf("\n\n\n");
	parse_arp_packet(buf + ETH_HEADER_SIZE, &etharp);

	if (!ip_rwpntr_cmp(etharp.target_pro_address, data->src_ip))
	{
		*n_bytes_ridden = TWO;
		malcolm_log("Got packet from desired target but it is requesting other IP address: ", NULL, etharp.target_pro_address, n_bytes_ridden, buf);
	}
	else if (!ip_rwpntr_cmp(etharp.sender_pro_address, data->target_ip))
	{
		*n_bytes_ridden = TWO;
		malcolm_log("Got packet from another device: ", NULL, etharp.sender_pro_address, n_bytes_ridden, buf);
	}
	else
	{
		printf("Everything ok\nBody of arp packet: \n");
		print_arpdata(etharp);
		printf("\n\n\n");
		ft_memset(response, 0, sizeof(response));
		generate_arp_packet(data->target_addr, data->target_ip, data->src_addr, data->src_ip, REPLY, response);
		struct	eth_header	response_header;
		parse_eth_header(response, &response_header);
		struct	arp_packet	reply;
		parse_arp_packet(response + ETH_HEADER_SIZE, &reply);
		printf("Ok we are about to send this to 'target': \n");
		print_eth_header(response_header);
		print_arpdata(reply);
		if (send_packet(response, data->raw_socket, data) != OK)
			return (error_log(ERR_SEND, argv));
		printf("Sent\n");
		data->go_on = ZERO;
		close(data->raw_socket);
	}

	return (OK);

}
