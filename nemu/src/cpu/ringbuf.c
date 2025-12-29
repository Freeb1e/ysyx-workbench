#include "ringbuf.h"

char itrace_buf[BUF_NUM][BUF_LENTH];
int head_ptr=0;

void ringbuf_init() {
    head_ptr=0;
    for(int i=0;i<BUF_NUM;i++){
        sprintf(itrace_buf[i],"NULL");
    }
    return;
}

void ringbuf_append(const char *entry) {
    sprintf(itrace_buf[head_ptr], "%s", entry);
    head_ptr = (head_ptr + 1) % BUF_NUM;
    return;
}

void ringbuf_print() {
    int idx = head_ptr % BUF_NUM;
    for (int i = 0; i < BUF_NUM; i++) {
        if(idx==0)printf("---- Instruction Ring Buffer ----\n");
        printf("%d %s\n", idx,itrace_buf[idx]);
        idx = (idx + 1) % BUF_NUM;
    }
    return;
}
