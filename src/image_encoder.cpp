#include "image_encoder.h"
#include <stdlib.h>
#include <stdio.h>

// stub or real implementations:
IE_Result ie_fetch_and_encode(const char *url, char **out_base64) {
    if(!url||!out_base64) return IE_ERR_INVALID_ARG;
    *out_base64 = (char*)malloc(1);
    if(!*out_base64) return IE_ERR_OOM;
    (*out_base64)[0] = '\0';
    return IE_OK;
}

IE_Result ie_write_base64_to_file(const char *base64, const char *filepath) {
    if(!base64||!filepath) return IE_ERR_INVALID_ARG;
    FILE *f = fopen(filepath,"wb");
    if(!f) return IE_ERR_FILE;
    fprintf(f, "%s", base64);
    fclose(f);
    return IE_OK;
}

void ie_free(char *ptr) {
    free(ptr);
}
