cbuffer ConstantBuffer
{
    matrix worldViewProjection;
    matrix world;
    float4 materialColour;
    float4 ambientLightColour;
    float4 DirectionalLightColour;
    float4 DirectionalLightVector;
    float4 specColour;

    float SpecularPower; // Add specular power

    // Padding to ensure the buffer size is a multiple of 16 bytes
    float3 pad;
};

Texture2D Texture;
SamplerState ss;

struct VertexIn
{
    float3 InputPosition : POSITION;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
};

struct VertexOut
{
    float4 OutputPosition : SV_POSITION;
    float3 Normal : TEXCOORD0;
    float3 WorldPosition : TEXCOORD1;
    float2 TexCoord : TEXCOORD2;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;

    // Transform to homogeneous clip space.
    vout.OutputPosition = mul(worldViewProjection, float4(vin.InputPosition, 1.0f));

    // Populate the normal and world position for interpolation
    vout.Normal = mul((float3x3) world, vin.Normal);
    vout.WorldPosition = mul(world, float4(vin.InputPosition, 1.0f)).xyz;

    // Pass texture coordinates
    vout.TexCoord = vin.TexCoord;

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    float3 eyePosition = float3(20.0f, 20.0f, -90.0f); //more control
    float3 toEye = normalize(eyePosition - pin.WorldPosition);

    float3 worldNormal = normalize(pin.Normal);
    float diffuseFactor = max(dot(worldNormal, -normalize(DirectionalLightVector.xyz)), 0.0);
    diffuseFactor = saturate(diffuseFactor);

    float3 lightDir = normalize(DirectionalLightVector.xyz);
    float3 reflected = reflect(-toEye, worldNormal);
    float specularFactor = pow(saturate(dot(reflected, toEye)), SpecularPower);

    // Incorporate specColour into the final color calculation
    float4 totalLight = saturate(ambientLightColour + (diffuseFactor * DirectionalLightColour) + (specularFactor * specColour));

    float4 finalColor = saturate(totalLight * materialColour);

    return finalColor * Texture.Sample(ss, pin.TexCoord);
    
    
    //return float4(abs(normalize(pin.Normal)), 1.0); //for debugging

}
