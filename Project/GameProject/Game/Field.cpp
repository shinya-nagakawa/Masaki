#include "Field.h"

Field::Field() : ObjectBase(eField) 
	, m_model(COPY_RESOURCE("Field", CModelObj)){
	m_rot += CVector3D(0.0f, DtoR(90.0f), 0.0f);
	m_scale = CVector3D(0.3f, 0.3f, 0.3f);

	//攻撃座標を設定
	m_atackPosList[0].push_back(CVector3D(-30.8f, -0.3f, 24.4f));
	m_atackPosList[1].push_back(CVector3D(-27.5f,  0.0f, 28.0f));
	m_atackPosList[2].push_back(CVector3D(-33.6f, -0.4f, 21.8f));
	m_atackPosList[3].push_back(CVector3D(-26.3f,  0.3f, 31.0f));
	m_atackPosList[4].push_back(CVector3D(-36.4f, -0.7f, 20.5f));
	m_atackPosList[5].push_back(CVector3D(-25.5f,  0.3f, 34.3f));
	m_atackPosList[6].push_back(CVector3D(-39.3f, -0.9f, 19.6f));
	m_atackPosList[7].push_back(CVector3D(-25.7f,  0.1f, 36.7f));
	m_atackPosList[8].push_back(CVector3D(-42.0f, -0.6f, 19.2f));
	m_atackPosList[9].push_back(CVector3D(-25.8f, -0.2f, 39.4f));

	//攻撃範囲を設定
	m_attackZone.InitializeAttackPos(m_atackPosList);
}

Field::~Field() {
}

void Field::Render() {
	m_skyBox.Render();
	m_model.SetRot(m_rot);
	m_model.SetScale(m_scale);
	m_model.Render();

	/*デバッグ 攻撃座標の表示*/
	//Utility::DrawSphere(CVector3D(-30.8f, -0.3f, 24.4f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-27.5f, 0.0f, 28.0f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-33.6f, -0.4f, 21.8f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-26.3f, 0.3f, 31.0f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-36.4f, -0.7f, 20.5f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-25.5f, 0.3f, 34.3f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-39.3f, -0.9f, 19.6f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-25.7f, 0.1f, 36.7f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-42.0f, -0.6f, 19.2f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
	//Utility::DrawSphere(CVector3D(-25.8f, -0.2f, 39.4f), 0.2f, CVector4D(0.0f, 1.0f, 1.0f, 1.0f));
}

AttackZone& Field::GetAttackZone(){
	return m_attackZone;
}


const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 PVWMatrix;
out vec3 vPos;
void main() {
    gl_Position = PVWMatrix * vec4(aPos, 1.0);
	vPos = aPos;
}
)";

const char* geometryShaderSource = R"(
#version 330 core
layout(points) in;
layout(triangle_strip, max_vertices = 6) out;

out vec2 TexCoord;
in vec3 vPos[];

uniform float time;
uniform float windStrength;
uniform mat4 PVWMatrix;
uniform mat4 builboardMatrix;

void main() {
	vec3 basePos = (PVWMatrix*vec4(vPos[0],1)).xyz;
 
    // 草の揺れを時間とともに変化させる
    float windOffset = sin(time + vPos[0].x * 3.0) * windStrength;

    // 根元と先端の揺れを異なるスケールで適用
    float swayFactor = 1.0f;  // 根元と先端で揺れを調整
    float adjustedWind = windOffset * swayFactor;

	float a = sin(vPos[0].x*0.3+vPos[0].z*2)*3.141592;
	float s = sin(a);
	float c = cos(a);
	float w = 0.2 + adjustedWind;
    // 草の頂点
    vec4 p0 = PVWMatrix*vec4(vPos[0] + vec3(-0.5*s, 0.0, -0.5*c),1.0);
    vec4 p1 = PVWMatrix*vec4(vPos[0] + vec3(0.5*s, 0.0, 0.5*c),1.0);
    vec4 p2 = PVWMatrix*vec4(vPos[0] + vec3((0.5+w)*s, 1.0, (0.5+w)*c),1.0);
    vec4 p3 = PVWMatrix*vec4(vPos[0] + vec3((-0.5+w)*s, 1.0, (-0.5+w)*c),1.0);
    

    // 草の三角形を描画
    gl_Position =p0;
    TexCoord = vec2(0.0, 1.0);
    EmitVertex();
    gl_Position = p1;
    TexCoord = vec2(1.0, 1.0);
    EmitVertex();
    gl_Position = p2;
    TexCoord = vec2(1.0, 0.0);
    EmitVertex();
    EndPrimitive();

    gl_Position = p0;
    TexCoord = vec2(0.0, 1.0);
    EmitVertex();
    gl_Position = p2;
    TexCoord = vec2(1.0, 0.0);
    EmitVertex();
    gl_Position = p3;
    TexCoord = vec2(0.0, 0.0);
    EmitVertex();
    EndPrimitive();
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec2 TexCoord;
out vec4 FragColor[2];

uniform sampler2D grassTexture;

void main() {
    vec4 texColor = texture(grassTexture, TexCoord);
    if (texColor.a <= 0.00)
        discard;
    FragColor[0] = texColor;
    FragColor[1] = vec4(0,0,0,0);
}
)";


