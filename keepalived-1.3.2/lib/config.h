/* lib/config.h.  Generated from config.h.in by configure.  */
/* lib/config.h.in.  Generated from configure.ac by autoheader.  */


#ifndef _CONFIG_H
#define _CONFIG_H
  

/* The configuration and build options from which the package is built */
#define CONFIGURATION_OPTIONS " PIPE2 FRA_OIFNAME LINUX_NET_IF_H_COLLISION LVS VRRP VRRP_AUTH VRRP_VMAC SOCK_NONBLOCK SOCK_CLOEXEC FIB_ROUTING SO_MARK"

/* Year of build configuration */
#define COPYRIGHT_YEAR "2016"

/* Define to 1 if need to call g_type_init() */
/* #undef DBUS_NEED_G_TYPE_INIT */

/* Defined here if not found in <net/ethernet.h>. */
/* #undef ETHERTYPE_IPV6 */

/* Define to 1 if using libnl-1 */
/* #undef FALLBACK_LIBNL1 */

/* Define to 1 if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define to 1 if you have the <asm/types.h> header file. */
#define HAVE_ASM_TYPES_H 1

/* Define to 1 if you have the declaration of `CLONE_NEWNET', and to 0 if you
   don't. */
#define HAVE_DECL_CLONE_NEWNET 1

/* Define to 1 if you have the declaration of `ETHERTYPE_IPV6', and to 0 if
   you don't. */
#define HAVE_DECL_ETHERTYPE_IPV6 1

/* Define to 1 if you have the declaration of `FRA_OIFNAME', and to 0 if you
   don't. */
#define HAVE_DECL_FRA_OIFNAME 1

/* Define to 1 if you have the declaration of `FRA_SUPPRESS_IFGROUP', and to 0
   if you don't. */
#define HAVE_DECL_FRA_SUPPRESS_IFGROUP 0

/* Define to 1 if you have the declaration of `FRA_SUPPRESS_PREFIXLEN', and to
   0 if you don't. */
#define HAVE_DECL_FRA_SUPPRESS_PREFIXLEN 0

/* Define to 1 if you have the declaration of `FRA_TUN_ID', and to 0 if you
   don't. */
#define HAVE_DECL_FRA_TUN_ID 0

/* Define to 1 if you have the declaration of `IFLA_INET6_ADDR_GEN_MODE', and
   to 0 if you don't. */
#define HAVE_DECL_IFLA_INET6_ADDR_GEN_MODE 0

/* Define to 1 if you have the declaration of `IFLA_MACVLAN_MODE', and to 0 if
   you don't. */
#define HAVE_DECL_IFLA_MACVLAN_MODE 1

/* Define to 1 if you have the declaration of `IPV4_DEVCONF_ACCEPT_LOCAL', and
   to 0 if you don't. */
/* #undef HAVE_DECL_IPV4_DEVCONF_ACCEPT_LOCAL */

/* Define to 1 if you have the declaration of `IPV4_DEVCONF_ARPFILTER', and to
   0 if you don't. */
/* #undef HAVE_DECL_IPV4_DEVCONF_ARPFILTER */

/* Define to 1 if you have the declaration of `IPV4_DEVCONF_ARP_IGNORE', and
   to 0 if you don't. */
/* #undef HAVE_DECL_IPV4_DEVCONF_ARP_IGNORE */

/* Define to 1 if you have the declaration of `IPV4_DEVCONF_RP_FILTER', and to
   0 if you don't. */
/* #undef HAVE_DECL_IPV4_DEVCONF_RP_FILTER */

/* Define to 1 if you have the declaration of `IPVS_DAEMON_ATTR_MCAST_GROUP',
   and to 0 if you don't. */
#define HAVE_DECL_IPVS_DAEMON_ATTR_MCAST_GROUP 0

/* Define to 1 if you have the declaration of `IPVS_DAEMON_ATTR_MCAST_GROUP6',
   and to 0 if you don't. */
#define HAVE_DECL_IPVS_DAEMON_ATTR_MCAST_GROUP6 0

/* Define to 1 if you have the declaration of `IPVS_DAEMON_ATTR_MCAST_PORT',
   and to 0 if you don't. */
