#ifndef __UTIL_STRCONV_H__
#define __UTIL_STRCONV_H__

#include "../vos/vos_defs.h"
#include "util_defs.h"

#ifndef PFM_NO_INCLUDE_ARPA_INET_H
#include <netinet/in.h>
#endif


#define UTIL_STRNCPY(dest, src, n)    util_strncpy(__FUNCTION__, __LINE__, dest, src, n)
#ifndef PFM_ALLOW_STRCPY
#undef strcpy
#define strcpy    ("Please use UTIL_STRNCPY to replace strcpy")
#endif /* PFM_ALLOW_STRCPY */

#define UTIL_STRNCAT(dest, src, n)    util_strncat(__FUNCTION__, __LINE__, dest, src, n)
#define UTIL_STRNCATF(dest, n, format, ...)    util_strncatf(__FUNCTION__, __LINE__, dest, n, format, ##__VA_ARGS__)
#ifndef PFM_ALLOW_STRCAT
#undef strcat
#define strcat    ("Please use UTIL_STRNCAT to replace strcat")
#endif /* PFM_ALLOW_STRCAT */

#define UTIL_SNPRINTF(str, size, format, ...)    util_snprintf(__FUNCTION__, __LINE__, str, size, format, ##__VA_ARGS__)

#define UTIL_SPRINTF_ALLOC(str, format, ...)    util_sprintf_alloc(__FUNCTION__, __LINE__, str, format, ##__VA_ARGS__)

#ifndef PFM_ALLOW_SPRINTF
#undef sprintf
#define sprintf    ("Please use UTIL_SNPRINTF to replace sprintf")
#endif /* PFM_ALLOW_SPRINTF */


#ifndef isblank
int isblank(int c);
#endif


/*!\file util_strconv.h
 * \brief Header file for the application to convert value from string to other formats.
 * This is in the vos_util library.
 */

/** Macro to determine if a string parameter is empty or not */
#define IS_EMPTY_STRING(s)    ((s == NULL) || (*s == '\0'))

/** convert vpiVciStr (eg. "0/35") to vpi=2 and vci=35
 * @param vpiVciStr (IN) vpi/vci string
 * @param vpi (OUT) vpi in SINT32 format 
 * @param vci (OUT) vpi in SINT32 format
 * @return VOS_RET_E enum.
 */
VOS_RET_E util_atmVpiVciStrToNum(const char *vpiVciStr, SINT32 *vpi, SINT32 *vci);

/**
 * @param vpiVciStr (IN) vpi/vci string
 * @param vpi (OUT) vpi in SINT32 format 
 * @param vci (OUT) vpi in SINT32 format
 * @return VOS_RET_E enum.
 */
VOS_RET_E util_atmVpiVciNumToStr(const SINT32 vpi, const SINT32 vci, char *vpiVciStr, UINT32 vpiVciStrLen);

/** convert macStr to macNum (array of 6 bytes)
 *  Ex: 0a:0b:0c:0d:0e:0f -> 0a0b0c0d0e0f
 *
 * @param macStr (IN) macStr to be converted.
 * @param macNum (OUT) macNum must point to a buffer of at least 6 bytes which the
 *                     caller provides.
 * @return VOS_RET_E enum.
 */
VOS_RET_E util_macStrToNum(const char *macStr, UINT8 *macNum);

/** convert macNum (array of 6 bytes) to macStr.
 *  Ex: 0a0b0c0d0e0f -> 0a:0b:0c:0d:0e:0f
 * 
 * @param macNum (IN) macNum array to be converted.
 * @param macStr (OUT) macStr must point to a buffer of at least MAC_STR_LEN+1 (17+1)
 *                     to store the results.
 * @return VOS_RET_E enum.
 */
VOS_RET_E util_macNumToStr(const UINT8 *macNum, char *macStr, UINT32 macStrLen);

/** macStr plus increase including macAddr carry bit
 *  Ex: 0a:0b:0c:0d:0e:ff + 2 -> 0a:0b:0c:0d:0f:01
 * 
 * @convert realMAC (the last three byte of macAddr)  to int .
 * @int realMAC plus increase.
 * @convert the int realMAC to str
 */