void Grass::GenerateGrassPositions() {
	const float range = 10.0f;
	for (int i = 0; i < m_grassPositions.size(); i++) {
		m_grassPositions[i] = CVector3D(Utility::Rand(-range, range), 0.0f, Utility::Rand(-range, range));
	}
}

bool Grass::WriteFile(const char* posfile)
{
	std::ofstream ofs(posfile);
	if (!ofs) {
		std::cerr << "Failed to open file." << std::endl;
		return false;
	}
	CVector3D pos;
	for (auto& pos : m_grassPositions)
	{
		ofs << pos.x << " " << pos.y << " " << pos.z << std::endl;
	}
	return true;
}

bool Grass::ReadFile(const char* posfile)
{
	m_grassPositions.clear();
	std::ifstream ifs(posfile);
	if (!ifs) {
		std::cerr << "Failed to open file." << std::endl;
		return false;
	}
	CVector3D pos;
	std::string tmp;
	while (getline(ifs, tmp)) {
		std::stringstream ss;
		ss << tmp;
		ss >> pos.x >> pos.y >> pos.z;
		m_grassPositions.push_back(pos);
	}
	return true;
}

Grass::Grass(const char* texture) :Base(BaseType::eGrass), m_grassPositions(2000), m_vao(0)
{
	GenerateGrassPositions();
	ADD_RESOURCE(texture, CTexture::LoadTexture(texture));
	m_grass_texture = GET_RESOURCE(texture, CTexture);
	m_grass_texture->SetWrapST(GL_CLAMP);
}

Grass::Grass(const char* texture, const char* posfile) :Base(BaseType::eGrass), m_vao(0)
{
	if (!ReadFile(posfile))
		GenerateGrassPositions();
	ADD_RESOURCE(texture, CTexture::LoadTexture(texture));
	m_grass_texture = GET_RESOURCE(texture, CTexture);
	m_grass_texture->SetWrapST(GL_CLAMP);
}

void Grass::Update()
{
	if (PUSH(CInput::eButton1)) {
		if (Field* f = dynamic_cast<Field*>(FindObject(BaseType::eField))) {
			for (auto it = m_grassPositions.begin(); it != m_grassPositions.end();) {
				bool ok = false;
				CVector3D c, n;
				if (f->GetModel()->CollisionRay(&c, &n, *it + CVector3D(0, 10, 0), *it + CVector3D(0, -10, 0))) {
					ok = true;
					*it = c;
				}
				if (!ok) {
					it = m_grassPositions.erase(it);
				}
				else {
					it++;
				}
			}
			WriteFile("grass_data_tmp.txt");
		}

	}
}

void Grass::Render()
{
	if (!m_vao) {
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_grassPositions.size() * sizeof(CVector3D), m_grassPositions.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CVector3D), (void*)0);
		glEnableVertexAttribArray(0);

		m_shaderProgram = glCreateProgram();
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
		glCompileShader(geometryShader);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		glAttachShader(m_shaderProgram, vertexShader);
		glAttachShader(m_shaderProgram, geometryShader);
		glAttachShader(m_shaderProgram, fragmentShader);
		glLinkProgram(m_shaderProgram);
		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
		glUseProgram(m_shaderProgram);
	}
	//	glDepthMask(GL_FALSE);


	glUseProgram(m_shaderProgram);
	glUniform1i(glGetUniformLocation(m_shaderProgram, "grassTexture"), 0);
	// 時間と風の強さの uniform 変数
	static float time = 0.0f;
	float windStrength = 0.1f;
	int timeLoc = glGetUniformLocation(m_shaderProgram, "time");
	int windLoc = glGetUniformLocation(m_shaderProgram, "windStrength");
	int PVWMatrix = glGetUniformLocation(m_shaderProgram, "PVWMatrix");
	int builboardMatrix = glGetUniformLocation(m_shaderProgram, "builboardMatrix");
	CMatrix world;
	world.SetIndentity();
	time += 0.01f;  // 経過時間の更新
	glUniform1f(timeLoc, time);
	glUniform1f(windLoc, windStrength);
	CMatrix pvm = CCamera::GetCurrent()->GetProjectionMatrix() * CCamera::GetCurrent()->GetViewMatrix();
	CMatrix buil = CCamera::GetCurrent()->GetViewMatrix().GetInverse();
	glUniformMatrix4fv(PVWMatrix, 1, GL_FALSE, pvm.f);
	glUniformMatrix4fv(builboardMatrix, 1, GL_FALSE, buil.f);
	//glUniformMatrix4fv(PVWMatrix, 1, GL_FALSE, (world).f);
	m_grass_texture->MapTexture();
	glBindVertexArray(m_vao);
	glDrawArrays(GL_POINTS, 0, m_grassPositions.size());
	m_grass_texture->UnmapTexture();
	//	glDepthMask(GL_TRUE);
	glBindVertexArray(0);
	glUseProgram(0);

}