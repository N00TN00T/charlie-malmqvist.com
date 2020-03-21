#shader vertex
#version 330 core
layout (location = 0) in vec2 v_position;
layout (location = 1) in vec2 v_uv;
layout (location = 2) in vec4 v_color;
layout (location = 3) in float v_location;
out vec2 uv;
out vec4 color;
out float location;
uniform mat4 u_camTransform;
void main() {
    uv = v_uv;
	location = v_location;
	color = v_color;
    gl_Position = u_camTransform * vec4(v_position, 0.0, 1.0);
}
#shader fragment
#version 330 core
out vec4 fragColor;
in vec2 uv;
in vec4 color;
in float location;
uniform sampler2D u_textures[32];
void main() {
    fragColor = texture(u_textures[int(round(location))], uv) * color;
}