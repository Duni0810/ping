#include <stdio.h>
#include <malloc.h>
#include "x_ping_common.h"


/**
 * @brief     : print ping command data
 * 
 * @param dat : include ping data 
 * @return    : NULL
 */
static void ping_finish_print(ping_finish_data_t *p_dat)
{
    printf(" host_name    : %s  \r\n", p_dat->host_name);
    printf(" n_trans      : %ld \r\n", p_dat->n_trans);
    printf(" received     : %ld \r\n", p_dat->received);
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

/**
 * @brief      : main entry code
 * 
 * @param argc : default
 * @param argv : default
 * @return int : default
 */
int main(int argc, char *argv[])
{
    int  i     = 0;
    char str[] = "ping  -c   5   114.114.114.114";

    ping_finish_data_t  data;

    memset(&data, 0, sizeof(ping_finish_data_t));


    for(i = 0; i < 10; i++) {
        memset(&data, 0, sizeof(ping_finish_data_t));
        printf("----------%d----------\r\n", i);
        ping_cmd_entry(str, &data);
        ping_finish_print(&data);
    }


    for (;;) {

        printf("%d\r\n", i++);
        sleep(1);
    }

    return 0;
} 