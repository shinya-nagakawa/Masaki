#include "Sea.h"

Sea::Sea(){
}

void Sea::errcheck(GLuint s){
	GLint compiled;
	glGetShaderiv(s, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLint length;
		GLchar* log;
		glGetShaderiv(s, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) {
			log = new GLchar[length];
			glGetShaderInfoLog(s, length, &length, log);
			MessageBox(GL::hWnd, log, "エラー", MB_OK);
			delete log;
		}
	}
}

void Sea::createMesh(GLuint& vao, GLuint& vbo, GLuint& ebo){
	// 頂点データ
	float vertices[] = {
		-1.0f, 0.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, 0.0f, -1.0f,  1.0f, 0.0f,
		-1.0f, 0.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, 0.0f,  1.0f,  1.0f, 1.0f,
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 1, 3
	};

	// VAO, VBO, EBOの生成
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

	// 頂点属性の設定
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

void Sea::InitWater(){
	shaderProgram = glCreateProgram();
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	//unsigned int tescShader = glCreateShader(GL_TESS_CONTROL_SHADER);
	//unsigned int teseShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	errcheck(vertexShader);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	errcheck(fragmentShader);

	//glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
	//glCompileShader(geometryShader);
	//errcheck(geometryShader);

	//glShaderSource(tescShader, 1, &tescShaderSource, NULL);
	//glCompileShader(tescShader);
	//errcheck(tescShader);

	//glShaderSource(teseShader, 1, &teseShaderSource, NULL);
	//glCompileShader(teseShader);
	//errcheck(teseShader);

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//glAttachShader(shaderProgram, geometryShader);
	//glAttachShader(shaderProgram, tescShader);
	//glAttachShader(shaderProgram, teseShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//glDeleteShader(geometryShader);
	//glDeleteShader(tescShader);
	//glDeleteShader(teseShader);
	glUseProgram(shaderProgram);

	tex_normal_map.Load("field/water/waternormals.png");
	tex_specular_map.Load("field/water/waterdudv.png");

	createMesh(VAO, VBO, EBO);
}

void Sea::RenderWater(){
	glDisable(GL_CULL_FACE);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	//glUniform1i(glGetUniformLocation(shaderProgram, "heightMap"), 0);
	//glUniform1f(glGetUniformLocation(shaderProgram, "displacementScale"), 0.3f);

	glUniform1i(glGetUniformLocation(shaderProgram, "normalMap"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "specularMap"), 1);

	glActiveTexture(GL_TEXTURE0);
	tex_normal_map.MapTexture();
	glActiveTexture(GL_TEXTURE1);
	tex_specular_map.MapTexture();
	glActiveTexture(GL_TEXTURE0);

	float timeValue = glfwGetTime() * 0.10f;
	glUniform1f(glGetUniformLocation(shaderProgram, "time"), timeValue);
	CMatrix matrix = CMatrix::MTranselate(0.0f, -3.5f, 0.0f) * CMatrix::MScale(1000.0f, 1000.0f, 1000.0f);
	CMatrix pvm = CCamera::GetCurrent()->GetProjectionMatrix() * CCamera::GetCurrent()->GetViewMatrix() * matrix;
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "WorldMatrix"), 1, GL_FALSE, matrix.f);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "PVWMatrix"), 1, GL_FALSE, pvm.f);
	//	glUniform3fv(glGetUniformLocation(shaderProgram, "viewDir"), 1, CCamera::GetCurrent()->GetDir().v);

		//不透明度
	glUniform1f(glGetUniformLocation(shaderProgram, "alpha"), 0.8f);
	//波の大きさ
	glUniform1f(glGetUniformLocation(shaderProgram, "size"), 0.5f);
	glUniform3fv(glGetUniformLocation(shaderProgram, "waterColor"), 1, CVector3D(0.4f, 0.6f, 1.0f).v);
	glBindFragDataLocation(shaderProgram, 0, "out_color");

	//明るさ
	glUniform3fv(glGetUniformLocation(shaderProgram, "lightAmbientColor"), 1, CVector3D(0.2f, 0.2f, 0.2f).v);
	glUniform3fv(glGetUniformLocation(shaderProgram, "lightDiffuseColor"), 1, CVector3D(1.0f, 1.0f, 1.0f).v);

	glUniform3fv(glGetUniformLocation(shaderProgram, "eyePos"), 1, CCamera::GetCurrent()->GetPos().v);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);

	glEnable(GL_CULL_FACE);
}
