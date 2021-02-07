#include"TexPos.hlsli"


VertexPosHTex main(VertexPosTex input)
{
	VertexPosHTex output;
	float4 pos = float4(input.pos, 1.0f);

	// ������λ��ת��ΪͶӰ�ռ䡣
	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

	// �����޸ĵش�����ɫ��
	output.uv= input.uv;

	return output;
}
