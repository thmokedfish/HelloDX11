#include"TexPos.hlsli"

float4 main(VertexPosHTex input) : SV_TARGET
{ 

	float4 texColor = g_Tex.Sample(g_SamLinear, input.uv);
	return texColor;
}
