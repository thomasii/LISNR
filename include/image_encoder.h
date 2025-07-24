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

// Fetches image from `url`, Base64-encodes it (RFC4648),
// and writes result into `out_base64`. Returns true on success.
IMAGE_ENCODER_API bool encode_image_from_url(
    const std::string& url,
    std::string& out_base64
);

#endif // IMAGE_ENCODER_H