VOS_RET_E util_increaseMacValue(UINT8 macAddr[6], SINT32 increase);

/** convert string to signed 32 bit integer, similar to unix strtol
 *
 * @param str (IN)        string to convert
 * @param endptr (IN/OUT) optional, if provided, will point to the first
 *                        character which caused conversion error.
 * @param base (IN)       radix to use for conversion.  If 0, then the
 *                        function will decide the radix based on input string.
 * @param val (OUT)       if conversion was successful, the resulting value.
 * @return VOS_RET_E enum.
 */
VOS_RET_E util_strtol(const char *str, char **endptr, SINT32 base, SINT32 *val);


/** convert string to unsigned 32 bit integer, similar to unix strtoul
 *
 * @param str (IN)        string to convert.  A leading - sign is not allowed.
 * @param endptr (IN/OUT) optional, if provided, will point to the first
 *                        character which caused conversion error.
 * @param base (IN)       radix to use for conversion.  If 0, then the
 *                        function will decide the radix based on input string.
 * @param val (OUT)       if conversion was successful, the resulting value.
 * @return VOS_RET_E enum.
 */
VOS_RET_E util_strtoul(const char *str, char **endptr, SINT32 base, UINT32 *val);


/** convert string to signed 64 bit integer, similar to unix strtoll
 *
 * @param str (IN)        string to convert
 * @param endptr (IN/OUT) optional, if provided, will point to the first
 *                        character which caused conversion error.
 * @param base (IN)       radix to use for conversion.  If 0, then the
 *                        function will decide the radix based on input string.
 * @param val (OUT)       if conversion was successful, the resulting value.
 * @return VOS_RET_E enum.
 */
VOS_RET_E util_strtol64(const char *str, char **endptr, SINT32 base, SINT64 *val);


/** convert string to unsigned 64 bit integer, similar to unix strtoull
 *
 * @param str (IN)        string to convert.  A leading - sign is not allowed.
 * @param endptr (IN/OUT) optional, if provided, will point to the first
 *                        character which caused conversion error.
 * @param base (IN)       radix to use for conversion.  If 0, then the
 *                        function will decide the radix based on input string.
 * @param val (OUT)       if conversion was successful, the resulting value.
 * @return VOS_RET_E enum.
 */
VOS_RET_E util_strtoul64(const char *str, char **endptr, SINT32 base, UINT64 *val);


void util_strToUpper(char *string);


/** convert string to lowercase string
 *
 * @param string (IN/OUT) the upper case of the characters in the string will be 
 *                        converted to lower case characters.
 */
void util_strToLower(char *string);


char *util_strDupLower(char *string);


void util_strTrimL(char *string);


void util_strTrimR(char *string);


void util_strTrim(char *string);


/*!\enum UrlProto
 * \brief URL protocols returned by util_parseUrl().
 */
typedef enum 
{
   URL_PROTO_HTTP=0, /**< http */
   URL_PROTO_HTTPS=1, /**< https */
   URL_PROTO_FTP=2,   /**< ftp */
   URL_PROTO_TFTP=3   /**< tftp */
} UrlProto;


/** Parse an URL and return is components.
 *
 * @param url    (IN) url to parse.
 * @param proto (OUT) If not NULL, and if URL is well formed, it will be
 *                    set to the URL protocol (URL_PROTO_HTTPD, URL_PROTO_FTP, etc.)
 * @param addr  (OUT) If not NULL, and if URL is well formed, it will be 
 *                    set to the address portion of the URL.  Caller is responsible
 *                    for freeing addr string.
 * @param port  (OUT) If not NULL, and if URL is well formed, it will be 
 *                    set to the port portion of the URL.  If no port number
 *                    is specified, then port will be set to 0.
 * @param path  (OUT) If not NULL, and if URL is well formed, it will be 
 *                    set to the path portion of the URL.  Caller is responsible for
 *                    freeing path string.
 *
 * @return VOS_RET_E enum, specifically, VOS_RET_SUCCESS if URL is well formed,
 *                      VOS_RET_INVALID_ARGUMENTS if URL is not well formed.
 */
