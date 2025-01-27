#pragma once

#include<string>
#include <GLFW/glfw3.h>
#include <functional>
class Application
{

public:
  GLFWwindow *window;
  Application(int width, int height, const std::string& name);
  ~Application();
  GLFWwindow* GetWindow();
  bool IsActive();
  void Run(const std::function<void()> &callback);
  void Exit();
private:
  void InitGLFW();
  void InitWindow(int width, int height, const std::string& name);
  void InitGlad();
  void CheckAndExit(bool condition, const std::string& msg);
};

