// Vertex Shader with HLSL

float4 VSMain(float3 inPos : POSITION) : POSITION
{
    return float4(inPos,1);
}