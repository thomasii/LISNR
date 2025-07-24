/**
 * @file use_image_encoder.cpp
 * @brief Example program that fetches and Base64-encodes a hard-coded image URL.
 *
 * Demonstrates usage of the `encode_image_from_url` API from the image_encoder library.
 *
 * @see image_encoder.h
 */

#include <iostream>
#include "image_encoder.h"

/**
 * @brief Entry point for the example usage program.
 *
 * Fetches the image at a predefined URL, encodes it in Base64, and prints the result.
 *
 * @return int Returns 0 on success; 1 if fetching or encoding fails.
 */
int main() {
    std::string out;
    if (!encode_image_from_url(
            "https://cdn.pixabay.com/photo/2025/07/12/10/04/reinebringen-9710168_1280.jpg",
            out
        )) {
        std::cerr << "Failed to fetch/encode" << std::endl;
        return 1;
    }

    std::cout << out << std::endl;
    return 0;
}
