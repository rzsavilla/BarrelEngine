#version 430

//Light intensity
uniform vec3 La;			//Ambient intensity
uniform vec3 Ld;            //Diffuse light intensity
uniform vec3 Ls;			//Specular intensity
uniform vec3 lightPosition;	//Light Position
uniform float lightRadius;	//Radius of the light

//Material
uniform vec3 Ka;			//Ambient reflectivity
uniform vec3 Kd;            //Diffuse reflectivity
uniform vec3 Ks;			//Specular reflectivity
uniform float shininess;	//Specular highlight

//Camera/View
uniform vec3 viewPos;		//Camera position

//Fragment
in vec3 fragVert;			//Vertex position in eye space
in vec3 fragNormal;			//Normal position in eye space

//Colour
uniform vec3 myColour;		//Vertex Colour

out vec4 Colour;			//Returns fragment - Data used to render pixel

void main() {
	//////Ambient//////
	vec3 ambient = La * Ka;

	//////Diffuse//////
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(lightPosition - fragVert);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = Ld * Kd * diff;
	diffuse = clamp(diffuse,0.0,1.0);

	//////Specular//////
	vec3 viewDir = normalize(viewPos - fragVert);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specular =  Ls * Ks * spec;

	//////Light Attenuation//////
	if (lightRadius > 0) {
		//Gradual loss of light intensity over distance
		float att = smoothstep(lightRadius, 0, length(lightPosition - fragVert));

		//Apply attenuation
		ambient *= att;
		diffuse *= att;
		specular *= att;
	}

	//Calculate fragment colour
	Colour = vec4(ambient + diffuse + specular,1.0) * vec4(myColour,1.0);
}