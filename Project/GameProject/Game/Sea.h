#pragma once

/*�t�B�[���h�̊O���ɕ`�悳���C Field������*/

class Sea {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Sea();

	static void errcheck(GLuint s);

	void createMesh(GLuint& vao, GLuint& vbo, GLuint& ebo);

	void InitWater();

	void RenderWater();

private:

	const char* vertexShaderSource = R"(

#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

uniform mat4 WorldMatrix;
uniform mat4 PVWMatrix;
//�t���O�����g�V�F�[�_�[�ɓn���ϐ�
out vec4 V;//���W
out vec3 N;//�@���x�N�g��
out vec2 texCoord;
void main(void)
{
	vec3 normal = vec3(0,1,0);
	V = WorldMatrix * vec4(inPosition, 1);
	gl_Position = PVWMatrix * vec4(inPosition, 1);
	N = normalize(mat3(WorldMatrix) * normal);
	texCoord = inTexCoord;
}


)";


	const char* tescShaderSource = R"(

)";

	const char* teseShaderSource = R"(

)";

	const char* geometryShaderSource = R"(


)";

	const char* fragmentShaderSource = R"(
#version 330 
uniform float alpha = 0.4;
uniform float time;
uniform float size = 0.1;
uniform float distortionScale = 1.5;   // �m�C�Y�̋����𒲐�
uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform vec3 sunDirection = vec3(0, -0.7, 0.7);
uniform vec3 eyePos;
uniform vec3 waterColor = vec3(0.6, 0.6, 1.0);
uniform vec3 lightAmbientColor;
uniform vec3 lightDiffuseColor;

in vec4 V;
in vec3 N;
in vec2 texCoord;
out vec4 out_color[2];

// �m�C�Y�����֐� (�g�ׂ̍����𒲐�)
vec4 getNoise(vec2 uv) {
	vec2 uv0 = (uv / 103.0) + vec2(time / 17.0, time / 29.0);
	vec2 uv1 = uv / 107.0 - vec2(time / -19.0, time / 31.0);
	vec2 uv2 = uv / vec2(8907.0, 9803.0) + vec2(time / 101.0, time / 97.0);
	vec2 uv3 = uv / vec2(1091.0, 1027.0) - vec2(time / 109.0, time / -113.0);
	vec4 noise = texture(normalMap, uv0) +
		texture(normalMap, uv1) +
		texture(normalMap, uv2) +
		texture(normalMap, uv3);
	return noise * 0.5 - 1.0;
}

// �t���l�����ʂ̌v�Z
float fresnelEffect(vec3 eyeDirection, vec3 surfaceNormal) {
    float fresnel = pow(1.0 - max(dot(eyeDirection, surfaceNormal), 0.0), 3.0);
    return clamp(fresnel * 2.0, 0.0, 1.0); // �t���l�����ʂ�����
}

// ���z���̌v�Z (�L���L������)
void sunLight(const vec3 surfaceNormal, const vec3 eyeDirection, float shiny, float spec, float diffuse, inout vec3 diffuseColor, inout vec3 specularColor) {
	vec3 reflection = normalize(reflect(sunDirection, surfaceNormal));
	float direction = max(0.0, dot(eyeDirection, reflection));

    // �X�y�L�����[�}�b�v�̓ǂݍ���
    float specularStrength = texture(specularMap, texCoord).r;
    specularStrength = clamp(specularStrength, 0.0, 1.0);

    // �n�C���C�g������ (�V���[�v�ɃL���L��������)
    float highlight = pow(direction, shiny * 20.0) * 2.0;
    highlight = clamp(highlight, 0.0, 1.0);
    
    // �X�y�L�����[���C�g�̌v�Z
    specularColor += highlight * lightDiffuseColor * spec * specularStrength + lightAmbientColor;
    
    // �f�B�t���[�Y���C�g�̌v�Z
    diffuseColor += max(dot(sunDirection, surfaceNormal), 0.0) * lightDiffuseColor * diffuse;
}

void main() {
    // �m�C�Y���g�p���Đ��ʂ̖@���𐶐�
	vec4 noise = getNoise(V.xz * size);
	vec3 surfaceNormal = normalize(noise.xzy * vec3(1.5, 1.0, 1.5));
	
    // �J��������̎�������
	vec3 worldToEye = eyePos - V.xyz;
	vec3 eyeDirection = normalize(worldToEye);
	
    // �t���l�����ʂ��v�Z
    float fresnel = fresnelEffect(eyeDirection, surfaceNormal);
	
    // ���̌v�Z
	vec3 diffuseLight = lightDiffuseColor;
	vec3 specularLight = vec3(0.0);
	sunLight(surfaceNormal, eyeDirection, 10.0, 0.4, 0.6, diffuseLight, specularLight);

    // �t���l�����ʂ𔽉f�����X�y�L�����[
    specularLight *= fresnel;
	
    // �U�����̌v�Z
	vec3 scatter = max(0.0, dot(surfaceNormal, eyeDirection)) * waterColor;
	float s = 1.0f;
	vec3 albedo = ((scatter + lightAmbientColor * waterColor) * s);
	vec3 outgoingLight = albedo;
	
    // �o��
	out_color[0] = vec4(outgoingLight, alpha);
	out_color[1] = vec4(specularLight, 1);
}


)";

	CTexture tex_normal_map;
	CTexture tex_specular_map;
	unsigned int shaderProgram;
	GLuint VAO, VBO, EBO;
};