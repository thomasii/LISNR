#ifndef IMAGE_ENCODER_H
#define IMAGE_ENCODER_H

#include <string>

// Fetches image from `url`, Base64-encodes it (RFC4648),
// and writes result into `out_base64`. Returns true on success.
bool encode_image_from_url(const std::string& url, std::string& out_base64);

#endif // IMAGE_ENCODER_H