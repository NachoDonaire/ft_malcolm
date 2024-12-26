#include <libft.h>
#include <stdio.h>
#include <ft_malcolm.h>
#include <parser.h>

void	write_sentence(int fd, char *s)
{
	for (unsigned long int i = 0; i < ft_strlen(s); i++)
		write(fd, &s[i], 1);
}

int fatal_error(int reason)
{
	if (reason == NARG_ERR)
		write_sentence(2, "Wrong number of arguments\n");
	else if (reason == IP_ERR)
		write_sentence(2, "Error in some ip address. Please, check both.\nFormat: q.q.q.q where q is value between 0 and 255\n");
	return (-1);
}	

int main(int argc, char **argv)
{
	struct Target	target;
	struct Source	source;
	int	parse_status;

	if (argc != 5 || argv[0] == NULL)
		return (fatal_error(NARG_ERR));
	parse_status = parse_args(&argv[1], &target, &source);
	if (parse_status != OK)
		return (fatal_error(parse_status));
	return (0);
}
