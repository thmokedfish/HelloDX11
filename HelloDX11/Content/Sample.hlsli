
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
struct VertexPosColor
{
	float3 pos : POSITION;
	float3 color : COLOR0;
};
struct VertexPosHColor
{
	float4 pos:SV_POSITION;
	float3 color : COLOR0;
};
