#include"Sample.hlsli"

float4 main(VertexPosHColor input) : SV_TARGET
{ 
	
	//float4 texColor = g_Tex.Sample(g_SamLinear, input.Tex);
	return float4(input.color, 1.0f);
}
