#include <iostream>
#include <fstream>
#include <getopt.h>

int main(int argc, char *argv[]) {
    std::string filename;
    std::streampos minByte, maxByte;

    struct option long_options[] = {
        {"file", required_argument, 0, 'f'},
        {"min_byte", required_argument, 0, 'm'},
        {"max_byte", required_argument, 0, 'M'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "f:m:M:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'm':
                minByte = std::stoll(optarg);
                break;
            case 'M':
                maxByte = std::stoll(optarg);
                break;
            default:
                std::cerr << "Invalid arguments\n";
                return 1;
        }
    }

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::streampos fileSize = file.tellg();
    if (minByte > fileSize) {
        std::cerr << "Minimum byte is larger than file size\n";
        return 1;
    }

    if (maxByte > fileSize) {
        maxByte = fileSize;
    }

    file.seekg(minByte);
    char buffer;
    while (file.tellg() <= maxByte && file.get(buffer)) {
        std::cout << buffer;
    }

    return 0;
}