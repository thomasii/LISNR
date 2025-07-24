/**
 * @file image_encoder.cpp
 * @brief Implementation of the Image Encoder API.
 *
 * Uses libcurl to fetch image bytes, then encodes them using RFC4648 Base64.
 *
 * @see image_encoder.h
 */

#include "image_encoder.h"
#include <curl/curl.h>
#include <vector>

/**
 * @brief libcurl write callback to accumulate downloaded bytes into a buffer.
 *
 * @param contents Pointer to the delivered data.
 * @param size Size of each data element.
 * @param nmemb Number of elements.
 * @param userp Pointer to the buffer (std::vector<unsigned char>).
 * @return Number of bytes processed.
 */
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    auto* buffer = static_cast<std::vector<unsigned char>*>(userp);
    size_t total = size * nmemb;
    unsigned char* data = static_cast<unsigned char*>(contents);
    buffer->insert(buffer->end(), data, data + total);
    return total;
}

/**
 * @brief Lookup table of Base64 characters (RFC 4648).
 *
 * This static constant string provides the mapping from 6-bit
 * values to their corresponding ASCII characters during Base64
 * encoding. It is needed to convert each 6-bit group of the input
 * into the proper printable character.
 */
static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

/**
 * @brief Base64-encodes a byte array (RFC4648).
 *
 * @param bytes_to_encode Pointer to the data to encode.
 * @param in_len Number of bytes to encode.
 * @return A std::string containing the Base64-encoded output.
 */
static std::string base64_encode(const unsigned char* bytes_to_encode, size_t in_len) {
    std::string ret;
    int i = 0, j = 0;
    unsigned char char_array_3[3], char_array_4[4];

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            for (i = 0; i < 4; ++i) ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }
    if (i) {
        for (j = i; j < 3; ++j) char_array_3[j] = '\0';
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        for (j = 0; j < i + 1; ++j) ret += base64_chars[char_array_4[j]];
        while (i++ < 3) ret += '=';
    }
    return ret;
}

/**
 * @brief Downloads an image from the specified URL and Base64-encodes it.
 *
 * @param url The HTTP(S) URL of the image to fetch.
 * @param out_base64 [out] Will be set to the Base64-encoded image data.
 * @return true on success, false on error (download or encode failure).
 *
 * @see image_encoder.h
 */
IMAGE_ENCODER_API bool encode_image_from_url(
    const std::string& url,
    std::string& out_base64
) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::vector<unsigned char> image_data;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &image_data);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        return false;
    }

    out_base64 = base64_encode(image_data.data(), image_data.size());
    return true;
}
