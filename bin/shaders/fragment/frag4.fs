#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	vec4 textureColour = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);

    vec4 result = vec4(ambient,1.0) * textureColour;

    FragColor = result;

}