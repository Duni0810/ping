#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>

#include "ping_data_get.h"


static void ping_info_print(ping_info_t *p_dat)
{
    printf(" host_name    : %s  \r\n", p_dat->host_name);
    printf(" n_trans      : %ld \r\n", p_dat->ntrans);
    printf(" received     : %ld \r\n", p_dat->nreceived);
    printf(" nrepeats     : %ld \r\n", p_dat->nrepeats);
    printf(" nchecksum    : %ld \r\n", p_dat->nchecksum);
    printf(" nerrors      : %ld \r\n", p_dat->nerrors);
    printf(" package_lose : %d  \r\n", p_dat->package_lose);
    printf(" sum_timeout  : %ld \r\n", p_dat->sum_timeout);
    printf(" i_min        : %ld \r\n", p_dat->i_min);
    printf(" d_min        : %ld \r\n", p_dat->d_min);
    printf(" i_avg        : %ld \r\n", p_dat->i_avg);
    printf(" d_avg        : %ld \r\n", p_dat->d_avg);
    printf(" i_max        : %ld \r\n", p_dat->i_max);
    printf(" d_max        : %ld \r\n", p_dat->d_max);
    printf(" i_mdev       : %ld \r\n", p_dat->i_mdev);
    printf(" d_mdev       : %ld \r\n", p_dat->d_mdev);
}

static int demo_ping_entry(void *p_arg)
{
    int         i                = 0;
    int         ret              = ERROR;
    char        ping_cmd[2][32]  = {"ping www.baidu.com -c 3\0", "ping aaa\0"};

    ping_info_t ping_info;

    for(i = 0; i < 10; i++) {
        printf("--------------------------%d------------------------\r\n", i);
        memset(&ping_info, 0, sizeof(ping_info_t));
        ret = ping_entry(ping_cmd[i % 2], &ping_info);
        ping_info_print(&ping_info);
    }

    return ret;
}

int main(int argc, char *argv[]) 
{

    static int i  = 0;

    demo_ping_entry(NULL);

    for(;;) {
        printf("i = %d\r\n", i++);
        sleep(1);
    }
}