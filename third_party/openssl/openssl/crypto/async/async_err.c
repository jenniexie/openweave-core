/*
 * Generated by util/mkerr.pl DO NOT EDIT
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>
#include <openssl/err.h>
#include <openssl/async.h>

/* BEGIN ERROR CODES */
#ifndef OPENSSL_NO_ERR

# define ERR_FUNC(func) ERR_PACK(ERR_LIB_ASYNC,func,0)
# define ERR_REASON(reason) ERR_PACK(ERR_LIB_ASYNC,0,reason)

static ERR_STRING_DATA ASYNC_str_functs[] = {
    {ERR_FUNC(ASYNC_F_ASYNC_CTX_NEW), "async_ctx_new"},
    {ERR_FUNC(ASYNC_F_ASYNC_INIT_THREAD), "ASYNC_init_thread"},
    {ERR_FUNC(ASYNC_F_ASYNC_JOB_NEW), "async_job_new"},
    {ERR_FUNC(ASYNC_F_ASYNC_PAUSE_JOB), "ASYNC_pause_job"},
    {ERR_FUNC(ASYNC_F_ASYNC_START_FUNC), "async_start_func"},
    {ERR_FUNC(ASYNC_F_ASYNC_START_JOB), "ASYNC_start_job"},
    {0, NULL}
};

static ERR_STRING_DATA ASYNC_str_reasons[] = {
    {ERR_REASON(ASYNC_R_FAILED_TO_SET_POOL), "failed to set pool"},
    {ERR_REASON(ASYNC_R_FAILED_TO_SWAP_CONTEXT), "failed to swap context"},
    {ERR_REASON(ASYNC_R_INIT_FAILED), "init failed"},
    {ERR_REASON(ASYNC_R_INVALID_POOL_SIZE), "invalid pool size"},
    {0, NULL}
};

#endif

int ERR_load_ASYNC_strings(void)
{
#ifndef OPENSSL_NO_ERR

    if (ERR_func_error_string(ASYNC_str_functs[0].error) == NULL) {
        ERR_load_strings(0, ASYNC_str_functs);
        ERR_load_strings(0, ASYNC_str_reasons);
    }
#endif
    return 1;
}
