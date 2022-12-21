#ifndef __VOS_EID_H__
#define __VOS_EID_H__


/*!\file vos_eid.h
 * \brief Header file containing entity id assignments in
 * the VOS.
 */


/*!\enum VosEntityId
 * \brief Entity Id's (eid) are like process id's (pid), except they identify an
 * application in general, not the specific instance of that application.
 *
 * For example, the ppp application has an entity id of 22.  That entity id
 * refers to the ppp application in general, not a specific instance of ppp,
 * which is uniquely identified by its process id (pid).
 * 
 * Entity Id's are used by the various VOS API's to identify its caller.
 * They are also used by the messaging sub-system to identify the source
 * and destination of messages.  In most cases, there is only one instance
 * of a particular application, so specifying the VosEntityId is enough to
 * identify the application.  However, for applications that may have multiple
 * instances, additional steps may be required.  (For details on how
 * to identify an application for the purpose of sending or receiving messages,
 * see vos_msg.h).
 *
 * Entity Id's and TR69 access bits are bound together by the entityInfoArray
 * in eid.c.  Entities that have TR69 access bits must be listed first.
 *
 * Any changes in this array must also be reflected in entityInfoArray in eid.c
 */
typedef enum {
   EID_INVALID=0,
   EID_AFU=1,
   EID_AUTODETECT=2,
   EID_BLOCKSITES=3,
   EID_DAI=4,
   EID_DDNS=5,
   EID_DEVMANAGE=6,
   EID_DEVPROBE=7,
   EID_DYNAMIC_QOS=8,
   EID_ENIGMA=9,
   EID_ENVCTL=10,
   EID_FILTERINGSCHEDULE=11,
   EID_FOTA=12,
   EID_LEDCONTROL=13,
   EID_LIBPKT_REDIRECT=14,
   EID_LIBSWITCH=15,
   EID_MONITOR=16,
   EID_MTDOOPS=17,
   EID_NTPOT=18,
   EID_OOKLA=19,
   EID_PHDDNS=20,
   EID_POWERDETECTION=21,
   EID_PROTEST=22,
   EID_SECURITYLOG=23,
   EID_SPEEDTEST=24,
   EID_SSK=25,
   EID_SWOP=26,
   EID_TELNETENABLED=27,
   EID_TRAFFICMETER=28,
   EID_TW_VTY=29,
   EID_UCI2DAT=30,
   EID_UHTTPD_CGI=31,
   EID_SYSLOGD=32,
   EID_SMD=33
} VosEntityId;


/** Param accessible by TR69C;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_TR69C              0x0001

/** Param accessible by TR64C;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_TR64C              0x0002

/** Param accessible by httpd;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_HTTPD              0x0004

/** Param accessible by SNMP;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_SNMPD              0x0008

/** Param accessible by consoled/cli;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_CONSOLED           0x0010

/** Param accessible by telnetd/cli;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_TELNETD            0x0020

/** Param accessible by sshd/cli;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_SSHD               0x0040

/** Param accessible by other apps;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_COMMON               0x0080

#if 0
/** Param accessible by UPnp;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_UPNP               0x0080

/** Param accessible by ssk;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_SSK                0x0100

/** Param accessible by vectoringd;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_VECTORINGD         0x0200

/** Param accessible by VODSL;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_VODSL              0x0400

/** Param accessible by eoc MME;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_MME               0x0800

/** used for voipagent;  Used in MdmNodeAttributes.accessBitMask.
 */
#define NDA_ACCESS_VOIPAGENT          0x1000

/** Param accessible by DECTDBGD;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_DECTDBGD           0x2000

/** Param accessible by SWMDK;  Used in MdmNodeAttributes.accessBitMask. */
#define NDA_ACCESS_EPONAPP            0x4000
#endif

/** List of all management entities other than tr69c.
 *
 * tr69c considers these management entities "subscriber" management entities.
 * This is used by TR69C to grant access to all other management entities.
 * This bit mask is used in MdmNodeAttributes.accessBitMask.
 * See also DEFAULT_ACCESS_BIT_MASK in mdm_defs.h
 *
 */
#define NDA_ACCESS_SUBSCRIBER  (NDA_ACCESS_HTTPD        | NDA_ACCESS_SNMPD      | \
                                NDA_ACCESS_CONSOLED     | NDA_ACCESS_TELNETD    | \
                                NDA_ACCESS_SSHD         | NDA_ACCESS_COMMON)


/** Entity is a server, which opens a socket and listens for requests.
 *
 * This flag is used in VosEntityInfo.flags below.
 */
#define EIF_SERVER                    0x01


