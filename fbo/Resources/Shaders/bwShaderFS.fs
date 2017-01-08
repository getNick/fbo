precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_texture_0;


void main()
{
	vec3 color =  texture2D(u_texture_0, v_uv).rgb;
	float avg = 0.3*color.r + 0.59*color.g + 0.11*color.b;
	gl_FragColor = vec4(avg, avg, avg, 1.0);
}
