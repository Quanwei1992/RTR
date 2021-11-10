//--------------------------------------------------------------------------------------
// File: EffectParam.fx
//
// The effect file for the EffectParam sample.  
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
matrix g_mvp;


struct VS_INPUT
{
    vector position:POSITION;
    float4 color:COLOR0;  
};

struct VS_OUTPUT
{
    vector position:POSITION;
    float4 color:COLOR0;
};

VS_OUTPUT VS_Main(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.position = mul(input.position,g_mvp);
    output.color = input.color;
    return output;
}

struct PS_INPUT
{
    float4 color:COLOR0;
};
struct PS_OUTPUT
{
    float4 color:COLOR0;
};

PS_OUTPUT PS_Main(PS_INPUT input)
{

    PS_OUTPUT output = (PS_OUTPUT)0;
    output.color = input.color;
    return output;
}


//--------------------------------------------------------------------------------------
// Techniques
//--------------------------------------------------------------------------------------
technique Default
{
    pass P0
    {
        VertexShader = compile vs_2_0 VS_Main();
        PixelShader  = compile ps_2_0 PS_Main();
    }
}
