/*****************************************************************************
 *============================================================================
 *                               HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Log$
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
/*****************************************************************************
 *
 * Filename:
 * ---------
 *    linux_socket.h
 *
 * Project:
 * --------
 *    Audio Route
 *
 * Description:
 * ------------
 *    This is a proprietary linux socket interface for bt agent to communicate each other.
 *
 * Author:
 * -------
 *    Iverson Hsieh
 *
 *============================================================================
 ****************************************************************************/
#ifndef LINUX_SOCKET_H
#define LINUX_SOCKET_H

/*****************************************************************/
/*                       INCLUDE FILES                           */
/*****************************************************************/


/*****************************************************************/
/*                     MACROS & CONTSTANTS                       */
/*****************************************************************/


/*****************************************************************/
/*                      DATA STRUCTURE                           */
/*****************************************************************/
 
 
/*****************************************************************/
/*                      FUNCTION PROTOTYPE                       */
/*****************************************************************/
/*
 *  Datagram socket server APIs.
 */
int socket_gram_srv_create(const char *name);
void socket_gram_srv_close(int sock, const char *name);
ssize_t socket_gram_srv_recv(int sock, char *buf, int len);
ssize_t socket_gram_srv_recvfrom(int sock, char *buf, int len, struct sockaddr_un *cli_addr, socklen_t *sock_len);
ssize_t socket_gram_srv_send(int sock, char *data, int len);
ssize_t socket_gram_srv_sendto(int sock, char *data, ssize_t len, struct sockaddr *cli_addr, socklen_t sock_len);

/*
 *  Datagram socket client APIs.
 */
int socket_gram_clnt_create(void);
void socket_gram_clnt_close(int sock);
ssize_t socket_gram_clnt_recv(int sock, char *buf, int len);
ssize_t socket_gram_clnt_sendto(int sock, char *name, char *data, int len);

/*
 *  Data stream socket server implementation.
 */
int socket_stream_srv_create(const char *name);
void socket_stream_srv_close(int sock, const char *name);
void socket_stream_srv_accept_clnt_close(int sock);
int socket_stream_srv_listen(int sock);
int socket_stream_srv_accept(int sock);
int socket_stream_srv_set_timeout(int sock, int s, int ms);
int socket_stream_srv_recv(int sock, char *buf, int len);
int socket_stream_srv_send(int sock, char *data, int len);

/*
 *  Data stream socket client implementation.
 */
int socket_stream_clnt_create(const char *name);
void socket_stream_clnt_close(int sock);
int socket_stream_clnt_recv(int sock, char *buf, int len);
int socket_stream_clnt_send(int sock, char *data, int len);

/*****************************************************************/
/*                      EXTERNAL VARIABLE                        */
/*****************************************************************/

#endif /* LINUX_SOCKET_H */

