      /* Ping the client, if he responds it'll keep activity on the link.
         * However, if the firewall blocks it, it will not help.  The suggested
         * way to deal witht his is to keep the DHCP lease time extremely
         * short:  Shorter than config->checkinterval * config->clienttimeout */

/**
 * Ping an IP.
 * @param IP/host as string, will be sent to gethostbyname
 */
void
icmp_ping(const char *host)
{
    struct sockaddr_in saddr;
    struct {
        struct ip ip;
        struct icmp icmp;
    } packet;
    unsigned int i, j;
    int opt = 2000;
    unsigned short id = rand16();

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    inet_aton(host, &saddr.sin_addr);
#if defined(HAVE_SOCKADDR_SA_LEN)
    saddr.sin_len = sizeof(struct sockaddr_in);
#endif

    memset(&packet.icmp, 0, sizeof(packet.icmp));
    packet.icmp.icmp_type = ICMP_ECHO;
    packet.icmp.icmp_id = id;

    for (j = 0, i = 0; i < sizeof(struct icmp) / 2; i++)
        j += ((unsigned short *)&packet.icmp)[i];

    while (j >> 16)
        j = (j & 0xffff) + (j >> 16);

    packet.icmp.icmp_cksum = (j == 0xffff) ? j : ~j;

    //设置2000字节的缓冲区 感觉此处代码写错，应该写SO_SENDBUF
    if (setsockopt(icmp_fd, SOL_SOCKET, SO_RCVBUF, &opt, sizeof(opt)) == -1)
        debug(LOG_ERR, "setsockopt(): %s", strerror(errno));

    if (sendto(icmp_fd, (char *)&packet.icmp, sizeof(struct icmp), 0,
               (const struct sockaddr *)&saddr, sizeof(saddr)) == -1)
        debug(LOG_ERR, "sendto(): %s", strerror(errno));

    opt = 1;
    if (setsockopt(icmp_fd, SOL_SOCKET, SO_RCVBUF, &opt, sizeof(opt)) == -1)
        debug(LOG_ERR, "setsockopt(): %s", strerror(errno));

    return;
}
