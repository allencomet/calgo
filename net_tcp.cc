#include "net_tcp.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <errno.h>

namespace net_tcp{

namespace timer{
//睡眠按毫秒计算
void msleep(uint32 ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = ms % 1000 * 1000000;

    while (nanosleep(&ts, &ts) == -1 && errno == EINTR);
}

//睡眠按微秒计算
void usleep(uint32 us) {
    struct timespec ts;
    ts.tv_sec = us / 1000000;
    ts.tv_nsec = us % 1000000 * 1000;

    while (nanosleep(&ts, &ts) == -1 && errno == EINTR);
}
}//namespace timer

typedef struct Param{
    int err;
    void *param;
    send_handler handler;
}Param; 

static void *callback_thread(void *param){//此处用的是一个线程
    assert(NULL != param);
    //do something
    Param *ptr = (Param *)param;
    int err = 0;
    for(;;) {
        sleep(3);//延时3秒执行callback函数，模拟将数据发送出去了
        ptr->handler(err, ptr->param);//函数指针执行函数，这个函数来自于应用层B
    }
}


void async_send(send_handler handler, void *par){
    Param *p = (Param *)malloc(sizeof(Param)); 
    assert(NULL != p);
    p->param = par;
    p->handler = handler;

    //创建线程
    pthread_t th;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&th,NULL,callback_thread,(void *)p);
    //pthread_join(th,NULL);
}


}//namespace net_tcp