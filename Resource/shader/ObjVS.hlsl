#include "Obj.hlsli"

VSOutput main( float4 pos : POSITION, float3 normal:NORMAL, float2 uv:TEXCOORD ){
	VSOutput output; //�s�N�Z���V�F�[�_�[�ɓn���l
	
	output.svpos = mul(mat, pos);
	output.normal = normal;
	output.uv = uv;

	return output;
}