/*****************************************************************************
 *
 * Filename:
 * ---------
 *    nvram_sock.h
 *
 * Project:
 * --------
 *    User Nvram Server
 *
 * Description:
 * ------------
 *    Provide interfaces for nvram server/client application to access.
 *
 * Author:
 * -------
 *    Landen
 *
 *============================================================================
 ****************************************************************************/
#ifndef NVRAM_SERVER_CTRL_IF_H
#define NVRAM_SERVER_CTRL_IF_H

#include <ctype.h>
#include <stdint.h>
#include "nvram.h"

/* Interface direction - client --> rplayer */ 
#define NVRAM_SERVER_NAME	"/tmp/nvram_srv.sock"
#define NVRAM_CIENT_NAME	"/tmp/nvram_clnt"

struct nvram_srv_msg {
	int		msg_id;
	uint32_t	index;
	uint32_t	data_len;
	char		name[MAX_NAME_LEN];
	char		value[MAX_VALUE_LEN];
};

#define NVRAM_SRV_MSG_HEADER_SIZE (sizeof(((struct nvram_srv_msg *)0)->msg_id) + sizeof(((struct nvram_srv_msg *)0)->index) + sizeof(((struct nvram_srv_msg *)0)->data_len) + 1)

#endif /* NVRAM_SERVER_CTRL_IF_H */
