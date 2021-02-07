#include"Sample.hlsli"

float4 main(VertexPosHColor input) : SV_TARGET
{ 
	
	return float4(input.color, 1.0f);
}
