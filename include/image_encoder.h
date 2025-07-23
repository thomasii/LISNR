#ifndef IMAGE_ENCODER_H
#define IMAGE_ENCODER_H

#ifdef _WIN32
  #ifdef IMAGE_ENCODER_EXPORTS
    #define IE_API __declspec(dllexport)
  #else
    #define IE_API __declspec(dllimport)
  #endif
#else
  #define IE_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

/// Error codes
typedef enum {
  IE_OK = 0,
  IE_ERR_NETWORK,
  IE_ERR_ENCODING,
  IE_ERR_OOM,
  IE_ERR_FILE,
  IE_ERR_INVALID_ARG
} IE_Result;

/**
 * Fetches the image at `url`, Base64-encodes it (RFC 4648),
 * and returns a newly-malloc’d NUL-terminated string in `*out_base64`.
 *
 * @param url           NUL-terminated URL of the image to fetch.
 * @param out_base64    On success, *out_base64 will point to a heap buffer
 *                      holding the Base64 string. Caller must free() it.
 * @return IE_OK on success, or an error code.
 */
IE_API IE_Result ie_fetch_and_encode(
    const char *url,
    char **out_base64
);

/**
 * Writes the NUL-terminated Base64 string `base64` to `filepath`.
 *
 * @param base64   NUL-terminated Base64 data.
 * @param filepath Path to the output file.
 * @return IE_OK on success, or IE_ERR_FILE if writing fails.
 */
IE_API IE_Result ie_write_base64_to_file(
    const char *base64,
    const char *filepath
);

/**
 * Frees memory returned by ie_fetch_and_encode().
 *
 * @param ptr  Pointer returned in *out_base64.
 */
IE_API void ie_free(char *ptr);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // IMAGE_ENCODER_H
