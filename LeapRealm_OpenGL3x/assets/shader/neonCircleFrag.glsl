#version 150

out vec4 fragColor;

uniform vec2 center;
uniform float radius;
uniform vec4 color;
uniform float lineWidth;

void main()
{
	float d0 = length(center - gl_FragCoord.xy);
	float d1 = abs(d0 - radius);
	float a = pow(1. - d1 / (lineWidth / 2.), 2);
	fragColor = color * a * clamp(lineWidth / 2. - d1, 0., 1.);
}
