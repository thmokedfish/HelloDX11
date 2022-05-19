#include "pch.h"
#include<vector>
#include<algorithm>
#include "Sample3DSceneRenderer.h"
#include "Car.h"
#include "Geometry.h"
#include"Ground.h"
#include"Skybox.h"
#include "Terrain/TerrainObject.h"
#include"consts/consts.h"

using namespace HelloDX11;
using namespace DirectX;
using namespace Windows::Foundation;

// 从文件中加载顶点和像素着色器，然后实例化立方体几何图形。
Sample3DSceneRenderer::Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_loadingComplete(false),
	m_degreesPerSecond(45),
	m_indexCount(0),
	m_tracking(false),
	m_deviceResources(deviceResources)
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
	//InputManager::GetInstance().Subscribe(xxx)
}

// 当窗口的大小改变时初始化视图参数。
void Sample3DSceneRenderer::CreateWindowSizeDependentResources()
{
	Size outputSize = m_deviceResources->GetOutputSize();
	float aspectRatio = outputSize.Width / outputSize.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	// 这是一个简单的更改示例，当应用程序在纵向视图或对齐视图中时，可以进行此更改
	if (aspectRatio < 1.0f)
	{
		fovAngleY *= 2.0f;
	}

	// 请注意，OrientationTransform3D 矩阵在此处是后乘的，
	// 以正确确定场景的方向，使之与显示方向匹配。
	// 对于交换链的目标位图进行的任何绘制调用
	// 交换链呈现目标。对于到其他目标的绘制调用，
	// 不应应用此转换。

	// 此示例使用行主序矩阵利用右手坐标系。
	XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovRH(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
		);
	XMFLOAT4X4 orientation = m_deviceResources->GetOrientationTransform3D();

	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);

	XMStoreFloat4x4(
		&m_constantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);
}
void Sample3DSceneRenderer::Update(DX::StepTimer const& timer)
{
	if (!m_loadingComplete)
	{
		return;
	}
	RenderObject::m_timer = &timer;
	root->Update();
	camera.OnUpdate(); 
	// view martix form camera
	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(camera.LookAt()));
}


void Sample3DSceneRenderer::Render()
{
	if (!m_loadingComplete)
	{
		return;
	}
	auto context = m_deviceResources->GetD3DDeviceContext();


	context->UpdateSubresource1(
		m_constantBuffer.Get(),
		0,
		NULL,
		&m_constantBufferData,
		0,
		0,
		0
		);
	
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	context->IASetInputLayout(m_inputLayout.Get());

	context->VSSetShader(
		m_vertexShader.Get(),
		nullptr,
		0
		);

	context->VSSetConstantBuffers1(
		0,
		1,
		m_constantBuffer.GetAddressOf(),
		nullptr,
		nullptr
		);

	context->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
		);

	root->Render( DirectX::XMMatrixIdentity());
	//skyRenderer.Render(context);
}

void Sample3DSceneRenderer::CreateDeviceDependentResources()
{
	typedef Geometry::VertexPosColor geoVPC;
	// 通过异步方式加载着色器。
	auto loadVSTask = DX::ReadDataAsync(L"SampleVertexShader.cso");
	auto loadPSTask = DX::ReadDataAsync(L"SamplePixelShader.cso");

	// 加载顶点着色器文件之后，创建着色器和输入布局。
	auto createVSTask = loadVSTask.then([this](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateVertexShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&m_vertexShader
				)
			);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateInputLayout(
				geoVPC::inputLayout,
				ARRAYSIZE(geoVPC::inputLayout),
				&fileData[0],
				fileData.size(),
				&m_inputLayout
				)
			);
	});

	// 加载像素着色器文件后，创建着色器和常量缓冲区。
	auto createPSTask = loadPSTask.then([this](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreatePixelShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&m_pixelShader
				)
			);

		CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer) , D3D11_BIND_CONSTANT_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
				&constantBufferDesc,
				nullptr,
				&m_constantBuffer
				)
			);
	});

	auto createResourcesTask = (createPSTask && createVSTask).then([this] () {
		InitObjects();
		//skyRenderer.Init(device);
	});

	createResourcesTask.then([this] () {
		m_loadingComplete = true;
	});
}

void Sample3DSceneRenderer::InitObjects()
{
	root = std::make_shared<TerrainObject>();
	root->GetTransform()->setPosition(XMVectorSet(-200.0f, -50.0f, -200.0f, 1));
	//root = std::make_shared<Ground>();
	//root->GetTransform()->setPosition(XMVectorSet(0, -100.0f, 0, 1));
	std::shared_ptr<RenderObject> car = std::make_shared<Car>();
	car->GetTransform()->setPosition(XMVectorSet(0, 0.18f, 0, 1));
	std::shared_ptr<RenderObject> sky = std::make_shared<Skybox>();
	Skybox* p = (Skybox*)sky.get();
	p->SetFollow(&camera);
	root->addChild(car);
	root->addChild(sky);
	camera.SetFollow(car.get());
	root->CreateResources(m_deviceResources);

}

void Sample3DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
	root->ReleaseDeviceDependentResources();
	m_vertexShader.Reset();
	m_pixelShader.Reset();
	m_constantBuffer.Reset();
	m_indexBuffer.Reset();
}