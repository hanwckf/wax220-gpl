#ifndef __FOTA_CURL_H__
#define __FOTA_CURL_H__

int curl_download_file_ftp(char * pUrl, char *pFw_local_path);
int curl_download_file_https(char * pUrl, char *pFw_local_path);
int curl_download_file_http(char * pUrl, char *pFw_local_path);

#endif

