#include <iostream>
#include <random>

#include "Core/Image.hpp"

int main()
{
    // Image
    constexpr uint16_t WIDTH = 2048;
    constexpr uint16_t HEIGHT = 1024;


    {
        ImageSpec spec = ImageSpec(WIDTH, HEIGHT, 31);
        Image img(spec);

        std::mt19937_64 generator(0);
        std::uniform_real_distribution<float> red(0, 1.0f);
        std::uniform_real_distribution<float> green(0, 1.0f);
        std::uniform_real_distribution<float> blue(0, 1.0f);

        // Render
        for (int j = 0; j < HEIGHT; j++) {
            std::clog << "\rScanlines remaining: " << (HEIGHT - j) << ' ' << std::flush;
            for (int i = 0; i < WIDTH; i++) {
                size_t idx = ((j * WIDTH) + i);

                img.m_data[idx].r = red(generator);     // Red channel (U)
                img.m_data[idx].g = green(generator); // Green channel (V)
                img.m_data[idx].b = blue(generator);
            }
        }
        std::clog << std::endl;

        img.writeToDisk("../test", true);
        std::clog << "\rDone\t\t\t\t";
        std::cin.get();
    }
    std::cin.get();
}