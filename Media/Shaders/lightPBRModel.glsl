// GGX
float DistributionBRDF(float roughness, float NxH)
{

    float m = roughness * roughness;
    float m2 = m * m;
    float d = ( NxH * m2 - NxH ) * NxH + 1;
    return m2 / ( d*d );
}

// Schlick
float GeometricBRDF(float roughness, float NxV, float NxL)
{   
    float a = roughness * roughness;
    float a2 = a * a;

    float v = NxV + sqrt( NxV * (NxV - NxV * a2) + a2 );
    float l = NxL + sqrt( NxL * (NxL - NxL * a2) + a2 );
    return clamp(1.0 / ( v * l ), 0.0, 1.0);
}

// Schlick
vec3 FresnelBRDF(vec3 specularColor, float LxH)
{
    return specularColor + (1.0 - specularColor) * pow(1.0 - LxH, 5.0); 
}

vec3 DiffuseBRDF(vec3 diffuseColor, float roughness, float NxV, float NxL, float VxH) 
{
    float VxL = 2 * VxH - 1;
    float m = roughness * roughness;
    float m2 = m * m;
    float C1 = 1 - 0.5 * m2 / (m2 + 0.33);
    float Cosri = VxL - NxV * NxL;
    float C2 = 0.45 * m2 / (m2 + 0.09) * Cosri * ( Cosri >= 0 ? min( 1, NxL / NxV ) : NxL );
    return diffuseColor / M_PI * ( NxL * C1 + C2 );
}

float safeDot(vec3 a, vec3 b) 
{
    return max(0.0, dot(a, b));
}

vec3 genericMicrofacetBRDF(vec3 f, float g, float d, float NxL, float NxV) 
{
    return (f * g * d) * max(0.0, 4.0 * NxL * NxV);
}

// Smith term for GGX
// [Smith 1967, "Geometrical shadowing of a random rough surface"]
float Vis_Smith( float Roughness, float NoV, float NoL )
{
    float a = Roughness * Roughness;
    float a2 = a*a;

    float Vis_SmithV = NoV + sqrt( NoV * (NoV - NoV * a2) + a2 );
    float Vis_SmithL = NoL + sqrt( NoL * (NoL - NoL * a2) + a2 );
    return 1.0 / ( Vis_SmithV * Vis_SmithL );
}