#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "net_tcp.h"

typedef struct DataRepo {
    int a;
    int b;
} DataRepo;


void send_handler(int err,void *param) {// 应用者增加的函数，此函数会在A中被执行
    //do something
    if (0 != err) {
        printf("error has been occured!\n");
        return;
    }
    DataRepo *data = (DataRepo *)param;
    assert(NULL != data);
    printf("send success!\n");
    printf("a[%d],b[%d]\n", data->a, data->b);
}


int main(int argc,char *argv[]){
    DataRepo *data_for_handler = (DataRepo *) malloc (sizeof(DataRepo));
    assert(NULL != data_for_handler);

    net_tcp::async_send(send_handler, data_for_handler);

    printf("------------------\n");
    net_tcp::timer::sleep(3);

    free(data_for_handler);
    data_for_handler = NULL;

    return 0;
}

