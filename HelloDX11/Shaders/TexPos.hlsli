
Texture2D g_Tex:register(t0);
SamplerState g_SamLinear : register(s0);
cbuffer ViewProjectionConstantBuffer : register(b0)
{
	//matrix model;
	matrix view;
	matrix projection;
};
cbuffer ModelConstantBuffer:register(b1)
{
	matrix model;
}
struct VertexPosTex
{
	float3 pos:POSITION;
	float2 uv:TEXCOORD;
};
struct VertexPosHTex
{
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD;
};