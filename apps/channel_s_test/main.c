/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: GPL-2.0
 *
 */

#include <stdio.h>
#include <rtthread.h>
#include <sys/rtt_syscall.h>
#include <string.h>

int main(int argc, char **argv)
{
    int msg_count = 1000000;
    int sender = rt_channel_open("channel_test", O_RDWR);
    int i = 0;
    struct rt_channel_msg msg_send;
    msg_send.type = RT_CHANNEL_RAW;
    struct rt_channel_msg msg_recv;
    unsigned tick_begin = rt_tick_get();
    while (i++ < msg_count)
    {
        rt_channel_send_recv(sender, &msg_send, &msg_recv);
    }
    unsigned tick_end = rt_tick_get();
    printf("%d msg: %d ticks\n", msg_count, (tick_end - tick_begin));
}