VOS_RET_E util_parseUrl(const char *url, UrlProto *proto, char **addr, UINT16 *port, char **path);
 


/** Return the path to the CommEngine build directory in the given buffer.
 *
 * This function should only be used for unit testing on the Linux desktop,
 * but we define the symbol for modem builds as well to reduce the number
 * of ifdef's in the code.
 *
 * @param pathBuf   (OUT) Contains the pathBuf.
 * @param pathBufLen (IN) Length of the buffer.  If the buffer is not large
 *                        enough to hold the path, an error will be returned.
 * @return VOS_RET_E enum.
 */
VOS_RET_E util_getBaseDir(char *pathBuf, UINT32 pathBufLen);


VOS_RET_E util_getRunTimePath(const char *target, char *pathBuf, UINT32 pathBufLen);

/** Return the Primary and Secondary DNS sever string.
 *
 *
 * @param str (IN)        comma seperated DNS Servers string to be converted
 * @param str (OUT)       if conversion was successful, Primary DNS string.
 * @param str (OUT)       if conversion was successful, Secondary DNS string.
 * @param str (IN)        is the query for IPv4 DNS server

 * @return VOS_RET_E enum.
 */
VOS_RET_E util_parseDNS(const char *inDsnServers, char *outDnsPrimary, UINT32 outDnsPrimaryLen, char *outDnsSecondary, UINT32 outDnsSecondaryLen, UBOOL8 isIPv4);


VOS_RET_E util_concatDNS(const char *dns1, const char *dns2, char *buf, UINT32 bufLen);


/** Return a syslog mode integer corresponding to the mode string.
 *
 * Mode refers to where the log goes.
 * The mode numbers are hard coded in logconfig.html, so there is no point in
 * defining #def's for them.
 * 1 = local circular buffer in shared mem
 * 2 = remote
 * 3 = local cirulcar buffer in shared mem and remote
 * 4 = local file (not clear if software actually supports this)
 * 5 = local file and remote (not clear if software actually supports this)
 *
 * @param modeStr (IN) mode string.
 *
 * @return mode number.
 */
SINT32 util_syslogModeToNum(const char *modeStr);


/** Given a syslog mode number, return the associated string.
 *
 * See util_syslogModeToNum for listing of valid mode numbers.
 *
 * @param mode (IN) mode number.
 *
 * @return mode string, this string is a pointer to a static string, so it
 * must not be modified or freed.
 */
char * util_numToSyslogModeString(SINT32 mode);


/** Return true if the given number is a valid and supported syslog mode.
 *
 * See util_syslogModeToNum for listing of valid mode numbers.
 * Only modes 1, 2, and 3 are supported.
 *
 * @param mode (IN) mode number.
 *
 * @return true if the given mode number is a valid and supported syslog mode.
 */
UBOOL8 util_isValidSyslogMode(const char *modeStr);


/** Given a syslog level string, return equivalent log level.
 *
 * The log level numbers are defined in /usr/include/sys/syslog.h.
 *
 * @param levelStr (IN) The level in string format.
 *
 * @return the equivalent syslog level number.
 */
SINT32 util_syslogLevelToNum(const char *levelStr);


/** Given a syslog level number, return the equivalent log level string.
 *
 * The log level numbers are defined in /usr/include/sys/syslog.h.
 *
 * @param level (IN) The log level number.
 *
 * @return the log level string, this string is a pointer to a static string, so it
 * must not be modified or freed.
 */
char * util_numToSyslogLevelString(SINT32 level);


/** Return true if the given number is a valid syslog level.
 *  This is designed for the cli menu input validation.  But I put this
 *  function here to keep all the syslog level conversions together.
 *
 * @param level (IN) The log level number in string format.
 * 
 * @return TRUE if the given number is a valid syslog level.
 */
UBOOL8 util_isValidSyslogLevel(const char *levelStr);


/** Return true if the string is a valid syslog level string.
 *
 * @param level (IN) The log level string.
 * 
 * @return TRUE if the given string is a valid syslog level string.
 */
UBOOL8 util_isValidSyslogLevelString(const char *level);

