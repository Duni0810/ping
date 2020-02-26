/**
 * @file ping_data_get.c
 * @author young
 * @brief 
 * @version 0.1
 * @date 2020-02-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "ping_data_get.h"

#define     IS_VALUE(var)                                 \
            do                                            \
            {                                             \
                if(NULL == var) {                         \
                    printf("INVALID PARAMETER VALUE\r\n");\
                    return ERROR;                         \
                }                                         \
            } while(0)
             

#define    PACKAGE_CMP(str, dat)                                    \
            do                                                      \
            {                                                       \
                if (strncmp(str, chr_info[i], strlen(str)) == 0) {  \
                dat = atol(chr_info[i - 1]);                        \
                continue;                                           \
                }                                                   \
            } while (0)


#define    PACKAGE_ASSI(ii, dat1, dat2)                      \
            do                                               \
            {                                                \
                if (i == ii) {                               \
                   p_data->dat1 = atol(chr_info[0]);         \
                   p_data->dat2 = atol(chr_info[1]);         \
                }                                            \
            } while (0)
            

// command to run, include memset function and sprintf
#define  CMD_EXECUTE(buf, str, args...)            \
         do                                        \
         {                                         \
             memset(buf, 0, sizeof(buf));          \
             sprintf(buf, str, ## args);           \
             system(buf);                          \
         } while (0)


/**
 * @brief          : Do character segmentation
 * 
 * @param pstr     : The source data to be processed
 * @param pcutcmd  : Saved split data
 * @param ch       : Split identifier
 * @return int     : the number of Split,form 0 to start
 */
static int __mysplit(char *pstr, char(*pcutcmd)[64], char ch)
{
    int ret = 0;
    
    if (NULL != pstr && NULL != pcutcmd) {
        char *tempstr = pstr;
        int i = 0, j = 0; 
        int countrow = 0;
        while (*tempstr) {

            if (ch == *tempstr) {
           
                *(*(pcutcmd + i) + j) = '\0';

            } else if ((ch == *(tempstr - 1)) && (ch != *tempstr)) {
            
                if (countrow != 0)
                    i++;
                j = 0;
                *(*(pcutcmd + i) + j) = *tempstr;
                j++;

            } else { 
           
                if(0 == i) {
                    countrow = 1;
                }

                *(*(pcutcmd + i) + j) = *tempstr;
                j++;
            }
            tempstr++;
        }
        ret = i;
    }
    return ret;
}


static int ping_info_get(FILE  *fp, ping_info_t *p_data)
{
    int  i                =  0;
    int  num              =  0;
    char var[64]          = {0};
    char buffer[256]      = {0};
    char save_str[4][10]  = {0};
    char chr_info[16][64] = {0};

    IS_VALUE(fp);
    IS_VALUE(p_data);

    /* first get string */
    fgets(buffer, sizeof(buffer) - 1, fp);
    num = __mysplit(buffer, chr_info, ' ');

    // get host name
    strcpy(p_data->host_name, chr_info[1]);

    // clear buffer
    memset(buffer, 0, sizeof(buffer));
    memset(chr_info, 0, sizeof(chr_info));

    /* second get string */
    fgets(buffer, sizeof(buffer) - 1, fp);
    num = __mysplit(buffer, chr_info, ' ');
    
    // n packets transmitted
    p_data->ntrans = atol(chr_info[0]);

    // n packets received 
    p_data->nreceived = atol(chr_info[3]);

    // find key word
    for (i = 4; i < num + 1; i++) {

        PACKAGE_CMP("duplicates", p_data->nrepeats);

        PACKAGE_CMP("corrupted", p_data->nchecksum);

        PACKAGE_CMP("errors", p_data->nerrors);
            
        if (strncmp("loss", chr_info[i], strlen("loss")) == 0) {
            chr_info[i - 2][strlen(chr_info[i - 2]) - 1] = '\0';

            p_data->package_lose = atoi(chr_info[i - 2]);
            continue;
        }

        if (strncmp("time", chr_info[i], strlen("time")) == 0) {
            chr_info[i + 1][strlen(chr_info[i + 1]) - 1] = '\0';

            p_data->sum_timeout = atol(chr_info[i + 1]);
            continue;
        }
    }
    memset(buffer, 0, sizeof(buffer));
    memset(chr_info, 0, sizeof(chr_info));

    /*  third get string */
    fgets(buffer, sizeof(buffer) - 1, fp);
    num = __mysplit(buffer, chr_info, ' ');
    
    strcpy(var, chr_info[3]);

    memset(chr_info, 0, sizeof(chr_info));
    __mysplit(var, chr_info, '/');

     for (i = 0; i < 4; i++) {
         strcpy(save_str[i],chr_info[i]);
     }

    // find value :min/avg/max/mdev
    for (i = 0; i < 4; i++) {
        memset(chr_info, 0, sizeof(chr_info));
        __mysplit(save_str[i], chr_info, '.');

        PACKAGE_ASSI(0, i_min,  d_min);
        PACKAGE_ASSI(1, i_avg,  d_avg);
        PACKAGE_ASSI(2, i_max,  d_max);
        PACKAGE_ASSI(3, i_mdev, d_mdev);
    }

    return OK;
}

/**
 * @brief ping_entry
 * 
 * @param p_cmd   : the command of the ping
 * @param p_data  : to save the ping command data
 * @return int    : return OK or ERROR
 */
int ping_entry(char *p_cmd, ping_info_t *p_data)
{
    int    row            = 0;
	FILE  *fp             = NULL;
    char   cmd_buf[128]   = {0};
    char   data_buff[256] = {0};

    IS_VALUE(p_cmd);
    IS_VALUE(p_data);

    sprintf(cmd_buf, "%s > %s", p_cmd, PING_FILE);
    system(cmd_buf);

    if((fp = fopen(PING_FILE, "r")) == NULL) {
        printf("operation error!\r\n");
        return ERROR;
    }

    while(fgets(data_buff, sizeof(data_buff), fp) != NULL) {
        row++;
    }
    fclose(fp);

    if (row < 3) {
        CMD_EXECUTE(cmd_buf, "cat %s", PING_FILE);

        CMD_EXECUTE(cmd_buf, "rm %s", PING_FILE);

        return ERROR;
    }

    fp = NULL;

    memset(cmd_buf, 0, sizeof(cmd_buf));
    sprintf(cmd_buf, "tail -n 3 %s", PING_FILE);

    fp = popen(cmd_buf, "r");

    IS_VALUE(fp);

    ping_info_get(fp, p_data);

    pclose(fp);

    unlink(PING_FILE);

    return 0;
}


/* file end */
