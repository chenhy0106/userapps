/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: GPL-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-20     Bernard      The first version
 */

#include <stdio.h>
#include <rtthread.h>
#include <sys/rtt_syscall.h>

int main(int argc, char **argv)
{
    int receiver = rt_channel_open("channel_test", O_CREAT);
    struct rt_channel_msg msg_recv;
    while (1)
    {
        rt_channel_recv(receiver, &msg_recv);
        rt_channel_reply(receiver, &msg_recv);
    }
}