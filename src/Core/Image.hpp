#ifndef IMG_HPP
#define IMG_HPP

#include <utility>
// #include <glm/glm.hpp>
#include "Core/vec4.hpp"


class string_view;

namespace rte
{
	enum ImgType
	{
		None = 0 << 0,
		JPG = 1 << 0,
		BMP = 1 << 1,
		HDR = 1 << 2,
		PNG = 1 << 3,
		TGA = 1 << 4,
	};

	class ImageSpec
	{
	public:
		ImageSpec() = default;
		ImageSpec(const size_t& w, const size_t& h, const uint8_t& _type) : width(w), height(h), type(_type), size(w*h) {
			(type & 1 << 3 || type & 1 << 4) ? channels = 4 : channels = 3;
			AspectRatio(-1);
		}

		ImageSpec(const size_t& size, const uint8_t& _type) : width(size), height(size), type(_type), size(size * size) {
			(type & 1 << 3 || type & 1 << 4) ? channels = 4 : channels = 3;
			AspectRatio(-1);
		}

		~ImageSpec()
		{
			width = 0;
			height = 0;
			type = ImgType::None;
			channels = 0;
			size = 0;
			aspect_ratio = 0;
		}

	public:
		size_t Channels() const { return channels; }

		void Type(const ImgType _t) { type = _t; }
		uint8_t Type() const { return type; }

		void AspectRatio(const double& ar = -1.0)
		{
			if (ar < 0)
			{
				aspect_ratio = static_cast<double>(width) / static_cast<double>(height);
			}
			else
			{
				aspect_ratio = ar;
			}
		}
		double AspectRatio() const { return aspect_ratio; }
	
		size_t Dimensions() const { return size; }

	public:
		size_t width = 256;
		size_t height = 256;

	private:
		uint8_t type = ImgType::JPG;
		size_t channels = 3;
		size_t size = 0;
		double aspect_ratio = 1.0;
	};

	class Image
	{
	public:
		Image();
		Image(const ImageSpec& spec);
		Image(ImageSpec&& spec);
		~Image();

	public:
		void writeToDisk(std::string_view fp, bool fillAlpha = true, double fillValue = 1.0);
		void generate_noise(int seed = 0);
		const ImageSpec& GetSpec() const;
	public:
		vec4* pixels = nullptr;

	private:
		ImageSpec m_specification;
	};
}

#endif // !IMG_HPP