/** Convert an IPv6 address string to its standard format returned
 *  from inet_ntop().
 *
 * @param address (IN) IPv6 address in CIDR notation.
 * @param address (OUT) standard format IPv6 address in CIDR notation.
 *
 * @return VOS_RET_E enum.
 */
VOS_RET_E util_standardizeIp6Addr(const char *address, char *stdAddr, UINT32 stdAddrLen);

/** Given an IPv6 address string, return true if it is a valid IPv6 global
 *  unicast address.
 *
 * @param address (IN) IPv6 address string.
 *
 * @return TRUE if the string is a valid IPv6 global unicast address.
 */
UBOOL8 util_isGUAorULA(const char *address);



/** Return the Primary and Secondary DNS sever string.
 *
 * @param str (IN)        comma seperated DNS Servers string to be converted
 * @param str (OUT)       if conversion was successful, Primary DNS string.
 * @param str (OUT)       if conversion was successful, Secondary DNS string.
 *
 * @return VOS_RET_E enum.
 */
VOS_RET_E util_replaceEui64(const char *address1, char *address2);


/** Return the Primary and Secondary DNS sever string.
 *
 * @param str (IN)        comma seperated DNS Servers string to be converted
 * @param str (OUT)       if conversion was successful, Primary DNS string.
 * @param str (OUT)       if conversion was successful, Secondary DNS string.
 *
 * @return VOS_RET_E enum.
 */
VOS_RET_E util_getAddrPrefix(const char *address, UINT32 plen, char *prefix);

/** Return the Primary and Secondary DNS sever string.
 *
 * @param str (IN)        comma seperated DNS Servers string to be converted
 * @param str (OUT)       if conversion was successful, Primary DNS string.
 * @param str (OUT)       if conversion was successful, Secondary DNS string.
 *
 * @return VOS_RET_E enum.
 */
VOS_RET_E util_parsePrefixAddress(const char *prefixAddr, char *address, UINT32 addressLen, UINT32 *plen);

/*!
 * \brief defines for ppp auto method in number
 */
#define PPP_AUTH_METHOD_AUTO        0
#define PPP_AUTH_METHOD_PAP         1
#define PPP_AUTH_METHOD_CHAP        2
#define PPP_AUTH_METHOD_MSCHAP      3


/** Given a ppp  auth method string, return the equivalent auth method number.
 *
 *
 * @param authStr (IN) The auth method string.
 *
 * @return the  auth method number
 */
SINT32 util_pppAuthToNum(const char *authStr);

/** Given a ppp auth method number, return the equivalent auth method string.
 *
 *
 * @param authNum (IN) The auth method number.
 *
 * @return the  auth method string, this string is a pointer to a static string, so it
 * must not be modified or freed.
 */
char * util_numToPppAuthString(SINT32 authNum);


/** Given an IP address string, return true if it is a valid IP address.
 *
 * @param af      (IN) address family, either AF_INET or AF_INET6.
 * @param address (IN) IP address string.
 *
 * @return TRUE if the string is a valid IP address.
 */
UBOOL8 util_isValidIpAddress(SINT32 af, const char* address);


/** Given an IP address string, return true if it is a valid IPv4 address.
 *
 * @param address (IN) IP address string.
 *
 * @return TRUE if the string is a valid IPv4 address.
 */
UBOOL8 util_isValidIpv4Address(const char* address);


/** Given a MAC address string, return true if it is a valid mac address
 *  string.  Note the string must be in the following format:
 *  xx:xx:xx:xx:xx:xx where x is a hex digit.
 *
 * @param macAddr (IN) mac address string.
 *
 * @return TRUE if the string is a valid mac address.
 */
UBOOL8 util_isValidMacAddress(const char* macAddress);


/** Given a port number string, return true if it is a valid port number.
 *
 * @param portNumberStr (IN) port number string.
 *
 * @return TRUE if the string is a valid port number.
 */
UBOOL8 util_isValidPortNumber(const char* portNumberStr);

/** Compare two strings.  Similar to strcmp except that NULL string will be
 *  treated as zero length string.
 *
 * @param s1 (IN) the first string.
 * @param s2 (IN) the second string.
 *
 * @return same return value as strcmp
 */
