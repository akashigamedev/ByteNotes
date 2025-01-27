#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <application.h>

Application::Application(int width, int height, const std::string& name)
{
  InitGLFW();
  InitWindow(width, height, name);
  InitGlad();
  glViewport(0, 0, width, height);
}

Application::~Application()
{
  Exit();
}

GLFWwindow* Application::GetWindow()
{
  return this->window;
}


void Application::InitGLFW()
{
  CheckAndExit(glfwInit(), "Failed to initialize GLFW!");
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Application::InitWindow(int width, int height, const std::string& name)
{
  this->window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
  CheckAndExit(window, "Failed to initialize window!"); 
  glfwMakeContextCurrent(window);
}

void Application::InitGlad()
{
  CheckAndExit(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD!");
}

void Application::Exit()
{
  if(window != NULL)
  {
    glfwDestroyWindow(window);
  }
  glfwTerminate();
  std::exit(EXIT_SUCCESS);
}

void Application::CheckAndExit(bool condition, const std::string& msg)
{
  if(!condition)
  {
    std::cerr << "Error: " <<  msg << std::endl;
    Exit();
  }
}

bool Application::IsActive()
{
  return !glfwWindowShouldClose(this->window);
}

void Application::Run(const std::function<void()> &callback)
{
  glfwPollEvents();
  callback();
  glfwSwapBuffers(this->window);
}

