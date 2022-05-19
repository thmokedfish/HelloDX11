#pragma once
#include "pch.h"
#include<map>
#include<vector>
#include<string>

namespace Geometry
{
    namespace Internal
    {
        //
        // ���½ṹ��ͺ��������ڲ�ʵ��ʹ��
        //

        struct VertexData
        {
            DirectX::XMFLOAT3 pos;
            DirectX::XMFLOAT3 normal;
            DirectX::XMFLOAT4 tangent;
            DirectX::XMFLOAT4 color;
            DirectX::XMFLOAT2 tex;
            //VertexData() :pos(),normal(),tangent(),color(),tex()
            //{}
        };

        // ����Ŀ�궥������ѡ���Խ����ݲ���
        template<class VertexType>
        inline void InsertVertexElement(VertexType& vertexDst, const VertexData& vertexSrc)
        {
            static std::string semanticName;
            // ��һ���������ڴ�ӳ���ϵ
            static const std::map<std::string, std::pair<size_t, size_t>> semanticSizeMap = {
                {"POSITION", std::pair<size_t, size_t>(0, 12)},
                {"NORMAL", std::pair<size_t, size_t>(12, 24)},
                {"TANGENT", std::pair<size_t, size_t>(24, 40)},
                {"COLOR", std::pair<size_t, size_t>(40, 56)},
                {"TEXCOORD", std::pair<size_t, size_t>(56, 64)}
            };

            // �ڶ���...
            for (size_t i = 0; i < ARRAYSIZE(VertexType::inputLayout); i++)
            {
                semanticName = VertexType::inputLayout[i].SemanticName;
                const auto& range =semanticSizeMap.at(semanticName);
                memcpy_s(reinterpret_cast<char*>(&vertexDst) + VertexType::inputLayout[i].AlignedByteOffset,
                    range.second - range.first,
                    reinterpret_cast<const char*>(&vertexSrc) + range.first,
                    range.second - range.first);
            }
        }
    }

    struct VertexPosNormalTex 
    {
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT3 normal;
        DirectX::XMFLOAT2 tex;
        static const D3D11_INPUT_ELEMENT_DESC inputLayout[3];

    };

    struct VertexPosColor
    {
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT4 color;
        static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
    };


    // ��������
    template<class VertexType = VertexPosNormalTex, class IndexType = UINT>
    struct MeshData
    {
        std::vector<VertexType> vertexVec;    // ��������
        std::vector<IndexType> indexVec;    // ��������

        MeshData()
        {
            // ������������ͺϷ���
            static_assert(sizeof(IndexType) == 2 || sizeof(IndexType) == 4, "The size of IndexType must be 2 bytes or 4 bytes!");
            static_assert(std::is_unsigned<IndexType>::value, "IndexType must be unsigned integer!");
        }
    };

    // ������������������
    template<class VertexType = VertexPosNormalTex, class IndexType = UINT>
    MeshData<VertexType, IndexType> CreateBox(float width = 2.0f, float height = 2.0f, float depth = 2.0f,
        const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

    // ����ֻ��Բ���������������ݣ�slicesԽ�󣬾���Խ��
    template<class VertexType = VertexPosNormalTex, class IndexType = UINT>
    MeshData<VertexType, IndexType> CreateCylinderNoCap(float radius = 1.0f, float height = 2.0f, UINT slices = 20, UINT stacks=10, float texU=0, float texV=0,
        const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });


    // ����Բ�����������ݣ�slicesԽ�󣬾���Խ�ߡ�
    template<class VertexType = VertexPosNormalTex, class IndexType = UINT>
    MeshData<VertexType, IndexType> CreateCylinder(float radius = 1.0f, float height = 2.0f, UINT slices = 20, UINT stacks=10, float texU=0, float texV=0,
        const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

    template<class VertexType, class IndexType>
    inline MeshData<VertexType, IndexType> CreateBox(float width, float height, float depth, const DirectX::XMFLOAT4& color)
    {
        using namespace DirectX;

        MeshData<VertexType, IndexType> meshData;
        meshData.vertexVec.resize(24);


        Internal::VertexData vertexDataArr[24];
        float w2 = width / 2, h2 = height / 2, d2 = depth / 2;

        // ����(+X��)
        vertexDataArr[0].pos = XMFLOAT3(w2, -h2, -d2);
        vertexDataArr[1].pos = XMFLOAT3(w2, h2, -d2);
        vertexDataArr[2].pos = XMFLOAT3(w2, h2, d2);
        vertexDataArr[3].pos = XMFLOAT3(w2, -h2, d2);
        // ����(-X��)
        vertexDataArr[4].pos = XMFLOAT3(-w2, -h2, d2);
        vertexDataArr[5].pos = XMFLOAT3(-w2, h2, d2);
        vertexDataArr[6].pos = XMFLOAT3(-w2, h2, -d2);
        vertexDataArr[7].pos = XMFLOAT3(-w2, -h2, -d2);
        // ����(+Y��)
        vertexDataArr[8].pos = XMFLOAT3(-w2, h2, -d2);
        vertexDataArr[9].pos = XMFLOAT3(-w2, h2, d2);
        vertexDataArr[10].pos = XMFLOAT3(w2, h2, d2);
        vertexDataArr[11].pos = XMFLOAT3(w2, h2, -d2);
        // ����(-Y��)
        vertexDataArr[12].pos = XMFLOAT3(w2, -h2, -d2);
        vertexDataArr[13].pos = XMFLOAT3(w2, -h2, d2);
        vertexDataArr[14].pos = XMFLOAT3(-w2, -h2, d2);
        vertexDataArr[15].pos = XMFLOAT3(-w2, -h2, -d2);
        // ����(+Z��)
        vertexDataArr[16].pos = XMFLOAT3(w2, -h2, d2);
        vertexDataArr[17].pos = XMFLOAT3(w2, h2, d2);
        vertexDataArr[18].pos = XMFLOAT3(-w2, h2, d2);
        vertexDataArr[19].pos = XMFLOAT3(-w2, -h2, d2);
        // ����(-Z��)
        vertexDataArr[20].pos = XMFLOAT3(-w2, -h2, -d2);
        vertexDataArr[21].pos = XMFLOAT3(-w2, h2, -d2);
        vertexDataArr[22].pos = XMFLOAT3(w2, h2, -d2);
        vertexDataArr[23].pos = XMFLOAT3(w2, -h2, -d2);

        for (UINT i = 0; i < 4; ++i)
        {
            // ����(+X��)
            vertexDataArr[i].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
            vertexDataArr[i].tangent = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
            vertexDataArr[i].color = color;
            // ����(-X��)
            vertexDataArr[i + 4].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);
            vertexDataArr[i + 4].tangent = XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f);
            vertexDataArr[i + 4].color = color;
            // ����(+Y��)
            vertexDataArr[i + 8].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
            vertexDataArr[i + 8].tangent = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
            vertexDataArr[i + 8].color = color;
            // ����(-Y��)
            vertexDataArr[i + 12].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
            vertexDataArr[i + 12].tangent = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
            vertexDataArr[i + 12].color = color;
            // ����(+Z��)
            vertexDataArr[i + 16].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
            vertexDataArr[i + 16].tangent = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
            vertexDataArr[i + 16].color = color;
            // ����(-Z��)
            vertexDataArr[i + 20].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
            vertexDataArr[i + 20].tangent = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
            vertexDataArr[i + 20].color = color;
        }

        for (UINT i = 0; i < 6; ++i)
        {
            vertexDataArr[i * 4].tex = XMFLOAT2(0.0f, 1.0f);
            vertexDataArr[i * 4 + 1].tex = XMFLOAT2(0.0f, 0.0f);
            vertexDataArr[i * 4 + 2].tex = XMFLOAT2(1.0f, 0.0f);
            vertexDataArr[i * 4 + 3].tex = XMFLOAT2(1.0f, 1.0f);
        }

        for (UINT i = 0; i < 24; ++i)
        {
            Internal::InsertVertexElement(meshData.vertexVec[i], vertexDataArr[i]);
        }

        meshData.indexVec = {
            0, 1, 2, 2, 3, 0,        // ����(+X��)
            4, 5, 6, 6, 7, 4,        // ����(-X��)
            8, 9, 10, 10, 11, 8,    // ����(+Y��)
            12, 13, 14, 14, 15, 12,    // ����(-Y��)
            16, 17, 18, 18, 19, 16, // ����(+Z��)
            20, 21, 22, 22, 23, 20    // ����(-Z��)
        };