SINT32 util_strcmp(const char *s1, const char *s2);


/** Compare two strings disregarding case.  Similar to strcasecmp except that
 *  NULL string will be treated as zero length string.
 *
 * @param s1 (IN) the first string.
 * @param s2 (IN) the second string.
 *
 * @return same return value as strcasecmp
 */
SINT32 util_strcasecmp(const char *s1, const char *s2);


/** Compare two strings.  Similar to strncmp except that NULL string will be
 *  treated as zero length string.
 *
 * @param s1 (IN) the first string.
 * @param s2 (IN) the second string.
 * @param n  (IN) number of characters to compare.
 *
 * @return same return value as strncmp
 */
SINT32 util_strncmp(const char *s1, const char *s2, SINT32 n); 


/** Compare two strings disregarding case.  Similar to strncasecmp except that
 *  NULL string will be treated as zero length string.
 *
 * @param s1 (IN) the first string.
 * @param s2 (IN) the second string.
 * @param n  (IN) number of characters to compare.
 *
 * @return same return value as strcmp
 */
SINT32 util_strncasecmp(const char *s1, const char *s2, SINT32 n); 


/** locate a substring disregarding case.  Similar to strstr except that NUll string will be
 *  treated as zero length string.
 *
 * @param s1 (IN) the first string.
 * @param s2 (IN) the second string.
 *
 * @return same return value as strstr
 */
char *util_strcasestr(const char *s1, const char *s2);



/** locate a substring.  Similar to strstr except that NUll string will be
 *  treated as zero length string.
 *
 * @param s1 (IN) the first string.
 * @param s2 (IN) the second string.
 *
 * @return same return value as strstr
 */
char *util_strstr(const char *s1, const char *s2);

/* Copies the string form source string(src) to destination
 *  buffer(dest). If the src string is larger than destination
 *  buffer then atmost dlen-1 bytes are copied into destination
 *  and also the dest is null terminated.
 *
 * @param dest(OUT)- destination buffer 
 * @param src (IN) the source string.
 * @param dlen(IN)- destination buffer size 
 *
 * @return destination address(dest)
 */
char *util_strncpy(const char *func, UINT32 line, char *dest, const char *src, SINT32 dlen);

char *util_strncat(const char *func, UINT32 line, char *dest, const char *src, SINT32 dlen);

char *util_strncatf(const char *func, UINT32 line, char *dest, SINT32 dlen, const char *format, ...) __attribute__((format(printf, 5, 6)));

/** locate a sub-option string in a string of sub-options separated by commas.
 * 
 * This function is useful if you have a parameter string that looks like:
 * AAAA, AAAABBB, CCC, DD
 * and you want to know if sub-option AAAA is present.  Note that strstr cannot
 * be used here because if your parameter string was
 * AAAABBB, CCC, DD
 * and you used strstr to look for option AAAA, then strstr would return a pointer
 * to AAAABBB, which is not the sub-option string you were really looking for.
 * This is required by the DSL code in dealing with the AdslModulationCfg parameter.
 *
 * @param s1 (IN) the full sub-option string.  Sub-options can be separated by any
 *                number of spaces and commas.
 * @param s2 (IN) the sub-option string.
 *
 * @return TRUE if the subOption string was found in the fullOptionString.
 */


/** Return the length of the source string.  Similar to strlen except that NUll string will be
 *  treated as zero length string.
 *
 * @param src (IN) the source string.
 *
 * @return same return value as strlen if NULL, return 0.
 */
SINT32 util_strlen(const char *src);


SINT32 util_snprintf(const char *func, UINT32 line, char *str, UINT32 size, const char *format, ...);

SINT32 util_sprintf_alloc(const char *func, UINT32 line, char **str, const char *format, ...);

SINT32 safe_strncmpIgnoreCase(const char *s1, const char *s2, SINT32 n); 

SINT32 safe_strcmpIgnoreCase(const char *s1, const char *s2);


UBOOL8 util_isSubOptionPresent(const char *fullOptionString, const char *subOption);


