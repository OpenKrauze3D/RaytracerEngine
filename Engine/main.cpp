#include <iostream>

#include <glm/glm.hpp>
#include "Image.hpp"

int main()
{
    // Image
    constexpr uint16_t WIDTH = 256;
    constexpr uint16_t HEIGHT = 256;
    constexpr uint8_t CHANNELS = 3;

    ImageSpec spec = ImageSpec(WIDTH, HEIGHT, 31);
    Image img(spec);

    // Render
    for (int j = 0; j < HEIGHT; ++j) {
        std::clog << "\rScanlines remaining: " << (HEIGHT - j) << ' ' << std::flush;
        for (int i = 0; i < WIDTH; ++i) {
            size_t idx = ((j * WIDTH) + i);

            img.m_data[idx].r = i / static_cast<double>(WIDTH);     // Red channel (U)
            img.m_data[idx].g = j / static_cast<double>(HEIGHT); // Green channel (V)
            img.m_data[idx].b = 0.0f;
        }
    }
    std::clog << std::endl;

    img.writeToDisk("../test", true);
    std::clog << "\rDone\t\t\t\t";
    std::cin.get();
}