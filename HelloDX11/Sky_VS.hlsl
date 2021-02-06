TextureCube g_TexCube : register(t0);
SamplerState g_Sam : register(s0);

cbuffer CBChangesEveryFrame : register(b0)
{
    matrix g_WorldViewProj;
}

struct VertexPos
{
    float3 PosL : POSITION;
};

struct VertexPosHL
{
    float4 PosH : SV_POSITION;
    float3 PosL : POSITION;
};

VertexPosHL VS(VertexPos vIn)
{
    VertexPosHL vOut;

    // 设置z = w使得z/w = 1(天空盒保持在远平面)
    float4 posH = mul(float4(vIn.PosL, 1.0f), g_WorldViewProj);
    vOut.PosH = posH.xyww;
    vOut.PosL = vIn.PosL;
    return vOut;
}