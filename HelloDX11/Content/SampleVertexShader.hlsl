#include"Sample.hlsli"


VertexPosHColor main(VertexPosColor input)
{
	VertexPosHColor output;
	float4 pos = float4(input.pos, 1.0f);

	// ������λ��ת��ΪͶӰ�ռ䡣
	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

	// �����޸ĵش�����ɫ��
	output.color = input.color;

	return output;
}
