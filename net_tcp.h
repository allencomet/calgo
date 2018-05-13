#ifndef __NET_TCP_H
#define __NET_TCP_H

#include "data_types.h"

#include <unistd.h>
#include <pthread.h>
#include <assert.h>

namespace net_tcp{

namespace timer{
/***** time utility *****/
/*
 * sleep for @ms milliseconds
 */
void msleep(uint32 ms);

/*
 * sleep for @us microseconds
 */
void usleep(uint32 us);

/*
 * sleep for @sec seconds
 */
inline void sleep(uint32 sec) {
    timer::msleep(sec * 1000);
}
}//namespace timer

typedef void (*send_handler)(int err,void *param);

// asnynchronmous send via tcp protocol
extern void async_send(send_handler handler, void *param);

}//namespace net_tcp

#endif