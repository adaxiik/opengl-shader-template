#version 330 core
out vec4 FragColor;
uniform vec2 res;
uniform float time;


void main()
{
   vec2 uv = (gl_FragCoord.xy-.5*res)/res.y;

   FragColor = vec4(uv,0, 1.0f);
}
