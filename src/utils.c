#include <utils.h>



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
