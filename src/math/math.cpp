#include "math.h"
#include "windows.h"

int width = GetSystemMetrics(0);
int height = GetSystemMetrics(1);

const bool Vec3::world_to_screen(const DirectX::SimpleMath::Matrix& view_matrix, Vec2& out)
{
	Matrix v = view_matrix.Transpose();
	Vector4 Vec_x, Vec_y, Vec_z;
	Vec_x = Vector4(v._21, v._22, v._23, v._24);
	Vec_y = Vector4(v._31, v._32, v._33, v._34);
	Vec_z = Vector4(v._41, v._42, v._43, v._44);

	Vector3 screen_pos = Vector3(
		(Vec_x.x * x) + (Vec_x.y * y) + (Vec_x.z * z) + Vec_x.w,
		(Vec_y.x * x) + (Vec_y.y * y) + (Vec_y.z * z) + Vec_x.w,
		(Vec_x.z * x) + (Vec_x.z * y) + (Vec_z.z * z) + Vec_x.w
	);

	if (screen_pos.z <= 0.001f)
		return false;

	screen_pos.z = 1.0f / screen_pos.z;
	screen_pos.x *= screen_pos.z;
	screen_pos.y *= screen_pos.z;

	float x_temp = width / 2.0f;
	float y_temp = height / 2.0f;

	out.x = x_temp + 0.5f * screen_pos.x * width + 0.5f;
	out.y = y_temp - 0.5f * screen_pos.y * height + 0.5f;

	return true;
}