#pragma once
#include <string>
#include <stdexcept>

// Forward-declare the C API:
extern "C" {
  #include "image_encoder.h"
}

class ImageEncoder {
public:
  /// Fetch & encode; throws std::runtime_error on error.
  static std::string fetchAndEncode(const std::string &url) {
    char *out = nullptr;
    IE_Result r = ie_fetch_and_encode(url.c_str(), &out);
    if (r != IE_OK) {
      throw std::runtime_error("Fetch/encode failed: " + std::to_string(r));
    }
    std::string result(out);
    ie_free(out);
    return result;
  }

  /// Write a Base64 string to disk; throws on failure.
  static void writeToFile(const std::string &b64, const std::string &path) {
    IE_Result r = ie_write_base64_to_file(b64.c_str(), path.c_str());
    if (r != IE_OK) {
      throw std::runtime_error("Write failed: " + std::to_string(r));
    }
  }
};
