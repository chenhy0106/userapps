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
#include <unistd.h>

void write_check_page(int value)
{
    int * pages = (int* )malloc(1024 * sizeof(int)); // one page
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

    free(pages);
    return;
}

int main(int argc, char **argv)
{
    if (argc != 2 || atoi(argv[1]) < 1)
    {
        printf("asid_test [process num 256]\n");
        return 0;
    }

    int process_num = atoi(argv[1]);
    int *child_pids = malloc(sizeof(int) * process_num);
    int child_pids_ptr = 0;

    for (int i = 0; i < process_num; i++)
    {
        int child_pid = fork();
        if (child_pid == 0)
        {// child
            write_check_page(getpid());
            exit(0);
        }
        else
        {
            child_pids[child_pids_ptr++] = child_pid;
        }
    }

    int status;
    int child_pid;
    for (int i = 0; i < child_pids_ptr; i++)
    {
        child_pid = child_pids[i];
        waitpid(child_pid, &status, 0);
    }

    printf("finished\n");
    return 0;
}