#define HAVE_DECL_IPVS_DAEMON_ATTR_MCAST_PORT 0

/* Define to 1 if you have the declaration of `IPVS_DAEMON_ATTR_MCAST_TTL',
   and to 0 if you don't. */
#define HAVE_DECL_IPVS_DAEMON_ATTR_MCAST_TTL 0

/* Define to 1 if you have the declaration of `IPVS_DAEMON_ATTR_SYNC_MAXLEN',
   and to 0 if you don't. */
#define HAVE_DECL_IPVS_DAEMON_ATTR_SYNC_MAXLEN 0

/* Define to 1 if you have the declaration of `IPVS_DEST_ATTR_ADDR_FAMILY',
   and to 0 if you don't. */
#define HAVE_DECL_IPVS_DEST_ATTR_ADDR_FAMILY 0

/* Define to 1 if you have the declaration of `IPVS_DEST_ATTR_STATS64', and to
   0 if you don't. */
#define HAVE_DECL_IPVS_DEST_ATTR_STATS64 0

/* Define to 1 if you have the declaration of `IPVS_SVC_ATTR_STATS64', and to
   0 if you don't. */
#define HAVE_DECL_IPVS_SVC_ATTR_STATS64 0

/* Define to 1 if you have the declaration of `IP_VS_SVC_F_ONEPACKET', and to
   0 if you don't. */
#define HAVE_DECL_IP_VS_SVC_F_ONEPACKET 1

/* Define to 1 if you have the declaration of `MACVLAN_MODE_PRIVATE', and to 0
   if you don't. */
#define HAVE_DECL_MACVLAN_MODE_PRIVATE 1

/* Define to 1 if you have the declaration of `RTAX_CC_ALGO', and to 0 if you
   don't. */
#define HAVE_DECL_RTAX_CC_ALGO 0

/* Define to 1 if you have the declaration of `RTAX_QUICKACK', and to 0 if you
   don't. */
#define HAVE_DECL_RTAX_QUICKACK 0

/* Define to 1 if you have the declaration of `RTA_ENCAP', and to 0 if you
   don't. */
#define HAVE_DECL_RTA_ENCAP 0

/* Define to 1 if you have the declaration of `RTA_EXPIRES', and to 0 if you
   don't. */
#define HAVE_DECL_RTA_EXPIRES 0

/* Define to 1 if you have the declaration of `RTA_NEWDST', and to 0 if you
   don't. */
#define HAVE_DECL_RTA_NEWDST 0

/* Define to 1 if you have the declaration of `RTA_PREF', and to 0 if you
   don't. */
#define HAVE_DECL_RTA_PREF 0

/* Define to 1 if you have the declaration of `RTA_VIA', and to 0 if you
   don't. */
#define HAVE_DECL_RTA_VIA 0

/* Define to 1 if you have the declaration of `SOCK_CLOEXEC', and to 0 if you
   don't. */
#define HAVE_DECL_SOCK_CLOEXEC 1

/* Define to 1 if you have the declaration of `SOCK_NONBLOCK', and to 0 if you
   don't. */
#define HAVE_DECL_SOCK_NONBLOCK 1

/* Define to 1 if you have the declaration of `SO_MARK', and to 0 if you
   don't. */
#define HAVE_DECL_SO_MARK 1

/* Define to 1 if you have the `dup2' function. */
#define HAVE_DUP2 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the `fork' function. */
#define HAVE_FORK 1

/* Define to 1 if you have the `getcwd' function. */
#define HAVE_GETCWD 1

/* Define to 1 if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if ipset supports iface type */
/* #undef HAVE_IPSET_ATTR_IFACE */

/* Define to 1 if you have the `crypto' library (-lcrypto). */
#define HAVE_LIBCRYPTO 1

/* Define to 1 if you have the <libipset/data.h> header file. */
/* #undef HAVE_LIBIPSET_DATA_H */

/* Define to 1 if you have the <libipset/linux_ip_set.h> header file. */
/* #undef HAVE_LIBIPSET_LINUX_IP_SET_H */

