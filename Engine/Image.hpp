#ifndef IMG_HPP
#define IMG_HPP

#include <utility>
#include <glm/glm.hpp>

class string_view;

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
	}

	ImageSpec(const size_t& size, const uint8_t& _type) : width(size), height(size), type(_type), size(size * size) {
		(type & 1 << 3 || type & 1 << 4) ? channels = 4 : channels = 3;
	}

	~ImageSpec() = default;

public:
	size_t Channels() const { return channels; }
	void Type(const ImgType _t) { type = _t; }
	uint8_t Type() const { return type; }

	size_t Size() const { return size; }

public:
	size_t width = 256;
	size_t height = 256;

private:
	uint8_t type = ImgType::JPG;
	size_t channels = 3;
	size_t size = 0;
};

class Image
{
public:
	Image() = delete;
	Image(const ImageSpec& spec);
	~Image();

public:
	void writeToDisk(const std::string_view fp, bool fillAlpha = true, double fillValue = 1.0);


public:
	glm::vec4* m_data = nullptr;

private:
	ImageSpec m_specification;
};

#endif // !IMG_HPP
