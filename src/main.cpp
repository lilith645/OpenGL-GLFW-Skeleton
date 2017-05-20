#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define  WIDTH  1024
#define  HEIGHT 786

#define GRIDX 100
#define GRIDY 100
/*
#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#else 
#include <GL/glc.h>
#include <GL/glu.h>
#endif
*/

void draw(GLFWwindow* window, float deltaTime) {
  
}

GLFWwindow* init() {
  GLFWwindow* window;
  
  if(!glfwInit()) {
    glfwSetWindowShouldClose(window, true);
    return window;
  }

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Windowed mode
  window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", nullptr, nullptr);
  // Fullscreen mode
  // window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", glfwGetPrimaryMonitor(), NULL);

  if(!window) {
    glfwTerminate();
    glfwSetWindowShouldClose(window, true);
    return window;
  }

  //gluOrtho2D(0.0f, GRIDX, 0.0f, GRIDY);

  return window;
}

int main(int argc, char* args[]) {
  GLFWwindow* window = init();

  glfwMakeContextCurrent(window);
  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  double last_time = glfwGetTime();
  while(!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    float ratio = width / (float)height;
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(0.f, GRIDX, 0.f, GRIDY);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 255.0f);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor4ub(255,255,255,255);
    
    double current_time = glfwGetTime();
    float delta_time = (float) (current_time - last_time);
    last_time = glfwGetTime();

     draw(window, delta_time);

    glfwSwapInterval(1);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  // clean
  glfwTerminate();
  return 0;
}
