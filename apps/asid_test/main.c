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
#include <stdlib.h>
#include <string.h>
#include <rtthread.h>
#include <math.h>
#include <unistd.h>

void write_check_page(int value)
{
    int * pages = (int* )rt_malloc(1024 * sizeof(int)); // one page
    for (unsigned i = 0; i < 1024; i++) 
    {
        pages[i] = value;
    }

    rt_thread_mdelay(1);

    for (unsigned i = 0; i < 1024; i++) 
    {
        if (pages[i] != value) 
        {
            printf("[Fail] pid = %d, data = %d\n", value, pages[i]);
            return;
        }
    }

    printf("%d pass\n", value);

    rt_free(pages);
}

int main(int argc, char **argv)
{
    if (argc != 2 || atoi(argv[1]) < 1)
    {
        printf("asid_test [process num 256]\n");
        return 0;
    }

    int process_num = atoi(argv[1]);
    int process_num_log = (int)log2(process_num);
    int origin_pid = getpid();

    for (int i = 0; i < process_num_log; i++)
    {
        int child_pid = fork();
        if (child_pid == 0)
        {// child
            write_check_page(getpid());
        }
        else
        {
            int status;
            waitpid(child_pid, &status, 0);
            write_check_page(getpid());
        }
    }

    if (getpid() == origin_pid)
    {
        printf("Succeed\n");
    }

    return 0;
}
