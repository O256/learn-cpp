#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoord;

void main() {
    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 color = vec3(0.7) * diff;
    FragColor = vec4(color, 1.0);
} 