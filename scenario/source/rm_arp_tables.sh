echo "arp tables before: "
cat /proc/net/arp
ip neigh flush all
echo "...."
echo "arp tables after deleting:"
cat /proc/net/arp