/** If entity is a server, server socket uses TCP (otherwise, uses UDP)
 *
 * This flag is used in VosEntityInfo.flags below.
 */
#define EIF_SERVER_TCP                0x02


/** Entity should be launched during stage 1 of VOS startup..
 *
 * This flag is used in VosEntityInfo.flags below.
 * So far, the only app we launch during stage 1 is ssk.
 */
#define EIF_LAUNCH_IN_STAGE_1         0x04


/** Entity should be launched on system boot (during stage 2).
 *
 * This flag is used in VosEntityInfo.flags below.
 */
#define EIF_LAUNCH_ON_BOOT            0x08


/** Entity will need access to the MDM.
 *
 * This flag is used in VosEntityInfo.flags below.
 * This flag will cause smd to pass the MDM shared memory id to the
 * app in the -m option.  
 * If the entity is going to access the MDM, it must have a NDA_ACCESS_xxx
 * bit defined for it.
 */
#define EIF_MDM                       0x10


/** Entity can run on the Desktop Linux.
 *
 * Some entities, such as httpd, can run on the Desktop Linux as
 * well as modems.  Others, such as dhcpd, can only run on the modem.
 */
#define EIF_DESKTOP_LINUX_CAPABLE     0x20


/** Entity will create a vos_msg communications link to smd. */
#define EIF_MESSAGING_CAPABLE         0x40


/** Entity can have multiple instances, currently only ppp and dhcpc */
#define EIF_MULTIPLE_INSTANCES        0x80


/** Entity supports IPv6. */
#define EIF_IPV6                      0x100

/** Tell smd to relaunch this App if it dies abnormally (sigsegv, etc) */
#define EIF_AUTO_RELAUNCH             0x200

/* Tell the progress been monitoring */
#define EIF_MONITOR                   0x400

/* Entity effect VOS_MSG_SYSTEM_READY */
#define EIF_SYSTEM_READY              0x800

#define EIF_NONE                      0x0000


/** A structure that contains info about an VosEntityId.
 *
 * For each new VosEntityId defined, add a corresponding entry to the
 * EntityInfoArray in vos_util/eid.c
 *
 */
typedef struct
{
    VosEntityId eid;    /**< The entity id for this entry. */
    UINT8 eidNum;
    UINT16 accessBit;   /**< This entity's bit position in MdmNodeAttributes.accessBitMask (only 15 bits available) */
    char *name;         /**< Short name for this entity. */
    char *path;         /**< Full path to the executable. */
    char *runArgs;      /**< Args to pass to this executable on startup */
    char *libPath;      /** < the so file path */
    UINT16 flags;       /**< Additional info about this entity, see EIF_xxx */
    UINT8  backLog;     /**< Backlog arg for the server socket */
    UINT16 port;        /**< If server, port number for the server socket. */
    UBOOL8 isFeatureCompiledIn; /**< Is this feature selected via make menuconfig */
    UINT32 uid;
    UINT8 maxCpuUsage;
    UINT32 maxPhyRam;
    UINT32 maxVirtRam;
    UINT32 maxDiskSize;
    UINT32 maxSocketNum;
    UBOOL8 coreDump;
    UBOOL8 newSession;
    UINT8 lifeNum;
    UINT8 spySig;
    UINT8 regexNum;
    char **regexList;
    UBOOL8 outDebug;
    char *netNs;
    UBOOL8 autoWakeup;
} VosEntityInfo;


typedef struct
{
    VosEntityId eid;
    UINT16 accessBit;
    char name[32];
    char path[128];
    char runArgs[256];
    UINT16 flags;
    UINT8 backLog;
    UINT16 port;
    UBOOL8 isFeartureComiledIn;
    UINT32 maxMemUsage;
    UINT32 normalMemUsage;
    UINT32 minMemUsage;
}VosEntityInfoMsg;


typedef struct 
{
    VosEntityId eid;
    char *name;
    UINT16 accessBit;   /**< This entity's bit position in MdmNodeAttributes.accessBitMask (only 15 bits available) */
} VOS_EID_NAME_MAP_T;


/** Get the VosEntityInfo for the specified VosEntityId.
 *
 * @param eid (IN) VosEntityId to get info on.
 * @return pointer to EntityInfo structure corresponding to the specified eid.
 *         Caller must not modify the returned VosEntityInfo structure.
 *         Caller must not free the returned VosEntityInfo structure.
 *         Returns NULL if VosEntityId is invalid.
 */
const VosEntityInfo *vosEid_getEntityInfo(VosEntityId eid);


