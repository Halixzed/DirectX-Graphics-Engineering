cbuffer ConstantBuffer
{
    matrix worldViewProjection;
    matrix world;
    float4 materialColour;
    float4 ambientLightColour;
    float4 DirectionalLightColour;
    float4 DirectionalLightVector;
    float4 specColour;

    float SpecularPower;
    float3 pad;
};


struct VertexIn
{
    float3 InputPosition : POSITION;
    float3 Normal : NORMAL;
};

struct VertexOut
{
    float4 OutputPosition : SV_POSITION;
    float4 Colour : COLOR;
    float3 Normal : TEXCOORD0;
    float3 WorldPosition : TEXCOORD1;
};

// Add these lines to the existing Vertex Shader
VertexOut VS(VertexIn vin)
{
    VertexOut vout;

    // Transform to homogeneous clip space.
    vout.OutputPosition = mul(worldViewProjection, float4(vin.InputPosition, 1.0f));

    // Transform normal to world space as float3 using the world matrix
    vout.Normal = mul((float3x3) world, vin.Normal);
    vout.WorldPosition = mul(world, float4(vin.InputPosition, 1.0f)).xyz;

    // Multiply by the material colour
    vout.Colour = saturate(materialColour);
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    //return pin.Colour;
    float3 eyePosition = float3(20.0f, 20.0f, -90.0f); //more control
    float3 toEye = normalize(eyePosition - pin.WorldPosition);

    float3 worldNormal = normalize(pin.Normal);
    float diffuseFactor = max(dot(worldNormal, -normalize(DirectionalLightVector.xyz)), 0.0);
    diffuseFactor = saturate(diffuseFactor);

    float3 lightDir = normalize(DirectionalLightVector.xyz);
    float3 reflected = reflect(-toEye, worldNormal);
    float specularFactor = pow(saturate(dot(reflected, toEye)), SpecularPower);

    // Incorporate specColour into the final color calculation
    float4 totalLight = saturate(ambientLightColour + diffuseFactor * DirectionalLightColour + specularFactor * specColour);

    float4 finalColor = saturate(totalLight * materialColour);

    return finalColor * pin.Colour; 
}