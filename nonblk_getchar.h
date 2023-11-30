#ifndef NONBLK_GETCHAR_H
#define NONBLK_GETCHAR_H
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
extern int nonblk_getkey(void);
extern int nonblk_getInput(char* buf, size_t len);

#ifdef __cplusplus
}
#endif
#endif /* NONBLK_GETCHAR_H */