/** Get the VOS_EID_NAME_MAP_T for the specified bit in the bitmask.
 *
 * @param bit (IN) A bit in the MdmNodeAttributes.accessBitMask.  Only a 
 *                 single bit is allowed.
 * @return pointer to EntityInfo structure corresponding to the specified bit.
 *         Caller must not modify the returned VosEntityInfo structure.
 *         Returns NULL if bit is not recognized.
 */
const VOS_EID_NAME_MAP_T *vosEid_getEntityInfoByAccessBit(UINT16 bit);


/** Get the VosEntityInfo for the specified entity's short string name.
 *
 * @param stringName (IN) The short string name of the entity.
 * @return pointer to EntityInfo structure corresponding to the specified name.
 *         Caller must not modify the returned VosEntityInfo structure.
 *         Caller must not free the returned VosEntityInfo structure.
 *         Returns NULL if name is not recognized.
 */
const VOS_EID_NAME_MAP_T *vosEid_getEntityInfoByStringName(const char *stringName);


/** Convert the given bitmask into a buffer of comma separated string names.
 *
 * If the bitmask contains bits which are not recognized, this function
 * will ignore them and fill the buffer with the string names for bits that it
 * does recognize and return VOS_RET_SUCCESS_UNRECOGNIZED_DATA_IGNORED.
 * If the bitmask is empty or does not contain any bits which this function
 * recognized, a buffer containing empty string will be returned.
 *
 * @param bitMask  (IN) bitmask.
 * @param buf     (OUT) A buffer containing the comma separated string names of the
 *                      entities in the bit mask.  The caller is responsible for
 *                      freeing the string buffer.
 * @return VOS_RET_E enum.
 */
VOS_RET_E vosEid_getStringNamesFromBitMask(UINT16 bitMask, char **buf);


/** Convert the given comma separated strings names into a bit mask.
 *
 * If the buffer contains string names which are not recognized, this function
 * will ignore them and fill the bitMask with bits for the string names that it
 * does recognize and return VOS_RET_SUCCESS_UNRECOGNIZED_DATA_IGNORED.
 *
 * @param buf      (IN) A buffer containing the comma separated string names of the
 *                      entities in the bit mask.  The caller is responsible for
 *                      freeing the string buffer.
 * @param bitMask (OUT) Resulting bitmask representation.
 *
 * @return VOS_RET_E enum.
 */
VOS_RET_E vosEid_getBitMaskFromStringNames(const char *buf, UINT16 *bitMask);


/** Get the process/thread id of the caller.
 *
 * Unlike the entity id, a pid is unique for all processes.  So two
 * instances of the same entity id will have different pid's.  This is
 * useful when you need to distinguish among multiple instances of
 * the same eid.
 *
 * @return SINT32 representing the pid.
 */
SINT32 vosEid_getPid(void);


/** Get the number of enties in the entityInfoArray.
 *
 * This function is for use by smd/oal_event.c.  Other callers should not use it.
 * 
 * @return number of entries in the entityInfoArray.
 */
UINT32 vosEid_getNumberOfEntityInfoEntries(void);


/** Get the first entry in the entityInfoArray.
 *
 * This function is for use by smd/oal_event.c.  Other callers should not use it.
 * 
 * @return pointer to the first entry in the entityInfoArray.
 */
const VosEntityInfo *vosEid_getFirstEntityInfo(void);

VOS_RET_E vosEid_setServerPort(VosEntityId eid, UINT16 port);

VosEntityId vosEid_addDynamicEntityInfo(const char *appName, const char *args);

VOS_RET_E vosEid_delDynamicEntityInfo(const char * appName);

void vosEid_init(void);

VOS_RET_E vosEid_getAppName(char *name, UINT32 size, VosEntityId eid);
UINT8 vosEid_getAppAccessBit(VosEntityId eid);
VosEntityId vosEid_getAppEid(char *name);


/** Mask to get the generic eid out of a UINT32 eid field. */
#define EID_EID_MASK  0x0000ffff

/** Mask to get the pid out of a UINT32 eid field */
#define EID_PID_MASK  0xffff0000

/** Get the generic eid out of a UINT32 eid field */
#define GENERIC_EID(e) (((UINT32) e) & EID_EID_MASK)

/** Get the pid out of a UINT32 eid field */
#define PID_IN_EID(e) ((((UINT32) e) & EID_PID_MASK) >> 16)

/** Make a specific UINT32 eid field out of a pid and a generic eid */
#define MAKE_SPECIFIC_EID(p, e) ((p << 16) | (((UINT32) e) & EID_EID_MASK))

#endif  /* __VOS_EID_H__ */

