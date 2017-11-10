
/* XXX DCY */
/**
 * Get an IP's MAC address from the ARP cache.
 * Go through all the entries in config->arp_table_path until we find the
 * requested IP address and return the MAC address bound to it.
 * @todo Make this function portable (using shell scripts?)
 */
char *
arp_get(const char *req_ip)
{
    FILE *proc;
    char ip[16];
    char mac[18];
    char *reply;
    s_config *config = config_get_config();

    if (!(proc = fopen(config->arp_table_path, "r"))) {
        return NULL;
    }

    /* Skip first line */
    while (!feof(proc) && fgetc(proc) != '\n') ;

    /* Find ip, copy mac in reply */
    reply = NULL;
    while (!feof(proc) && (fscanf(proc, " %15[0-9.] %*s %*s %17[A-Fa-f0-9:] %*s %*s", ip, mac) == 2)) {
        if (strcmp(ip, req_ip) == 0) {
            reply = safe_strdup(mac);
            break;
        }
    }

    fclose(proc);

    return reply;
}
