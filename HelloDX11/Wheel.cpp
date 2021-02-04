#include "pch.h"
#include "Wheel.h"
using namespace HelloDX11;
using namespace DirectX;
void Wheel::OnUpdate(DX::StepTimer const& timer)
{
	float degreesPerSecond = 45;
	// 将度转换成弧度，然后将秒转换为旋转角度
	float radiansPerSecond = XMConvertToRadians(degreesPerSecond);
	double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
	float radians = static_cast<float>(fmod(totalRotation, XM_2PI));
	Rotate(radians);
	//if input w
	//wheel rotate x
	//if input a/d
	//wheel rotate y
}
Geometry::MeshData<geoVPC> Wheel::CreateMesh()
{
	return Geometry::CreateCylinder<geoVPC>(0.2f, 0.1f, 16, 8, 0, 0, { (1.0f),(0.5f),(0.5f),(1.0f) });
}
void Wheel::Rotate(float radians)
{
	XMMATRIX model = XMMatrixTranspose(XMMatrixRotationY(radians));
	model = XMMatrixTranspose(XMMatrixRotationZ(XM_PIDIV2)) * model;
	m_rotation= model;
}