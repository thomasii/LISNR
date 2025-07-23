#include "ImageEncoder.hpp"
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <URL> <output-file>\n";
    return 1;
  }

  try {
    std::string b64 = ImageEncoder::fetchAndEncode(argv[1]);
    ImageEncoder::writeToFile(b64, argv[2]);
    std::cout << "Base64 data written to " << argv[2] << "\n";
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
