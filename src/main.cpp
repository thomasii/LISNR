#include "image_encoder.h"
#include <iostream>
#include <fstream>

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