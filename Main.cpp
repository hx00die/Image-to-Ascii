#include <iostream>
#include <fstream>
#include <vector>
#include <string>

extern "C" {
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
}
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

bool load_image(std::vector<unsigned char>& image, const std::string& filename, int& x, int& y)
{
    int n;
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 4);
    unsigned char* sized_data = data;
    stbir_resize_uint8(data, x, y, 0, sized_data, 100, 100, 0, 4);
    if (data != nullptr)
    {
        image = std::vector<unsigned char>(sized_data, sized_data + 100 * 100 * 4);
    }
    stbi_image_free(data);
    return (data != nullptr);
}

char BestCharector(float colour) {
    switch ((int)(colour * 11.0f)) {
    case 0: return '@';
    case 1: return '#';
    case 2: return '%'; 
    case 3: return 'x'; 
    case 4: return 'o'; 
    case 5: return ';'; 
    case 6: return ':'; 
    case 7: return ','; 
    case 8: return '.'; 
    case 9: return ' ';
    }
}

void convert2ascii(std::vector<unsigned char> image, const size_t &RGBA, int width, int height) {
    char charector;
    std::fstream file;
    file.open("image.txt", std::ios::out);
    if (file.is_open()) {
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                size_t index = RGBA * (j * width + i);
                float r = static_cast<int>(image[index + 0]) / 255.0f;
                float g = static_cast<int>(image[index + 1]) / 255.0f;
                float b = static_cast<int>(image[index + 2]) / 255.0f;
                float colour = r * 0.3 + g * 0.59 + b * 0.11;
                charector = BestCharector(colour);
                file << charector;
            }
            file << '\n';
        }
        file.close();
    }
}

int main()
{
    std::string filename;
    std::cout << "Enter the path to image file: ";
    std::cin >> filename;

    int width, height;
    int fixedWidth = 100, fixedHeight = 100;
    
    std::vector<unsigned char> image;
    bool success = load_image(image, filename, width, height);
    if (!success)
    {
        std::cout << "Error loading image\n";
        return 1;
    }

    std::cout << "Image width = " << width << '\n';
    std::cout << "Image height = " << height << '\n';
    std::cout << "Dimensions changed to 100x100\n";
    
    const size_t RGBA = 4;
    convert2ascii(image, RGBA, 100, 100);
    std::cout << "Done!\n";
    
    char key;
    std::cout << "Press a key and then enter to close the window. ";
    std::cin >> key;

    return 0;
}
