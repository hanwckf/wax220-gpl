#ifndef __XML_PARSER_SM_H__
#define __XML_PARSER_SM_H__


/*----------------------------------------------------------------------*
<:copyright-broadcom 
 
 Copyright (c) 2005 Broadcom Corporation 
 All Rights Reserved 
 No portions of this material may be reproduced in any form without the 
 written permission of: 
          Broadcom Corporation 
          16215 Alton Parkway 
          Irvine, California 92619 
 All information contained in this document is Broadcom Corporation 
 company private, proprietary, and trade secret. 
 
:>
 *----------------------------------------------------------------------*
 * File Name  : xmlParserSM.h
 *
 * Description: xmlParser state machine 
 *   
 *  
 * $Revision: 1.4 $
 * $Id: xmlParserSM.h,v 1.4 2005/05/12 19:34:31 dmounday Exp $
 *----------------------------------------------------------------------*/
/* *
 * The callbacks are only called if they are found in the correct state
 * as defined by the XmlNodeDesc tables below. 
 * Each node contains a tag and attribute list that is valid for the node.
 * Associated with
 * each tag or attribute name is the function pointer. Functions associated
 * with tag names are called on the start of the tag with a ttype of TAGBEGIN and
 * when the tag end is found with a ttype of TAGEND. Data found in between the
 * state and end of a tag causes a callback with ttype of TAGDATA.
 * Functions associated with attributes are called when the value is determined.
 * If the XML structure is syntacly valid then unknown tags are quitely parsed
 * and ignored. 
 * The scanSink function variable in parseState may be set to cause the callbacks
 * to write the parsed XML to a file or else where for processing. This parsed
 * XML has blanks removed and the line breaks altered.  The nodeFlags must also be 
 * set to XML_SCAN_F in order for the scanSink function to be called. A typical
 * use of this function is to enable the sink function in the TAGBEGIN and disable
 * it in the TAGEND function. All of the XML within the TAG will be written 
 * to the sink function.
 * 
 * The parse_error routine function variable defined in parseState is called
 * when there are XML structure errors or unknow attributes within a know tag.
 * Unknow tags and their nested tags and attributes are ignored.
* Example fragment of xml tree definition:
*
*       XmlNodeDesc mgmtDesc[] = {
*           {"response", setResponse,&responseDesc},
*            {"version", setEscVersion, NULL},
*            {"gwapp", NULL,NULL},
*            {NULL, NULL, NULL},
*        };
*        
*        XmlNodeDesc topLevel[] = {
*            {"escmgmt", setEscMgmt, &mgmtDesc},
*            {"escconf", setEscconf, &escconfDesc}, 
*            {"system", setSystem, &systemDesc},
*            {NULL,NULL,NULL}
*        };
* The first element of the structure is the tagName or attrName, the second is a function pointer.
* The third element is NULL if the entry describes an attribute, or a pointer to the next
* level node descriptor if the entry describes a tag.
* If the parser state machine finds a tag it will call the function once at the beginning of the tag
* and once at the end. If the parserSM finds an attribute the function is called when the
* value has been collected. The function pointer may be set to NULL. 
* In the above each node is defined by a XmlNodeDesc structure array that contains an
* entry for each item at the node. For example topLevel would represent the tag escmgmt as:
*
*       <ecsmgmt version="0.1" gwapp="trx">
*           <response ....... 
*           </response>
*       </escmgmt>
* */
/* The more argument in xmlData and xmlValue indicate that more data is pending */
/* If the more flag is set the callback will be called again with data that is */
/* to be appended to the current data. Mutlitple callbacks can occur befor the */
/* more flag is reset. This is caused if a data item spans multiple write_xml calls */

#include "xml_nano.h"

/*****
static void xmlTagBegin( nxml_t handle, const char *tagName, unsigned lth);

static void xmlTagEnd ( nxml_t handle, const char *tagName, unsigned lth);
static void xmlData( nxml_t handle, const char *dataValue, unsigned lth, int more);

static void xmlAttr( nxml_t handle, const char *attrName, unsigned lth);

static void xmlValue( nxml_t handle, const char *attrValue, unsigned lth, int more);
*****/

typedef enum {
    NO_ERROR = 0,
    PARSE_ERROR
} eParseStatus;

typedef struct ParseHow {
    XmlNodeDesc *topLevel;
    NameSpace   *nameSpace;
} ParseHow;

#define XML_BUFSIZE 4096
eParseStatus parseGeneric(char *path, char *memory, int size, ParseHow *parseHow );


#endif    /* __XML_PARSER_SM_H__ */
