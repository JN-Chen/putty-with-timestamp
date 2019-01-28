/*
 * wincapi.c: implementation of wincapi.h.
 */

#include "putty.h"

#if !defined NO_SECURITY

#define WINCAPI_GLOBAL
#include "wincapi.h"
#include <windows.h>
int got_crypt(void)
{
    static int attempted = FALSE;
    static int successful;
    static HMODULE crypt;

    if (!attempted) {
        attempted = TRUE;
        crypt = load_system32_dll("crypt32.dll");
        successful = crypt &&
#ifdef COVERITY
            /* The build toolchain I use with Coverity doesn't know
             * about this function, so can't type-check it */
            GET_WINDOWS_FUNCTION_NO_TYPECHECK(crypt, CryptProtectMemory)
#else
            GET_WINDOWS_FUNCTION(crypt, CryptProtectMemory)
#endif
            ;
    }
    return successful;
}

#endif /* !defined NO_SECURITY */


void sysUsecTime(char* str_time){
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	sprintf(str_time, "[%02d:%02d:%02d.%03d]", sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
}
