#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <sstream>
#include <cmath>

template<typename T>
class float3
{
public:

	// Initializers / Destructors
	float3<T>() : e{ 0,0,0 } {}

	float3<T>(const T& _x, const T& _y, const T& _z) noexcept : e{_x, _y, _z} {}

	float3<T>(const T& xyz) : float3<T>(xyz, xyz, xyz) {}
	float3<T>(const float3<T>& vec) : float3<T>(vec.e[0], vec.e[1], vec.e[2]) {}
	float3<T>(const float3<T>&& vec) : float3<T>(vec.e[0], vec.e[1], vec.e[2]) {}

	~float3<T>() = default;

	// Accessors
	inline float3<T> operator=(const float3<T>& other)
	{
		e[0] = other.e[0];
		e[1] = other.e[1];
		e[2] = other.e[2];
	}

	T operator[](const size_t &i) const { return e[i]; }
	T& operator[](const size_t &i) { return e[i]; }

	// Math Operators
	float3<T>& operator+=(const float3<T>& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	float3<T>& operator-=(const float3<T>& v) {
		e[0] -= v.e[0];
		e[1] -= v.e[1];
		e[2] -= v.e[2];
		return *this;
	}

	float3<T>& operator*=(T t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}
	float3<T>& operator/=(T t) {
		return *this *= 1 / t;
	}


	inline float3<T> operator+(const float3<T>& v) {
		return float3<T>(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
	}
	inline float3<T> operator+(const T t) {
		return float3<T>(e[0] + t, e[1] + t, e[2] + t);
	}

	float3<T> operator-() const { return float3<T>(-e[0], -e[1], -e[2]); }
	inline float3<T> operator-(const float3<T>& v) {
		return float3<T>(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
	}
	inline float3<T> operator-(const T t) {
		return float3<T>(e[0] - t, e[1] - t, e[2] - t);
	}

	inline float3<T> operator*(const float3<T>& v) {
		return float3<T>(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]);
	}
	inline float3<T> operator*(const T t) {
		return float3<T>(t * e[0], t * e[1], t * e[2]);
	}

	inline float3<T> operator/(const float3<T>& v) {
		return float3<T>(e[0] * 1/v.e[0], e[1] * 1/v.e[1], e[2] * 1/v.e[2]);
	}
	inline float3<T> operator/(const T t) {
		return float3<T>(e[0] * 1/t, e[1] * 1/t, e[2] * 1/t);
	}

	float length() const {
		return std::sqrtf(length_squared());
	}
	T length_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	// Debug Utility
	operator std::string() const
	{
		std::stringstream ss;
		ss << +e[0] << ' ' << +e[1] << ' ' << +e[2];
		return ss.str();
	}

	friend std::ostream& operator<<(std::ostream& out, const float3<T>& v)
	{
		return out << +v.x << ' ' << +v.y << ' ' << +v.z;
	}

	struct {
		union {
			T x, y, z;
		};
		union {
			T r, g, b;
		};
		T e[3] = { 0,0,0 };
	};
};

using vec3f = float3<float>;
using vec3 = float3<double>;

using vec3i8 = float3<int8_t>;
using vec3i16 = float3<int16_t>;
using vec3i32 = float3<int32_t>;
using vec3i64 = float3<int64_t>;

using vec3u8 = float3<uint8_t>;
using vec3u16 = float3<uint16_t>;
using vec3u32 = float3<uint32_t>;
using vec3u64 = float3<uint64_t>;


template<typename T>
inline T dot(const float3<T>& a, const float3<T>& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

template<typename T>
inline float3<T> cross(const float3<T>& u, const float3<T>& v)
{
	return float3<T>
	(
		(u.y * v.z) - (u.z * v.y),
		(u.z * v.x) - (u.x * v.z),
		(u.x * v.y) - (u.y * v.x)
	);
}

template<typename T>
inline float3<T> normalize(float3<T>& a)
{
	return a / a.length();
}


#endif //! float3<T>_H