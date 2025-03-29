#include <global.h>
#include <general.h>
#include <eter_arp.h>


void	print_etarp(struct eter_arp etarp)
{
	printf("Hardware address space: %u\n", etarp.has);
	printf("Protocol address space: %u\n", etarp.pas);
	printf("Hardware address length: %u\n", etarp.hal);
	printf("Protocol address length: %u\n", etarp.pal);
	printf("############################\n");
	printf("opcode: %u\n", etarp.opcode);
	printf("source address --> ");
	for (int i = 0; i < ADDR_LEN; i++)
	{
		if (i == FIVE)
			printf("%x\n", etarp.sender_address[i]);
		else
			printf("%x:", etarp.sender_address[i]);
	}
	printf("Sender protocol address: %u\n", etarp.sender_pro_address);
	printf("target address --> ");
	for (int i = 0; i < ADDR_LEN; i++)
	{
		if (i == FIVE)
			printf("%x\n", etarp.target_address[i]);
		else
			printf("%x:", etarp.target_address[i]);
	}
	printf("Target protocol address: %u\n", etarp.target_pro_address);
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
	/*if (ft_strlen(msg) != ADDR_LEN)
	{
		ft_bzero(filled, ADDR_LEN);
		return ;
	}
	*/
	for (int i = 0; i < ADDR_LEN; i++)
	{
		filled[i] = msg[i];
	}
}

void	fillfourbytes(uint8_t *laquesis, uint8_t *msg)
{
	/*if (ft_strlen(laquesis) != FOUR || ft_strlen(msg < FOUR))
	{
		ft_bzero(laquesis, FOUR);
		return ;
	}*/
	for (int i = 0; i < FOUR; i++)
	{
		laquesis[i] = msg[i];
	}
}



void	parse_arp_packet(uint8_t *msg, struct eter_arp *arp)
{
	uint8_t	spa[FOUR];
	uint8_t	tpa[FOUR];
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
	onetofour(spa, &(arp->target_pro_address));
}
