#include "systemmanager.h"
#include "iconfigurationmanager.h"
#include "log.hpp"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <ifaddrs.h>
#include <linux/if_link.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

namespace mars {
namespace core {

IPAddressList SystemManager::getIP()
{
    IPAddressList addresses;
    struct ifaddrs *ifaddr, *ifa;
    int family, s, n;
    char host[NI_MAXHOST];
    if (getifaddrs(&ifaddr) == -1) {
        mars_warn("Unable to get IP address");
    }
    std::string iface;
    for (ifa = ifaddr, n = 0; ifa != nullptr; ifa = ifa->ifa_next, n++) {
        if (ifa->ifa_addr == nullptr) {
            continue;
        }

        family = ifa->ifa_addr->sa_family;

        /* Display interface name and family (including symbolic
           form of the latter for the common families) */
        iface = ifa->ifa_name;

        if (family == AF_INET || family == AF_INET6) {
            s = getnameinfo(ifa->ifa_addr,
                (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6), host, NI_MAXHOST,
                nullptr, 0, NI_NUMERICHOST);
            if (s != 0) {
                mars_error("getnameinfo() failed: {}", gai_strerror(s));
            }
        }
        addresses.push_back({ host, ifa->ifa_name });
    }

    freeifaddrs(ifaddr);

    return addresses;
}

std::string SystemManager::uuid() const { return _cfg.uuid(); }
} // namespace common
} // namespace mars
