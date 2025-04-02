#include <global.h>
#include <general.h>
#include <utils.h>
#include <arp_packet.h>



void	print_arpdata(struct arp_packet arpdata)
{
	printf("Hardware address space: %u\n", arpdata.has);
	printf("Protocol address space: %u\n", arpdata.pas);
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
