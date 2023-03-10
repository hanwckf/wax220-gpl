#ifndef __FWK_H__
#define __FWK_H__


#include "vos/vos_defs.h"
#include "vos/vos_mem.h"
#include "vos/vos_eid.h"
#include "vos/vos_msg.h"
#include "vos/vos_sm.h"
#include "vos/vos_log.h"
#include "vos/vos_log_security.h"
#include "util/util_defs.h"
#include "util/util_ast.h"
#include "util/util_params.h"
#include "util/util_tms.h"
#include "util/util_strconv.h"
#include "util/util_fil.h"
#include "util/util_list.h"
#include "util/util_dlist.h"
#include "util/util_hashmap.h"
#include "util/util_base64.h"
#include "util/util_hexbinary.h"
#include "util/util_lzw.h"
#include "util/util_crc.h"
#include "util/util_xml.h"
#include "util/util_pwd.h"
#include "util/util_rand.h"
#include "util/util_ftrace.h"
#include "util/util_vector.h"
#include "util/util_shell.h"
#include "util/util_prctl.h"
#include "util/util_msg.h"
#include "util/util_cli.h"
#include "util/util_linklist.h"
#include "util/util_tmr.h"
#include "util/util_srpc.h"
#include "util/util_image.h"
#include "util/util_net.h"
#include "util/util_defs.h"
#include "xml/xml_nano.h"
#include "xml/xml_parser_sm.h"
//#include "sf/soft_feature_def.h"
//#include "sf/soft_feature_lib.h"
//#include "sf/soft_feature_def_comb.h"
#include "util/util_psp.h"
#include "util/util_modsw.h"
#include "util/util_nfc.h"
#include "util/util_sgw.h"
#include "util/util_utf8.h"
#include "util/util_misc.h"
#include "util/util_md5.h"
#include "util/util_task.h"
#include "util/util_security.h"
#include "util/util_sha256.h"
#include "bt/bt.h"
#include <errno.h>

#define DEBUG_FWK(args, ...) printf("%s %d : "args"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)

#endif /* __FWK_H__ */
