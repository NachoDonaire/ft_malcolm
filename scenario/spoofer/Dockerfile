FROM debian:bookworm

RUN apt update && apt upgrade -y && apt install iproute2 iputils-arping -y  && apt install -y gcc make libc-dev


RUN mkdir -p /ft_malcolm

WORKDIR /ft_malcolm

#RUN make re

COPY entrypoint.sh /usr/bin/

#ENTRYPOINT ["bash", "/etc/entrypoint.sh"]
ENTRYPOINT ["tail", "-f"]
