#include "pch.h"
#include "Ground.h"
using namespace HelloDX11;
using namespace DirectX;
using namespace Geometry;

void Ground::OnCreateResource()
{
    float width = 5; float height = 0.1f; float depth = 5;
    XMFLOAT4 white = { 1.0f, 1.0f, 1.0f, 1.0f };
    XMFLOAT4 blue = { 0.5f,0.5f,1.0f,1.0f };
    XMFLOAT4 red = { 1,0.5f,0.5f,1.0f };
    XMFLOAT4 black = { 0,0,0,1 };
    MeshData<VertexPosColor, DWORD> meshData;
    meshData.vertexVec.resize(4);

    float w2 = width / 2, h2 = height / 2, d2 = depth / 2;
    meshData.vertexVec[0].pos = XMFLOAT3(-w2, h2, -d2);
    meshData.vertexVec[1].pos = XMFLOAT3(-w2, h2, d2);
    meshData.vertexVec[2].pos = XMFLOAT3(w2, h2, d2);
    meshData.vertexVec[3].pos = XMFLOAT3(w2, h2, -d2);

    meshData.vertexVec[0].color = red;
    meshData.vertexVec[1].color = black;
    meshData.vertexVec[2].color = blue;
    meshData.vertexVec[3].color = white ;

    meshData.indexVec = {
        0, 1, 2, 2, 3, 0,       
    };

    CreateResourceWithVertexData(meshData);
}

void Ground::OnUpdate()
{
}