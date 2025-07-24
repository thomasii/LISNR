/**
 * @file image_encoder.h
 * @brief Provides an API to fetch an image from a URL and Base64-encode it (RFC 4648).
 *
 * @details
 * This library uses libcurl to download the raw binary of an image,
 * then encodes it into a Base64 string.
 */

#ifndef IMAGE_ENCODER_H
#define IMAGE_ENCODER_H

#include <string>

// Export macro for Windows DLL
#if defined(_WIN32) || defined(__CYGWIN__)
  #ifdef IMAGE_ENCODER_EXPORTS
    #define IMAGE_ENCODER_API __declspec(dllexport)
  #else
    #define IMAGE_ENCODER_API __declspec(dllimport)
  #endif
#else
  #define IMAGE_ENCODER_API
#endif

/**
 * @brief Downloads an image from the given URL and Base64-encodes it.
 * 
 * @param url The HTTP(S) URL of the image to fetch.
 * @param out_base64 [out] Will be set to the Base64-encoded image data.
 * @return true if the download and encode succeeded; false on any error.
 *
 */
IMAGE_ENCODER_API bool encode_image_from_url(
    const std::string& url,
    std::string& out_base64
);

#endif // IMAGE_ENCODER_H
