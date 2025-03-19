FROM debian:bookworm

RUN apt update && apt upgrade -y && apt install iproute2 iputils-arping -y

COPY ../entrypoint.sh /

ENTRYPOINT ["bash", "/entrypoint.sh"]
