#ifndef __COMMON_H_
#define __COMMON_H_

#define  OK      0
#define ERROR    1


#define PING_FILE    "ping_tem_file"

typedef struct ping_info {
	char   host_name[32];
	long    ntrans;
	long    nreceived;
   
	long    nrepeats;			/* number of duplicates */
	long    nchecksum;			/* replies with bad checksum */
	long    nerrors;			/* icmp errors */
   
	int     package_lose;      /* loss packages */
	long    sum_timeout;       /* the total number of timeout */

 	/** 
      * unit  : ms 
      * fomat :int:decimal 
      */
	long    i_min;
	long    d_min;

	long    i_avg;
	long    d_avg;

	long    i_max;
	long    d_max;

	long    i_mdev;
	long    d_mdev;

} ping_info_t;

/**
 * @brief ping_entry
 * 
 * @param p_cmd   : the command of the ping
 * @param p_data  : to save the ping command data
 * @return int    : return OK or ERROR
 */
int ping_entry(char *p_cmd, ping_info_t *p_data);




#endif