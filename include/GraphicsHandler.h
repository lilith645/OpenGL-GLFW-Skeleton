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
    
    // Call once per loop (At start)
    void useShader();
    
    // Draws object at position x/y, with specified size, rotated 0 degrees, full colour
    void drawObject(glm::vec2 position, glm::vec2 size);
    // Draws object at position x/y, with specified size, rotated specified degrees, full colour
    void drawObject(glm::vec2 position, glm::vec2 size, GLfloat rotate);
    // Draws object at position x/y, with specified size, rotated specified degrees, With only colours specified drawn
    void drawObject(glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 colour);
    
    GLuint getShader();
    
  protected:
    void draw();
    void loadShaders(const char * vertex_file_path,const char * fragment_file_path);
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
