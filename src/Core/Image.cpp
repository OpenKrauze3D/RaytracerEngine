#include <string_view>
#include <iostream>
#include <random>

#define STB_IMAGE_IMPLEMENTATION
#include <stb-image/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb-image/stb_image_write.h>
// #include <glm/glm.hpp>

#include "Core/Image.hpp"

#include <filesystem>
namespace rte
{
	Image::Image() {}
	
	Image::Image(const ImageSpec& spec)
	{
		m_specification = spec;
		pixels.resize(m_specification.Dimensions());
	}

	Image::Image(const Image& img)
	{
		m_specification = img.m_specification;
		pixels.reserve(img.m_specification.Dimensions());
		pixels.resize(m_specification.Dimensions());
	}

	Image::~Image()
	{
		pixels.clear();
	}

	void Image::writeToDisk(const std::string_view fp, bool fillAlpha, double fillValue)
	{
		uint8_t* imgBytes = nullptr;
		uint8_t* imgBytesWAlpha = nullptr;
		float* imgFloats = nullptr;

		// If there is non-HDR
		if ((m_specification.Type() & ImgType::JPG) || (m_specification.Type() & ImgType::BMP))
			imgBytes = new uint8_t[m_specification.Dimensions() * 3];

		if ((m_specification.Type() & ImgType::PNG) || (m_specification.Type() & ImgType::TGA))
			imgBytesWAlpha = new uint8_t[m_specification.Dimensions() * 4];

		if (m_specification.Type() & ImgType::HDR)
			imgFloats = new float[m_specification.Dimensions() * 3];

		std::cout << "Making image buffers!\n";
		for (size_t j = 0; j < m_specification.height; j++)
		{
			for (size_t i = 0; i < m_specification.width; i++)
			{
				const size_t index = i + (m_specification.width * j);
				const size_t chan3idx = index * 3;
				const size_t chan4idx = index * 4;

				const rte::vec4& pixel = pixels[index];

				if (imgFloats != nullptr)
				{
					imgFloats[chan3idx + 0] = pixel[0];
					imgFloats[chan3idx + 1] = pixel[1];
					imgFloats[chan3idx + 2] = pixel[2];
				}

				if (imgBytes != nullptr)
				{
					imgBytes[chan3idx + 0] = static_cast<uint8_t>(255.9999f * pixel[0]);
					imgBytes[chan3idx + 1] = static_cast<uint8_t>(255.9999f * pixel[1]);
					imgBytes[chan3idx + 2] = static_cast<uint8_t>(255.9999f * pixel[2]);
				}

				if (imgBytesWAlpha != nullptr)
				{
					imgBytesWAlpha[chan4idx + 0] = static_cast<uint8_t>(255.9999f * pixel[0]);
					imgBytesWAlpha[chan4idx + 1] = static_cast<uint8_t>(255.9999f * pixel[1]);
					imgBytesWAlpha[chan4idx + 2] = static_cast<uint8_t>(255.9999f * pixel[2]);
					imgBytesWAlpha[chan4idx + 3] = (!fillAlpha) ? (uint8_t)255.9999f * pixel[3] : static_cast<uint8_t>(255.9999f * fillValue);
				}
			}
		}
	
		std::cout << "Writing to disk!\n";
		std::cout << std::filesystem::current_path() << "\\" << fp << std::endl;

		for (size_t i = 0; i <= 4; i++)
		{
			const uint8_t mask = 1 << i;
			const uint8_t index = (this->m_specification.Type() & mask);
			switch (index)
			{
			case ImgType::JPG:
				std::cout << "Detected JPG\n";
				stbi_write_jpg(std::string(fp.data() + std::string(".jpg")).c_str(), m_specification.width, m_specification.height, 3, imgBytes, 100);
				break;
			case ImgType::BMP:
				std::cout << "Detected BMP\n";
				stbi_write_bmp(std::string(fp.data() + std::string(".bmp")).c_str(), m_specification.width, m_specification.height, 3, imgBytes);
				break;
			case ImgType::HDR:
				std::cout << "Detected HDR\n";
				stbi_write_hdr(std::string(fp.data() + std::string(".hdr")).c_str(), m_specification.width, m_specification.height, 3, imgFloats);
				break;
			case ImgType::PNG:
				std::cout << "Detected PNG\n";
				stbi_write_png(std::string(fp.data() + std::string(".png")).c_str(), m_specification.width, m_specification.height, m_specification.Channels(), imgBytesWAlpha, 0);
				break;
			case ImgType::TGA:
				std::cout << "Detected TGA\n";
				stbi_write_tga(std::string(fp.data() + std::string(".tga")).c_str(), m_specification.width, m_specification.height, m_specification.Channels(), imgBytesWAlpha);
				break;
			}
		}

		if (imgFloats != nullptr) 
		{ delete[] imgFloats; }
	
		if (imgBytesWAlpha != nullptr) 
		{ delete[] imgBytesWAlpha; }
	
		if (imgBytes != nullptr) 
		{ delete[] imgBytes; }
	}

	void Image::generate_noise(int seed)
	{
		std::mt19937_64 generator(seed);
		std::uniform_real_distribution<float> red(0, 1.0f);
		std::uniform_real_distribution<float> green(0, 1.0f);
		std::uniform_real_distribution<float> blue(0, 1.0f);

		const size_t width = m_specification.width;
		const size_t height = m_specification.height;
		// Render
		for (size_t j = 0; j < width; ++j) {
			for (size_t i = 0; i < height; ++i) {
				const size_t idx = ((j * width) + i);
    
				pixels[idx][0] = red(generator);     // Red channel
				pixels[idx][1] = green(generator);   // Green channel
				pixels[idx][2] = blue(generator);    // Blue channel
			}
		}
	}

	const ImageSpec& Image::GetSpec() const
	{
		return m_specification;
	}
}