        return meshData;
    }

    template<class VertexType, class IndexType>
    inline MeshData<VertexType, IndexType> CreateCylinderNoCap(float radius, float height, UINT slices,UINT stacks, float texU, float texV, const DirectX::XMFLOAT4& color)
    {
        using namespace DirectX;

        MeshData<VertexType, IndexType> meshData;
        UINT vertexCount = (slices + 1) * (stacks + 1);
        UINT indexCount = 6 * slices * stacks;
        meshData.vertexVec.resize(vertexCount);
        meshData.indexVec.resize(indexCount);

        float h2 = height / 2;
        float theta = 0.0f;
        float per_theta = XM_2PI / slices;
        float stackHeight = height / stacks;

        Internal::VertexData vertexData;

        // �Ե������������˵�
        UINT vIndex = 0;
        for (UINT i = 0; i < stacks + 1; ++i)
        {
            float y = -h2 + i * stackHeight;
            // ��ǰ�㶥��
            for (UINT j = 0; j <= slices; ++j)
            {
                theta = j * per_theta;
                float u = theta / XM_2PI;
                float v = 1.0f - (float)i / stacks;
                vertexData = { XMFLOAT3(radius * cosf(theta), y, radius * sinf(theta)), XMFLOAT3(cosf(theta), 0.0f, sinf(theta)),
                              XMFLOAT4(-sinf(theta), 0.0f, cosf(theta), 1.0f), color, XMFLOAT2(u * texU, v * texV) };
                Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);
            }
        }

        // ��������
        UINT iIndex = 0;
        for (UINT i = 0; i < stacks; ++i)
        {
            for (UINT j = 0; j < slices; ++j)
            {
                meshData.indexVec[iIndex++] = i * (slices + 1) + j;
                meshData.indexVec[iIndex++] = (i + 1) * (slices + 1) + j;
                meshData.indexVec[iIndex++] = (i + 1) * (slices + 1) + j + 1;

                meshData.indexVec[iIndex++] = i * (slices + 1) + j;
                meshData.indexVec[iIndex++] = (i + 1) * (slices + 1) + j + 1;
                meshData.indexVec[iIndex++] = i * (slices + 1) + j + 1;
            }
        }



        return meshData;
    }

    template<class VertexType, class IndexType>
    inline MeshData<VertexType, IndexType> CreateCylinder(float radius, float height, UINT slices, UINT stacks, float texU, float texV, const DirectX::XMFLOAT4& color)
    {
        using namespace DirectX;

        auto meshData = CreateCylinderNoCap<VertexType, IndexType>(radius, height, slices, stacks,texU,texV, color);
        UINT vertexCount = (slices + 1) * (stacks + 3) + 2;
        UINT indexCount = 6 * slices * (stacks + 1);
        meshData.vertexVec.resize(vertexCount);
        meshData.indexVec.resize(indexCount);

        float h2 = height / 2;
        float theta = 0.0f;
        float per_theta = XM_2PI / slices;

        IndexType vIndex = (slices + 1) * (stacks + 1), iIndex = 6 * slices * stacks;
        IndexType offset = vIndex;
        Internal::VertexData vertexData;

        // ���붥��Բ��
        vertexData = { XMFLOAT3(0.0f, h2, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f),
                      XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.5f, 0.5f) };
        Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

        // ���붥��Բ�ϸ���
        for (UINT i = 0; i <= slices; ++i)
        {
            theta = i * per_theta;
            float u = cosf(theta) * radius / height + 0.5f;
            float v = sinf(theta) * radius / height + 0.5f;
            vertexData = { XMFLOAT3(radius * cosf(theta), h2, radius * sinf(theta)), XMFLOAT3(0.0f, 1.0f, 0.0f),
                          XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(u, v) };
            Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);
        }

        // ����׶�Բ��
        vertexData = { XMFLOAT3(0.0f, -h2, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f),
                      XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.5f, 0.5f) };
        Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

        // ����ײ�Բ�ϸ���
        for (UINT i = 0; i <= slices; ++i)
        {
            theta = i * per_theta;
            float u = cosf(theta) * radius / height + 0.5f;
            float v = sinf(theta) * radius / height + 0.5f;
            vertexData = { XMFLOAT3(radius * cosf(theta), -h2, radius * sinf(theta)), XMFLOAT3(0.0f, -1.0f, 0.0f),
                          XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(u, v) };
            Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);
        }



        // ���붥������������
        for (UINT i = 1; i <= slices; ++i)
        {
            meshData.indexVec[iIndex++] = offset;
            meshData.indexVec[iIndex++] = offset + i % (slices + 1) + 1;
            meshData.indexVec[iIndex++] = offset + i;
        }

        // ����ײ�����������
        offset += slices + 2;
        for (UINT i = 1; i <= slices; ++i)
        {
            meshData.indexVec[iIndex++] = offset;
            meshData.indexVec[iIndex++] = offset + i;
            meshData.indexVec[iIndex++] = offset + i % (slices + 1) + 1;
        }

        return meshData;
    }

}
