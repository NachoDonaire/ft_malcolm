#include <global.h>
#include <general.h>
#include <utils.h>
#include <arp_packet.h>



void	print_arpdata(struct arp_packet arpdata)
{
	printf("Hardware address space: %u\n", arpdata.has);
	printf("Protocol address space: 0x%x\n", arpdata.pas);
	printf("Hardware address length: %u\n", arpdata.hal);
	printf("Protocol address length: %u\n", arpdata.pal);
	printf("\n############################\n\n");
	printf("opcode: %u\n", arpdata.opcode);
	printf("\n############################\n\n");
	printf("source address --> ");
	for (int i = 0; i < ADDR_LEN; i++)
	{
		if (i == FIVE)
			printf("%02x\n", arpdata.sender_address[i]);
		else
			printf("%02x:", arpdata.sender_address[i]);
	}
	printf("source protocol address --> ");
	for (unsigned int i = 0; i < FOUR; i++)
	{
		if (i == THREE)
			printf("%u\n", get_ippos(i, arpdata.sender_pro_address));
		else
			printf("%u.", get_ippos(i, arpdata.sender_pro_address));
	}
	printf("\n############################\n\n");
	printf("target address --> ");
	for (int i = 0; i < ADDR_LEN; i++)
	{
		if (i == FIVE)
			printf("%02x\n", arpdata.target_address[i]);
		else
			printf("%02x:", arpdata.target_address[i]);
	}
	printf("target protocol address --> ");
	for (unsigned int i = 0; i < FOUR; i++)
	{
		if (i == THREE)
			printf("%u\n", get_ippos(i, arpdata.target_pro_address));
		else
			printf("%u.", get_ippos(i, arpdata.target_pro_address));
	}
}

void	cpy_mac(unsigned char *dst, char *mac)
{
	char	byte[THREE];
	int	y;
	int	i;
	ft_memset(dst, 0, ADDR_LEN);
	ft_memset(byte, 0, THREE);

	y = 0;
	i = 0;
	while (y < ADDR_LEN)
	{
		if ( (i + ONE) % 3 != 0)
		{
			byte[ZERO] = mac[i++];
			byte[ONE] = mac[i++];
			byte[TWO] = 0;
			sscanf(byte, "%hhx", &dst[y++]);
			ft_memset(byte, 0, THREE);
		}
		else
			i++;
	}

}


void	cpy_ip(unsigned char *dst, char *ip)
{
	char	byte[FOUR];
	int	y;
	int	i;
	int	z;

	ft_memset(dst, 0, PAL);
	ft_memset(byte, 0, FOUR);

	y = 0;
	i = 0;
	z = 0;
	while (y < PAL)
	{
		if (ip[i] == '.' || ip[i] == ZERO)
		{
			byte[z] = 0;
			sscanf(byte, "%hhu", &dst[y++]);
			ft_memset(byte, 0, FOUR);
			i++;
			z = 0;
		}
		else
			byte[z++] = ip[i++];
	}
}

int	generate_arp_packet(char *dest_addr, char *dest_ip, char *src_addr, char *src_ip, uint16_t opcode, unsigned char *packet)
{
	uint16_t	prot_arp = ARP_PROTOCOL;
	uint16_t	has = HAS;
	uint16_t	pas = PAS;
	int		ppos;

	ppos = 0;

	ft_memset(packet, 0, sizeof(packet));


	cpy_mac(packet, dest_addr);
	cpy_mac(&packet[ADDR_LEN], src_addr);

	packet[ADDR_LEN * 2] = prot_arp >> 8;
	packet[ADDR_LEN * 2 + ONE] = prot_arp;

	ppos = ADDR_LEN * 2 + TWO;

	/* ################################################################ final del header eth*/

	packet[ppos++] = has >> 8;
	packet[ppos++] = has;

	packet[ppos++] = pas >> 8;
	packet[ppos++] = pas;

	packet[ppos++] = HAL;

	packet[ppos++] = PAL;

	packet[ppos++] = opcode >> 8;
	packet[ppos++] = opcode;

	cpy_mac(&packet[ppos], src_addr);
	ppos += ADDR_LEN;

	cpy_ip(&packet[ppos], src_ip);
	ppos += PAL;

	cpy_mac(&packet[ppos], dest_addr);
	ppos += ADDR_LEN;
	
	cpy_ip(&packet[ppos], dest_ip);
	
	return (OK);
}
	





void	parse_arp_packet(uint8_t *buf, struct arp_packet *arp)
{
	unsigned char	*msg;
	uint8_t		spa[FOUR];
	uint8_t		tpa[FOUR];

	msg = buf;
	/* hardware and protocol address space */
	onetotwo(*msg, *(msg + 1), &arp->has);
	msg += 2;
	onetotwo((*msg), *(msg + 1), &arp->pas);
	msg += 2;

	/* the same as before but just for its lenght */
	arp->hal = *msg;
	msg++;
	arp->pal = *msg;
	msg++;

	/* opcode: request or reply */
	onetotwo(*msg, *(msg + 1), &arp->opcode);
	msg += 2;

	/* now, fill hardware and protocol address of sender */
	packet_address(arp->sender_address, msg);
	msg += ADDR_LEN;
	fillfourbytes(spa, msg);
	msg += FOUR;
	onetofour(spa, &(arp->sender_pro_address));

	/* and now for the target */
	packet_address(arp->target_address, msg);
	msg += ADDR_LEN;
	fillfourbytes(tpa, msg);
	onetofour(tpa, &(arp->target_pro_address));
}
