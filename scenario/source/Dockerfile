FROM debian:bookworm

RUN apt update && apt upgrade -y && apt install iproute2 iputils-arping net-tools -y

COPY ../entrypoint.sh /
COPY rm_arp_tables.sh /
COPY sendarp.sh /

RUN chmod +x rm_arp_tables.sh
RUN chmod +x sendarp.sh

ENTRYPOINT ["bash", "/entrypoint.sh"]
