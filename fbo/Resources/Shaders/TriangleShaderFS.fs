precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_texture_0;


void main()
{
	gl_FragColor = texture2D(u_texture_0,v_uv); 
}