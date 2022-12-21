#ifndef __UTIL_XML_H__
#define __UTIL_XML_H__



/*!\file util_xml.h
 * \brief Header file for XML string escaping/unescaping functions.
 *
 * These functions allow callers to escape strings that contain
 * reserved XML characters, < > % &, and unescape them again.
 *
 */


/** Escape any reserved XML characters in the given string.
 * 
 * @param string        (IN)  Input string which may contain reserved XML characters.
 * @param escapedString (OUT) This function will allocate a buffer and put the
 *                            escaped string in it.  The caller is
 *                            responsible for freeing this buffer.
 *
 * @return VOS_RET_E enum.
 */ 
VOS_RET_E utilXml_escapeString(const char *string, char **escapedString);


/** Convert a string with escaped XML characters back into normal string.
 * 
 * @param escapedString (IN)  Input string which may contain escaped character sequences.
 * @param string        (OUT) This function will allocate a buffer and put
 *                            the unescaped string into the buffer.  The caller
 *                            is responsible for freeing the buffer.
 * @return VOS_RET_E enum.
 */
VOS_RET_E utilXml_unescapeString(const char *escapedString, char **string);



#endif  /* __VOS_HEXBINARY_H__ */
