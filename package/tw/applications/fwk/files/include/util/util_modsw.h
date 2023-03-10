/***********************************************************************
 *
 *  Copyright (c) 2006-2007  Broadcom Corporation
 *  All Rights Reserved
 *
 * <:label-BRCM:2011:DUAL/GPL:standard
 * 
 * Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed
 * to you under the terms of the GNU General Public License version 2
 * (the "GPL"), available at http://www.broadcom.com/licenses/GPLv2.php,
 * with the following added to such license:
 * 
 *    As a special exception, the copyright holders of this software give
 *    you permission to link this software with independent modules, and
 *    to copy and distribute the resulting executable under terms of your
 *    choice, provided that you also meet, for each linked independent
 *    module, the terms and conditions of the license of that module.
 *    An independent module is a module which is not derived from this
 *    software.  The special exception does not apply to any modifications
 *    of the software.
 * 
 * Not withstanding the above, under no circumstances may you combine
 * this software in any way with any other Broadcom software provided
 * under a license other than the GPL, without Broadcom's express prior
 * written consent.
 * 
:>
 *
 ************************************************************************/

#ifndef __UTIL_PARAMS_MODSW_H__
#define __UTIL_PARAMS_MODSW_H__

/*!\file cms_params_modsw.h
 * \brief Header file containing customizable parameters related to
 *               Modular Software.
 */



/** Path to Modular Software dir.
 */
#define UTIL_MODSW_DIR   "/var/config/modsw"


/** Path to tmp modsw dir.  Files are initially downloaded to tmp before
 *  they are put in their correct location.
 */
#define UTIL_MODSW_TMP_DIR   "/var/config/modsw/tmp"


/** Common path to both OSGI DU and Linux DU.
 *
 */
#define UTIL_MODSW_DU_DIR    "/var/config/modsw/tr157du"


/** Path to TR157 Deployment Unit Directory for OSGI bundles.
 *  OSGI bundle deployment units are put in this directory based on their
 *  name, e.g. /var/config/modsw/tr157du/osgibundle/bundle_name...
 * So each DU has its own directory.
 */
#define UTIL_MODSW_OSGIEE_DU_DIR    "/var/config/modsw/tr157du/osgibundles"


/** Path to TR157 Deployment Unit Dir for Linux packages.
 * Linux deployment units are put in this directory based on their name,
 * e.g. /var/config/modsw/tr157du/linux/du_name...
 * So each DU has its own directory.
 */
#define UTIL_MODSW_LINUXEE_DU_DIR    "/var/config/modsw/tr157du/linuxpkgs"


/** Path to TR157 Primary Firmware Patch dir.  Patches to the primary firmware
 *  are put in this directory based on their name,
 *  e.g. /var/config/modsw/tr157pfp/pfpname/...
 *  So each Primary Firmware Patch has its own directory.
 */
#define UTIL_MODSW_LINUXPFP_DIR   "/var/config/modsw/tr157pfp"


/** First 32 bytes of a Primary Firmware Patch consists of this string.
 *  This string must be 32 bytes, as specified by CMS_MODSW_LINUX_HEADER1_LEN
 *  below.
 */
#define UTIL_MODSW_LINUXPFP_HEADER "BCMTR157:Linux:PrimFirmwrePatch;"


/** First 32 bytes of a Linux Deployment Unit (DU) consists of this string.
 *  This string must be 32 bytes, as specified by CMS_MODSW_LINUX_HEADER1_LEN
 *  below.
 */
#define UTIL_MODSW_LINUXEE_DU_HEADER "BCMTR157:LinuxEE:DeploymentUnit;"


/** Length of first Header section.
 */
#define UTIL_MODSW_LINUX_HEADER1_LEN    32


/** Length of second Header section, which is the name of the patch or DU.
 *  If the name is shorter than the length, the remaining bytes must
 *  contain 0.
 */
#define UTIL_MODSW_LINUX_HEADER2_LEN    128


/** Text header in the outer tarball */
#define UTIL_MODSW_OUTER_HEADER_NAME    "outer-header.txt"


/** Below are the keywords allowed in version 1 of the outer-header */
#define BCMPKG_VERSION                1

#define BCMPKG_KW_VERSION             "version"
#define BCMPKG_TK_VERSION             1001

#define BCMPKG_KW_INNERFILENAME       "innerFilename"
#define BCMPKG_TK_INNERFILENAME       1002
/* matches max length defined for TR181 Execution Unit name */
#define BCMPKG_INNERFILENAME_MAX_LEN  32

#define BCMPKG_KW_CHECKSUMALGO        "checksumAlgo"
#define BCMPKG_TK_CHECKSUMALGO        1003

#define BCMPKG_KW_CHECKSUM            "checksum"
#define BCMPKG_TK_CHECKSUM            1004

#define BCMPKG_SHA1_CHECKSUM_LEN      40


/** Text header in the inner tarball */
#define UTIL_MODSW_INNER_HEADER_NAME    "inner-header.txt"

/** Below are the keywords allowed in version 1 of the inner-header */
#define BCMPKG_KW_PKGVERSION          "pkgVersion"
#define BCMPKG_TK_PKGVERSION          2001
#define TR157_VERSION_STR_LEN         32

#define BCMPKG_KW_PKGDESCRIPTION      "pkgDescription"
#define BCMPKG_TK_PKGDESCRIPTION      2002
#define TR157_DESCRIPTION_STR_LEN     256

#define BCMPKG_KW_INNERVERSION        "innerVersion"
#define BCMPKG_TK_INNERVERSION        2003

#define BCMPKG_KW_INNERDESCRIPTION    "innerDescription"
#define BCMPKG_TK_INNERDESCRIPTION    2004



/** Debug log for storing various ModSw operations.  Use of this file is
 *  deprecated.  Was OSGID_LOG_FILE.
 */
#define UTIL_MODSW_DEBUG_LOG           "/var/config/modsw/tmp/DuLog"


/*
 * Defines specific to the Linux Execution Environment.
 */

#define LINUXEE_NAME     "Linux"
#define LINUXEE_TYPE     "Linux"
#define LINUXEE_VENDOR   "Linux"
#define LINUXEE_VERSION  "3.4"

#endif  /* __UTIL_PARAMS_MODSW_H__ */
