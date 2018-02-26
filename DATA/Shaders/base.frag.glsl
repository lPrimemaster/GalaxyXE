#version 450 core

//DEFINES
#define GXE_DIRECTIONAL_LIGHT 0x0F0
#define GXE_SPOT_LIGHT 0x0F1
#define GXE_POINT_LIGHT 0x0F2

// CONST VARS
const int MAX_LIGHTS = 1;
const float shininess = 20;
const float strength = 1;

const vec2 poissonDisk[4] = vec2[](
  vec2( -0.94201624, -0.39906216 ),
  vec2( 0.94558609, -0.76890725 ),
  vec2( -0.094184101, -0.92938870 ),
  vec2( 0.34495938, 0.29387760 )
);

// IN VARS
in vec2 fuvs;
in vec3 surfaceNormal;
in vec4 worldPosition;
in vec4 shadowCoord;

// OUT VARS
out vec4 fColor;

struct LightProperties
{
	vec3 position;
	vec3 direction;
	vec3 color;
	vec3 ambient;

	vec3 coneDirection;
	
	bool isEnabled;
	uint lightType;
	
	float spotCosCutoff;
	float spotExponent;

	float constAtt;
	float linearAtt;
	float quadAtt;
};

uniform LightProperties light[MAX_LIGHTS];

// UNIFORM DECLARATION
uniform sampler2D sampler;
uniform sampler2D shadow;
uniform vec3 EyeDirection;

//FUNCTION DEFINITION

float calculateShadows(sampler2D shadowMap)
{
	vec3 coords = shadowCoord.xyz / shadowCoord.w;
	float visibility = 1.0;
	
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	
	for (int i=0; i < 4; i++)
	{
		if ( texture( shadowMap, coords.xy + poissonDisk[i]/700.0 ).r  <  coords.z )
		{
			visibility-=0.2;
		}
	}
	
	if(coords.z > 1.0)
		visibility = 0.0;
	
	return visibility;
}

vec4 calculateLights(vec4 inColor)
{
	vec3 scatteredLight = vec3(0.0);
	vec3 reflectedLight = vec3(0.0);
	
	vec3 lightDir;
	float attenuation;
	
	for(int i = 0; i < MAX_LIGHTS; i++)
	{
		if(!light[i].isEnabled)
		{
			continue;
		}
		else if(light[i].lightType == GXE_DIRECTIONAL_LIGHT) //Directional light setup
		{
			attenuation = 1.0; 
			lightDir = light[i].direction;
			lightDir = normalize(lightDir);
		}
		else if(light[i].lightType != GXE_DIRECTIONAL_LIGHT)
		{
			lightDir = light[i].position - vec3(worldPosition);
			float dist = length(lightDir);
			lightDir = lightDir / dist;
			attenuation = 1.0 / (light[i].constAtt + light[i].linearAtt * dist + light[i].quadAtt * dist * dist);
			
			if(light[i].lightType == GXE_SPOT_LIGHT)
			{
				float spotCos = dot(lightDir, -light[i].coneDirection);
				if(spotCos < light[i].spotCosCutoff)
					attenuation = 0.0;
				else
					attenuation *= pow(spotCos, light[i].spotExponent);
			}
		}
		
		float diffuse = max(0.0, dot(surfaceNormal, lightDir));
		vec3 rVector = reflect(lightDir, surfaceNormal);
		float specular = max(0.0, dot(rVector, -EyeDirection));
		
		if(diffuse == 0.0)
			specular = 0.0;
		else
			specular = pow(specular, shininess) * strength;
		scatteredLight += light[i].ambient * 0.1 * attenuation + diffuse * light[i].color * attenuation * calculateShadows(shadow);
		reflectedLight += light[i].color * specular * attenuation * calculateShadows(shadow);
		
		vec3 rgb = min(inColor.rgb * scatteredLight + reflectedLight, vec3(1.0));
		return vec4(rgb, inColor.a);		
	}
}

void main()
{
	//vec4 color = texture(sampler, fuvs);
	vec4 color = vec4(0.0, 0.0, 1.0, 1.0);
	fColor = calculateLights(color);
}
