#include "../include/GraphicsHandler.h"

GraphicsHandler::GraphicsHandler() {

}

void GraphicsHandler::useShader() {
  glUseProgram(shaderProgram);
}

GLuint GraphicsHandler::getShader() {
  return shaderProgram;
}

void GraphicsHandler::init(int width, int height) {
  
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  loadShaders("./shaders/shader.vert", "./shaders/shader.frag");
  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width),
                                   static_cast<GLfloat>(height), 0.0f, -0.1f, 1.0f);

  grid = glm::vec2(width, height);
  
  glUseProgram(shaderProgram);
  glUniform1i(glGetUniformLocation(shaderProgram, (const GLchar*)"image"), 0);
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, (const GLchar*)"projection"), 1, GL_FALSE, glm::value_ptr(projection));

  
  GLuint VBO;
  GLfloat vertices[] = { 
    // Pos      // Tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 
    
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };
  
  glGenVertexArrays(1, &quadVAO);
  glGenBuffers(1, &VBO);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glBindVertexArray(quadVAO);
  glEnableVertexAttribArray(0);
  
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
  // Load textures probs
    
  texture = txt::LoadTexture("./Textures/image.png");
}

void GraphicsHandler::drawObject(glm::vec2 position, glm::vec2 size) {
  
  transformModel(glm::vec3(position.x-size.x*0.5f, grid.y-position.y-size.y*0.5f, 0.0f), 
                 size, 
                 0.0f,
                 glm::vec3(1.0f, 1.0f, 1.0f));
   
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  
  draw();
}

void GraphicsHandler::drawObject(glm::vec2 position, glm::vec2 size, GLfloat rotate) {
  
  transformModel(glm::vec3(position.x-size.x*0.5f, grid.y-position.y-size.y*0.5f, 0.0f), 
                 size, 
                 rotate,
                 glm::vec3(1.0f, 1.0f, 1.0f));
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  
  draw();
}

void GraphicsHandler::drawObject(glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 colour) {
    transformModel(glm::vec3(position.x-size.x*0.5f, grid.y-position.y-size.y*0.5f, 0.0f), 
                   size, 
                   rotate,
                   colour);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    draw();
}

void GraphicsHandler::draw() {
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);    
}


void GraphicsHandler::transformModel(glm::vec3 position, glm::vec2 size, GLfloat rotation, glm::vec3 colour) {
  glm::mat4 model;
  model = glm::translate(model, position);
  
  if ((int)rotation%360 != 0) {
    model = glm::translate(model, glm::vec3(0.5f*size.x, 0.5f*size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f*size.x, -0.5f*size.y, 0.0f));
  }
  
  model = glm::scale(model, glm::vec3(size, 1.0f));
  
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, (const GLchar*)"model"), 1, GL_FALSE, glm::value_ptr(model));
  glUniform3f(glGetUniformLocation(shaderProgram, "fragColour"), colour.x, colour.y, colour.z);
}

void GraphicsHandler::loadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. \n", vertex_file_path);
		getchar();
		return;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	shaderProgram = ProgramID;
}
