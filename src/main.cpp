/**
 * @file image_encoder_cli.cpp
 * @brief Command-line tool that fetches an image from a URL and writes its Base64 encoding to a file.
 *
 * This CLI wraps the `encode_image_from_url` API from the image_encoder library.
 * It downloads the image at the specified URL, encodes it (RFC4648), and saves the result.
 *
 * @see image_encoder.h
 */

#include "image_encoder.h"
#include <iostream>
#include <fstream>

/**
 * @brief Program entry point for the Base64 image encoder CLI.
 *
 * @param argc Argument count. Must be 3: program name, image URL, and output file path.
 * @param argv Argument vector. argv[1] = URL, argv[2] = output file path.
 * @return int Returns 0 on success; 1 on any error (usage, download, encoding, or file I/O).
 */
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <image_url> <output_file>\n";
        return 1;
    }
    std::string url = argv[1];
    std::string output_file = argv[2];

    std::string base64_data;
    if (!encode_image_from_url(url, base64_data)) {
        std::cerr << "Error: failed to encode image from URL: " << url << "\n";
        return 1;
    }

    std::ofstream ofs(output_file, std::ios::binary);
    if (!ofs) {
        std::cerr << "Error: could not open file: " << output_file << "\n";
        return 1;
    }
    ofs << base64_data;
    return 0;
}