/* Define to 1 if you have the <libipset/session.h> header file. */
/* #undef HAVE_LIBIPSET_SESSION_H */

/* Define to 1 if you have the <libipset/types.h> header file. */
/* #undef HAVE_LIBIPSET_TYPES_H */

/* Define to 1 if you have the <libiptc/libip6tc.h> header file. */
/* #undef HAVE_LIBIPTC_LIBIP6TC_H */

/* Define to 1 if you have the <libiptc/libiptc.h> header file. */
/* #undef HAVE_LIBIPTC_LIBIPTC_H */

/* Define to 1 if you have the <libiptc/libxtc.h> header file. */
/* #undef HAVE_LIBIPTC_LIBXTC_H */

/* Define to 1 if you have the <libnfnetlink/libnfnetlink.h> header file. */
/* #undef HAVE_LIBNFNETLINK_LIBNFNETLINK_H */

/* Define to 1 if you have the `nl-genl-3' library (-lnl-genl-3). */
/* #undef HAVE_LIBNL_GENL_3 */

/* Define to 1 if you have the `nl-route-3' library (-lnl-route-3). */
/* #undef HAVE_LIBNL_ROUTE_3 */

/* Define to 1 if you have the `ssl' library (-lssl). */
#define HAVE_LIBSSL 1

/* Define to 1 if you have the `xtables' library (-lxtables). */
/* #undef HAVE_LIBXTABLES */

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <linux/ethtool.h> header file. */
#define HAVE_LINUX_ETHTOOL_H 1

/* Define to 1 if you have the <linux/fib_rules.h> header file. */
#define HAVE_LINUX_FIB_RULES_H 1

/* Define to 1 if you have the <linux/icmpv6.h> header file. */
#define HAVE_LINUX_ICMPV6_H 1

/* Define to 1 if you have the <linux/if_addr.h> header file. */
#define HAVE_LINUX_IF_ADDR_H 1

/* Define to 1 if you have the <linux/if_arp.h> header file. */
#define HAVE_LINUX_IF_ARP_H 1

/* Define to 1 if you have the <linux/if_ether.h> header file. */
#define HAVE_LINUX_IF_ETHER_H 1

/* Define to 1 if you have the <linux/if_link.h> header file. */
#define HAVE_LINUX_IF_LINK_H 1

/* Define to 1 if you have the <linux/if_packet.h> header file. */
#define HAVE_LINUX_IF_PACKET_H 1

/* Define to 1 if you have the <linux/ip.h> header file. */
#define HAVE_LINUX_IP_H 1

/* Define to 1 if you have the <linux/ip_vs.h> header file. */
#define HAVE_LINUX_IP_VS_H 1

/* Define to 1 if you have the <linux/netfilter/xt_set.h> header file. */
/* #undef HAVE_LINUX_NETFILTER_XT_SET_H */

/* Define to 1 if you have the <linux/netfilter/x_tables.h> header file. */
#define HAVE_LINUX_NETFILTER_X_TABLES_H 1

/* Define to 1 if you have the <linux/rtnetlink.h> header file. */
/* #undef HAVE_LINUX_RTNETLINK_H */

/* Define to 1 if you have the <linux/sockios.h> header file. */
#define HAVE_LINUX_SOCKIOS_H 1

/* Define to 1 if you have the <linux/types.h> header file. */
#define HAVE_LINUX_TYPES_H 1

/* Define to 1 if your system has a GNU libc compatible `malloc' function, and
   to 0 otherwise. */
#define HAVE_MALLOC 1

/* Define to 1 if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the <netlink/genl/ctrl.h> header file. */
/* #undef HAVE_NETLINK_GENL_CTRL_H */

/* Define to 1 if you have the <netlink/genl/genl.h> header file. */
/* #undef HAVE_NETLINK_GENL_GENL_H */

/* Define to 1 if you have the <netlink/netlink.h> header file. */
/* #undef HAVE_NETLINK_NETLINK_H */

/* Define to 1 if you have the <netlink/route/link.h> header file. */
/* #undef HAVE_NETLINK_ROUTE_LINK_H */

/* Define to 1 if you have the <netlink/route/link/inet.h> header file. */
/* #undef HAVE_NETLINK_ROUTE_LINK_INET_H */

