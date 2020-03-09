#version 330 core
#define MAX_LIGHTS 6
uniform int numLights;

uniform struct Light{
 vec3 position;
 vec3 ambient;
 vec3 diffuse;
 vec3 specular;
 float coneAngle;
 vec3 coneDirection;
} lights[MAX_LIGHTS];

struct DirLight{
 vec3 direction;
 vec3 ambient;
 vec3 diffuse;
 vec3 specular;
};

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct Material{
 vec3 ambient;
 vec3 diffuse;
 vec3 specular;
 float shininess;
};

in vec4 positionOut;

in vec3 colourOut;
out vec4 pixelColour;
uniform vec3 mixColour;
uniform float mixValue;

in vec2 textureUV; //UV 1
in vec2 textureUV2; //UV 2
uniform sampler2D textureImage; //Texture 1
uniform sampler2D otherTexture; //Texture 2

uniform bool isLit;
uniform vec3 lightColour;
vec3 lightDirection;
float lightIntensity;

uniform vec3 cameraPosition;
vec3 viewDirection;

in vec3 normalOut;
uniform mat3 normalMatrix;

uniform bool isWater;

uniform Light light;

uniform Material material;


vec4 calcLight(Light light){
	
		vec3 normal = vec3(0.0, 1.0, 0.0);
		//vec3 normal = normalize(normalMatrix * normalOut);

		//Ambient light
		vec3 ambientColor = light.ambient * material.ambient;

		
		lightDirection = normalize(light.position - vec3(positionOut));
		lightIntensity = max(dot(lightDirection, normal), 0.0);

		vec3 diffuseColor = light.diffuse * material.diffuse * lightIntensity;



		//Specular lighting
		viewDirection = normalize(cameraPosition - vec3(positionOut));
		//lightDirection = normalize(vec3(positionOut) - light.position);
		vec3 reflection = reflect(-lightDirection, normal); //Reflection vector
		float specularAmount = pow(max(dot(viewDirection, reflection), 0.0), material.shininess);
		
		vec3 finalSpecular = light.specular * material.specular * specularAmount;




		float dist = distance(light.position, vec3(positionOut));
		//float attenuation = 1.0 / (1.0 + 0.1 * dist + 0.01 * dist * dist);

		float radius = sqrt(1.0 / (0.01 * 0.01));
		float attenuation = clamp(1.0 - dist*dist/(radius*radius), 0.0, 1.0); //attenuation *= attenuation;


		//float lightToSurfaceAngle = radians(acos(dot(lightDirection, normalize(light.coneDirection))));
		//
		//if(lightToSurfaceAngle > light.coneAngle){
		//	attenuation = 0.0;
		//}



		vec3 coneDirection = normalize(light.coneDirection);

		float lightToSurfaceAngle = degrees(acos(dot(-lightDirection, coneDirection)));

		if(lightToSurfaceAngle > light.coneAngle){
			attenuation = 0;
		}

		if (isWater){
			return vec4((ambientColor + diffuseColor + finalSpecular), 1.0) * attenuation * mix(texture(textureImage, textureUV.st), texture(otherTexture, textureUV2.st), 0.5);
		}else{
			return vec4((ambientColor + diffuseColor + finalSpecular), 1.0) * attenuation * texture(textureImage, textureUV.st);
		}
}


void main(void){

	//Mix with multiple textures
	//pixelColour = vec4(colourOut, 1.0);// * mix(texture(textureImage, textureUV.st), texture(otherTexture, textureUV2.st), mixValue);

		

	if (isLit){
		
		vec4 finalColour = vec4(0);
		for (int i = 0; i < numLights; i++){
			finalColour += calcLight(lights[i]);
		}
		pixelColour = finalColour;
	}
	else{
	
		pixelColour = vec4(colourOut, 1.0);


		//Render without lighting calculations
		//pixelColour = vec4(colourOut, 1.0) * mix(texture(textureImage, textureUV.st), texture(otherTexture, textureUV2.st), mixValue);
	}
}