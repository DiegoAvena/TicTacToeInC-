/*

Creator: Diego Avena
Last Updated: 9/17/21

*/

#version 330 core

out vec4 color;

in vec2 vTexCoord; 

uniform vec4 aCol;
uniform sampler2D tex;
uniform float lerpFactor; 
uniform bool winningPiece; 

void main() {

	vec4 texColor = texture(tex, vTexCoord);
	
	if (winningPiece) {

		texColor.rgb += vec3(0.0f, 0.5f, 0.0f);

	}

	color = mix(aCol, texColor, lerpFactor);

}