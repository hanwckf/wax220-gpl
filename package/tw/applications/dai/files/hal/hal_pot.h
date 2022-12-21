#ifndef  _POT_H_
#define  _POT_H_

/******************************************************************************
*                                 MACRO
******************************************************************************/
#ifdef POT_DEBUG
#define POT_TRACE(fmt, args...) 	COMMON_TRACE(MID_MON, fmt, ##args)
#else
#define POT_TRACE(str, args...)
#endif


/******************************************************************************
*                                 ENUM
******************************************************************************/
#define POT_FILENAME            "/var/pot_value"
#define POT_MTD_NAME            "POT"
/* Netgear spec 5.6.1 Power-on Time
   POT_MaxValue: This is the max time value that will be kept in the device. Once POT has reached
   the value of POT_MaxValue, POT value will not be changed. Current value is set to 4320 (3 days). 
   In order to store 4320 bits, we need 540 bytes of flash memory. If this is not feasible, the minimum 
   value has to be 1440 i.e. 1 day and Netgear must be notified about this exception.*/
/* 4320 bit => 540 bytes, "md 0xbc030000" can show the value*/
#define POT_MAX_VALUE       4320    

/* Netgear spec 5.6.1 Power-on Time
   POT_Resolution: This is similar to a time click in the POT value counter. For example, if 
   POT_Resolution is set to 1, then POT value will be incremented by 1 in 1 minute. If 
   POT_Resolution is set to 60, then POT value will be incremented by 1 in 1 hour (60 minutes). 
   Current value is set to 1.
    */
#define POT_RESOLUTION      1   /*60s*/
//#define POT_BACKUP_OFFSET		1024		/*first pot space is 0~1023 bytes, backup space is 1024~2043, md 0xbc030400 show*/

/* Netgear spec 5.6.2	First Time for Internet Connection
  The first 4 bytes after the 2K of power-on time section stores the time when the extender first gets the 
  NTP synchronized with the NTGR NTP server after it came out from the factory. That is the starting
  address of this 4 bytes is
          (the starting address of the POT section) + 2048
  , and these 4 bytes store the time in the number of seconds since year 1970 in the GMT time. */
  /*2048 bytes => 2K bytes, "md 0xbc030800" can show the value*/
#define NTPST_OFFSET        (2048)      

/* Netgear spec 5.6.2	First Time for Internet Connection
   The 6 bytes after the timestamp of NTP synchronization stores the MAC address of the first Wi-Fi STA 
   that connects to the extender after it came out from the factory. That is the starting address of this 6 
   bytes is (the starting address of the POT section) + 2048 + 4
  */
#define STAMAC_OFFSET       (NTPST_OFFSET + 4)  /*"md 0xbc030804" can show the value*/

struct mtd_info_user {
    unsigned char type;
    unsigned int  flags;
    unsigned int  size;	 // Total size of the MTD
    unsigned int  erasesize;
    unsigned int  writesize;
    unsigned int  oobsize;   // Amount of OOB data per block (e.g. 16)
    /* The below two fields are obsolete and broken, do not use them
     * (TODO: remove at some point) */
    unsigned int  ecctype;
    unsigned int  eccsize;
};


struct erase_info_user {
    unsigned int start;
    unsigned int length;
};

#define MEMGETINFO         _IOR('M', 1, struct mtd_info_user)
#define MEMERASE           _IOW('M', 2, struct erase_info_user)


/******************************************************************************
*                               FUNCTION DECLARE                              *
******************************************************************************/

int hal_pot_value_init(void);

unsigned int hal_pot_resolution_value_get(void);

unsigned int hal_potMaxValueGet(void);

int hal_potValueGet(unsigned int *potvalue);

int hal_potValueSet(void);

int hal_potStamacGet(char *stamac);

int hal_potStamacSet(const char *stamac);

int hal_potNtpstGet(char *ntpst);

int hal_potNtpstSet(void);

#endif
