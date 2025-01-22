#include <libft.h>
#include <stdio.h>
#include <ft_malcolm.h>
#include <parser.h>

void	write_sentence(int fd, char *s)
{
	for (unsigned long int i = 0; i < ft_strlen(s); i++)
		write(fd, &s[i], 1);
}



void print_target(struct Target t)
{
	write_sentence(1, "IP ADDRESS: ");
	write_sentence(1, t.ip_addr);
	write_sentence(1, "\n");
	write_sentence(1, "MAC ADDRESS: ");
	write_sentence(1, t.mac_addr);
	write_sentence(1, "\n");
	printf("Socket: %d\n", t.socket);
}


void print_source(struct Source t)
{
	write_sentence(1, "IP ADDRESS: ");
	write_sentence(1, t.ip_addr);
	write_sentence(1, "\n");
	write_sentence(1, "MAC ADDRESS: ");
	write_sentence(1, t.mac_addr);
	write_sentence(1, "\n");
	printf("Socket: %d\n", t.socket);
}

int fatal_error(int reason)
{
	if (reason == NARG_ERR)
		write_sentence(2, "Wrong number of arguments\n");
	else if (reason == IP_ERR)
		write_sentence(2, "Error in some ip address. Please, check both.\nFormat: q.q.q.q where q is value between 0 and 255\n");
	else if (reason == MAC_ERR)
		write_sentence(2, "Error in some mac address. Please, check both.\nFormat: ff:ff:ff:ff:ff:ff where ff represents a hexadecimal number\n");
	else if  (reason == SOCKET_ERR)
		write_sentence(2, "Error creating socket, exiting\n");
	else
		write_sentence(2, "Fatal error\n");
	return (-1);
}	

int main(int argc, char **argv)
{
	struct Target	target;
	struct Source	source;
	int	parse_status;
	int	sockfd;
	uint8_t buffer[ETH_HDRLEN + ARP_HDRLEN + 18];
	struct ether_arp *arp;
	//char	buff[BUFF_SIZE];
	//int	nnreadd;
	//struct sockaddr_ll	sll;

	if (argc != 5 || argv[0] == NULL)
		return (fatal_error(NARG_ERR));

	parse_status = parse_args(&argv[1], &target, &source);
	if (parse_status != OK)
		return (fatal_error(parse_status));

	if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0) {
		fatal_error(SOCKET_ERR);
	}

	while (1) {
		if (recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL) < 0) {
			fatal_error(0);
		}

		// Verificar si es un paquete ARP
		struct ethhdr *eth = (struct ethhdr *)buffer;
		if (ntohs(eth->h_proto) == ETH_P_ARP) {
			arp = (struct ether_arp *)(buffer + ETH_HDRLEN);

			// Verificar si es una solicitud ARP
			if (ntohs(arp->ea_hdr.ar_op) == ARPOP_REQUEST) {
				printf("Solicitud ARP recibida\n");
			}
		}
	}
	return (0);
}