/** Retrieve WAN protocol name of the given protocol ID
 *
 * @param prtcl     (IN) network protocol
 * @param portId  (OUT) name - protocol name for html
 *
 * @return None.
 */
void util_getWanProtocolName(UINT8 protocol, char *name, UINT32 nameLen) ;


/** Convert a linear array of DHCP Vendor Ids into a single comma separated string.
 *
 * @param vendorIds (IN) This is a sequence of DHCP Vendor Ids laid out as a single linear buffer.
 *                       There are MAX_PORTMAPPING_DHCP_VENDOR_IDS (5) chunks in the buffer.
 *                       Each chunk is DHCP_VENDOR_ID_LEN + 1 bytes long.  Within each chunk
 *                       there may be a single DHCP vendor id.
 *
 * @return comma separated string of vendor ids.  The caller is responsible for freeing
 *         this buffer.
 */
char *util_getAggregateStringFromDhcpVendorIds(const char *vendorIds);

/** Convert a comma separated string of vendor ids into a linear array of DHCP vendor ids.
 *
 * @param aggregateString (IN) This is a sequence of up to MAX_PORTMAPPING_DHCP_VENDOR_IDS(5) comma 
 *                             separated dhcp vendor id strings.
 *
 * @return a linear buffer of vendor ids.  The caller is responsible for freeing this buffer.
 */
char *util_getDhcpVendorIdsFromAggregateString(const char *aggregateString);


/** Get number of DHCP vendor ids in the aggregate string
 * 
 * This is not implemented yet because it is not needed.  But it seems like a
 * useful function to have.
 * 
 * @param aggregateString (IN) This is a sequence of up to MAX_PORTMAPPING_DHCP_VENDOR_IDS(5) comma 
 *                             separated dhcp vendor id strings.
 * 
 * @return number of DHCP vendor ids.
 */
UINT32 util_getNumberOfDhcpVendorIds(const char *aggregateString);


#define DSL_LINK_DESTINATION_PREFIX_PVC   "PVC:"
#define DSL_LINK_DESTINATION_PREFIX_SVC   "SVC:"


/** Convert connection mode string to a ConnectionModeType number
 *
 * @param connModeStr (IN) MDMVS_ string defined in mdm 
 *
 * @return a ConnectionModeType number
 */
ConnectionModeType util_connectionModeStrToNum(const char *connModeStr);

void util_generateUuidStr(char *str, int len, unsigned char *macAddress);

UBOOL8 util_ipStrToOctets(const char *input, char *output);


/** Encode a string with base 64
 * Warning: The caller would be responsible for free the memory
 *
 * @param value (IN) value
 * @param value (IN) vlen
 *
 * @return a pointer to encoded string memory 
 */
char *UTIL_base64Encode(const unsigned char *value, int vlen);

/** Decode a string with base 64
 * Warning: The caller would be responsible for free the memory
 *
 * @param value (IN) value
 * @param value (IN) rlen
 *
 * @return a pointer to decoded string memory 
 */
unsigned char *UTILs_base64Decode(const char *value, int *rlen);

UBOOL8 UTIL_strIsUTF8(const char *str);


/** Check the str first, if the str is not utf-8, then convert to utf8 or do nothing 
  *  Warning: If the ori string is utf8, the return value is NULL, The caller need check it and  response free the memory 
  * @param value (IN) value
  *
   * @return a pointer to utf-8 string memory 
 */
char *UTIL_strConvToUTF8(const char *str);

void UTIL_str2Upper(char *str);


#define UTIL_AF_SELECT_IPV4       0x0001
#define UTIL_AF_SELECT_IPV6       0x0002

#define UTIL_AF_SELECT_IPVX       (UTIL_AF_SELECT_IPV4 | UTIL_AF_SELECT_IPV6)

UBOOL8 util_isZeroIpvxAddress(UINT32 ipvx, const char *addr);

int uitl_strToHex(char *str,char *pszHex,int len);

int uitl_charToHex(char c);

int util_strIsInt(char *str);

int util_xmlSpecialCharConvert(char *src, char*dst, int length);

char* util_getUtf16OneLine(char* buf, int bufSize, FILE* fp);

#endif /* __UTIL_STRCONV_H__ */

