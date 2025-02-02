#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <application.h>
#include <memory>

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
  return window.get();
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
  window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(width, height, name.c_str(), NULL, NULL), glfwDestroyWindow);
  CheckAndExit(window.get(), "Failed to initialize window!"); 
  glfwMakeContextCurrent(window.get());
}

void Application::InitGlad()
{
  CheckAndExit(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD!");
}

void Application::Exit()
{
  if(window != NULL)
  {
    glfwDestroyWindow(window.get());
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
  return !glfwWindowShouldClose(window.get());
}

void Application::Run(const std::function<void()> &callback)
{
  glfwPollEvents();
  callback();
  glfwSwapBuffers(window.get());
}

