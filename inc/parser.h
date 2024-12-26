#ifndef PARSER_H
#define PARSER_H



struct Target {
	int	socket;
	char	mac_addr[8];
	char	ip_addr[12];
} ;


struct Source {
	int	socket;
	char	mac_addr[8];
	char	ip_addr[12];
} ;

int parse_args(char **argv, struct Target *t, struct Source *s);





#endif
