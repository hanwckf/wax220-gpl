#ifndef __BT_H__
#define __BT_H__

#define BT_VERSION_MAJOR    (1)
#define BT_VERSION_MINOR    (0)

int BT_genBacktrace(void **buffer, int size);
void BT_printBacktrace(void **buffer, int size);

void BT_sigHandler(int sig);
void BT_init(int spySig);

#endif /* __BT_H__ */
