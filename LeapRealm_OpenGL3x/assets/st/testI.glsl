#if 0
	uniform vec3      iResolution;				
	uniform float     iTime;					
	uniform float     iTimeDelta;				
	uniform int       iFrame;              		
	uniform float     iChannelTime[4];			
	uniform vec3      iChannelResolution[4];	
	uniform vec4      iMouse;					
	uniform sampler2D iChannel0;        		
	uniform sampler2D iChannel1;        		
	uniform sampler2D iChannel2;        		
	uniform sampler2D iChannel3;        		
	uniform vec4      iDate;					
	uniform float     iSampleRate;				
#endif

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
	float d = length(iMouse.xy - fragCoord.xy);
	fragColor = vec4(clamp(100. - d, 0., 1.));
}
