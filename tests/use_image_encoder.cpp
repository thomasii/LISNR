#include <iostream>
#include "image_encoder.h"

int main() {
    std::string out;
    if (!encode_image_from_url("https://cdn.pixabay.com/photo/2025/07/12/10/04/reinebringen-9710168_1280.jpg", out)) {
        std::cerr << "Failed to fetch/encode" << std::endl;
        return 1;
    }
    std::cout << out << std::endl;
    return 0;
}