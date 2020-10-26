#ifndef CONTIKI_CONF_H_CDBB4VIH3I__
#define CONTIKI_CONF_H_CDBB4VIH3I__

#include "stm8l15x.h"
#define CCIF
#define CLIF

#define NETSTACK_CONF_WITH_IPV4 1
#define WITH_ASCII 1

#define CLOCK_CONF_SECOND 100

typedef unsigned int clock_time_t;
typedef unsigned int uip_stats_t;

#ifndef BV
#define BV(x) (1<<(x))
#endif

/* uIP configuration */
#define UIP_CONF_LLH_LEN         0
#define UIP_CONF_BROADCAST       1
#define UIP_CONF_LOGGING 1
#define UIP_CONF_BUFFER_SIZE 116

#define UIP_CONF_TCP_FORWARD 1

/* Prefix for relocation sections in ELF files */
#define REL_SECT_PREFIX ".rel"

#define CC_BYTE_ALIGNED __attribute__ ((packed, aligned(1)))

#define USB_EP1_SIZE 64
#define USB_EP2_SIZE 64

#define RAND_MAX 0x7fff
#endif /* CONTIKI_CONF_H_CDBB4VIH3I__ */
