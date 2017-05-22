#ifndef GRAPHICSHANDLER
#define GRAPHICSHANDLER

// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <fstream>

#include "./LoadTexture.h"

class GraphicsHandler {
  public:
    GraphicsHandler();
    void init(int width, int height);
    void loadShaders(const char * vertex_file_path,const char * fragment_file_path);
    void useShader();
    
    void drawObject(glm::vec2 position, glm::vec2 size);
    void drawObject(glm::vec2 position, glm::vec2 size, GLfloat rotate);
    void drawObject(glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 colour);
    
    GLuint getShader();
    
  protected:
    void draw();
    void transformModel(glm::vec3 position, glm::vec2 size, GLfloat rotation, glm::vec3 colour);

    GLuint shaderProgram;
    GLuint quadVAO;
    
    GLuint texture;
    
    glm::vec2 grid;
    // Interesting way to give names to array
    // std::map<std::string, Texture2D> textures
    // std::string name = "Weapon3"
    // return textures[name]
};

#endif
