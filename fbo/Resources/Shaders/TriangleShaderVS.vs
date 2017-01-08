attribute vec3 a_posL;
uniform mat4 u_matT;
attribute vec2 a_uv; 
varying vec2 v_uv;

void main()
{
gl_Position = u_matT*vec4(a_posL, 1.0);
v_uv = a_uv;
}
   