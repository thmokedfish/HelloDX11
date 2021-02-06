#include"Sample.hlsli"


VertexPosHColor main(VertexPosColor input)
{
	VertexPosHColor output;
	float4 pos = float4(input.pos, 1.0f);

	// 将顶点位置转换为投影空间。
	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

	// 不加修改地传递颜色。
	output.color = input.color;

	return output;
}
