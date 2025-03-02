#include <numbers>
#include <cmath>
#include <Windows.h>

#include "../../ext/SimpleMath.h"


using namespace DirectX::SimpleMath;

class Vec2 {
public:
    constexpr Vec2(
        const float x = 0.f,
        const float y = 0.f,
        const float z = 0.f) noexcept :
        x(x), y(y) {
    }

    float x, y;
};


class Vec3
{
public:
    // Constructor with default values for x, y, z
    constexpr Vec3(
        const float x = 0.f,
        const float y = 0.f,
        const float z = 0.f) noexcept :
        x(x), y(y), z(z) {
    }

    // Overload for addition (operator+)
    constexpr Vec3 operator+(const Vec3& other) const noexcept
    {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    // Overload for subtraction (operator-)
    constexpr Vec3 operator-(const Vec3& other) const noexcept
    {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    // Overload for multiplication with a scalar (operator*)
    constexpr Vec3 operator*(const float factor) const noexcept
    {
        return Vec3(x * factor, y * factor, z * factor);
    }

    // Overload for division by a scalar (operator/)
    constexpr Vec3 operator/(const float factor) const noexcept
    {
        return Vec3(x / factor, y / factor, z / factor);
    }

    // Function to check if the vector is a zero vector
    constexpr bool IsZero() const noexcept
    {
        return x == 0.f && y == 0.f && z == 0.f;
    }

    // World to screen transformation (example placeholder, actual implementation may vary)
    const bool world_to_screen(const DirectX::SimpleMath::Matrix& view_matrix, Vec2& out);

    // Member variables for the vector components
    float x, y, z;
};