/* Define to 1 if you have the `netsnmp_enable_subagent' function. */
/* #undef HAVE_NETSNMP_ENABLE_SUBAGENT */

/* Define to 1 if you have the <net-snmp/agent/agent_sysORTable.h> header
   file. */
/* #undef HAVE_NET_SNMP_AGENT_AGENT_SYSORTABLE_H */

/* Define to 1 if you have the <net-snmp/agent/snmp_vars.h> header file. */
/* #undef HAVE_NET_SNMP_AGENT_SNMP_VARS_H */

/* Define to 1 if you have the <net-snmp/agent/util_funcs.h> header file. */
/* #undef HAVE_NET_SNMP_AGENT_UTIL_FUNCS_H */

/* Define to 1 if you have the <openssl/err.h> header file. */
#define HAVE_OPENSSL_ERR_H 1

/* Define to 1 if you have the <openssl/md5.h> header file. */
#define HAVE_OPENSSL_MD5_H 1

/* Define to 1 if you have the <openssl/sha.h> header file. */
/* #undef HAVE_OPENSSL_SHA_H */

/* Define to 1 if you have the <openssl/ssl.h> header file. */
#define HAVE_OPENSSL_SSL_H 1

/* Define to 1 if you have the `pipe2' function. */
#define HAVE_PIPE2 1

/* Define to 1 if your system has a GNU libc compatible `realloc' function,
   and to 0 otherwise. */
#define HAVE_REALLOC 1

/* Define to 1 if you have the `select' function. */
#define HAVE_SELECT 1

/* Define to 1 if you have the `setenv' function. */
#define HAVE_SETENV 1

/* Define to 1 if you have the `setns' function. */
#define HAVE_SETNS 1

/* Define to 1 if you have the `socket' function. */
#define HAVE_SOCKET 1

/* Define to 1 if stdbool.h conforms to C99. */
#define HAVE_STDBOOL_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strpbrk' function. */
#define HAVE_STRPBRK 1

/* Define to 1 if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define to 1 if you have the `strtol' function. */
#define HAVE_STRTOL 1

/* Define to 1 if you have the `strtoul' function. */
#define HAVE_STRTOUL 1

/* Define to 1 if you have the <syslog.h> header file. */
#define HAVE_SYSLOG_H 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the `uname' function. */
#define HAVE_UNAME 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `vfork' function. */
#define HAVE_VFORK 1

/* Define to 1 if you have the <vfork.h> header file. */
/* #undef HAVE_VFORK_H */

/* Define to 1 if `fork' works. */
#define HAVE_WORKING_FORK 1

/* Define to 1 if `vfork' works. */
#define HAVE_WORKING_VFORK 1

/* Define to 1 if you have the <xtables.h> header file. */
/* #undef HAVE_XTABLES_H */

/* Define to 1 if have struct xt_set_info_match_v1 */
/* #undef HAVE_XT_SET_INFO_MATCH_V1 */

/* Define to 1 if the system has the type `_Bool'. */
#define HAVE__BOOL 1

/* Define to 1 if libipvs can use netlink */
/* #undef LIBIPVS_USE_NL */

/* Define to 1 if <linux/netlink.h> needs <sys/socket.h> */
/* #undef NETLINK_H_NEEDS_SYS_SOCKET_H */

/* Name of package */
#define PACKAGE "keepalived"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "keepalived-devel@lists.sourceforge.net"

/* Define to the full name of this package. */
#define PACKAGE_NAME "Keepalived"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "Keepalived 1.3.2"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "keepalived"

/* Define to the home page for this package. */
#define PACKAGE_URL "http://www.keepalived.org/"

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.3.2"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "1.3.2"

/* Date of build configuration */
#define VERSION_DATE "12/08,2016"

/* Define if <linux/netfilter/x_tables.h> doesnt define it */
/* #undef XT_EXTENSION_MAXNAMELEN */

/* Define to 1 if <linux/netfilter/xt_set.h> needs <libipset/linux_ip_set.h>
   */
/* #undef XT_SET_H_NEEDS_LINUX_IP_SET_H */

/* Define to 1 to build with debugging support */
/* #undef _DEBUG_ */

/* Define to 1 if have FIB routing support */
#define _HAVE_FIB_ROUTING_ 1 

/* Define to 1 if <net/if.h> and <netlink/route/link.h> namespace collision */
/* #undef _HAVE_IF_H_LINK_H_COLLISION_ */

/* Define to 1 if have IPv4 netlink device configuration */
/* #undef _HAVE_IPV4_DEVCONF_ */

/* Define to 1 if have IPVS syncd attributes */
/* #undef _HAVE_IPVS_SYNCD_ATTRIBUTES_ */

/* Define to 1 if have ipset library */
/* #undef _HAVE_LIBIPSET_ */

/* Define to 1 if have iptables libraries */
/* #undef _HAVE_LIBIPTC_ */

/* Define to 1 if using libnl-1 */
/* #undef _HAVE_LIBNL1_ */

/* Define to 1 if using libnl-3 */
/* #undef _HAVE_LIBNL3_ */

/* Define to 1 if have libiptc/libiptc.h linux/if.h and net/if.h namespace
   collision */
#define _HAVE_LINUX_NET_IF_H_COLLISION_ 1 

/* Define to 1 if have pe selection support */
#define _HAVE_PE_NAME_ 1 

/* Define to 1 if have MAC VLAN support */
#define _HAVE_VRRP_VMAC_ 1 

/* Define to 1 to build with malloc/free checks */
/* #undef _MEM_CHECK_ */

/* Define to 1 to log malloc/free checks to syslog */
/* #undef _MEM_CHECK_LOG_ */

/* Define to 1 to have keepalived send RFC6257 SNMP responses for VRRPv2
   instances */
/* #undef _SNMP_REPLY_V3_FOR_V2_ */

/* Define for Solaris 2.5.1 so the uint32_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT32_T */

/* Define for Solaris 2.5.1 so the uint64_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT64_T */

/* Define for Solaris 2.5.1 so the uint8_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT8_T */

/* Define to 1 to have DBUS support */
/* #undef _WITH_DBUS_ */

/* Define to 1 to have DBus create instance support */
/* #undef _WITH_DBUS_CREATE_INSTANCE_ */

/* Define to 1 if have IPVS support */
#define _WITH_LVS_ 1 

/* Define to 1 if have IPVS 64 bit stats */
/* #undef _WITH_LVS_64BIT_STATS_ */

/* Define to 1 to have SHA1 support */
/* #undef _WITH_SHA1_ */

/* Define to 1 to have keepalived SNMP support */
/* #undef _WITH_SNMP_ */

/* Define to 1 to have keepalived SNMP checker support */
/* #undef _WITH_SNMP_CHECKER_ */

/* Define to 1 to have keepalived SNMP VRRP support */
/* #undef _WITH_SNMP_KEEPALIVED_ */

/* Define to 1 to have RFCv2 SNMP support */
/* #undef _WITH_SNMP_RFCV2_ */

/* Define to 1 to have RFCv3 SNMP support */
/* #undef _WITH_SNMP_RFCV3_ */

/* Define to 1 to have RFC SNMP support */
/* #undef _WITH_SNMP_RFC_ */

/* Define to 1 if have SO_MARK */
#define _WITH_SO_MARK_ 1 

/* Define to 1 to build with stacktrace support */
/* #undef _WITH_STACKTRACE_ */

/* Define to 1 if have VRRP support */
#define _WITH_VRRP_ 1 

/* Define to 1 if want ARRP authentication support */
#define _WITH_VRRP_AUTH_ 1 

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to the type of a signed integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int64_t */

/* Define to rpl_malloc if the replacement function should be used. */
/* #undef malloc */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to rpl_realloc if the replacement function should be used. */
/* #undef realloc */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to the type of an unsigned integer type of width exactly 16 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint16_t */

/* Define to the type of an unsigned integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint32_t */

/* Define to the type of an unsigned integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint64_t */

/* Define to the type of an unsigned integer type of width exactly 8 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint8_t */

/* Define as `fork' if `vfork' does not work. */
/* #undef vfork */


#endif
  
