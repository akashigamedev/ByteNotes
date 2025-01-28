#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <application.h>

int main()
{
  Application app(800, 600, "ByteNotes");

  // ImGUI Configuration
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  
  // Dark Theme UI
  ImGui::StyleColorsDark();

  // Initialize ImGui With OpenGL
  ImGui_ImplGlfw_InitForOpenGL(app.GetWindow(), true);
  ImGui_ImplOpenGL3_Init("#version 330");

  while (app.IsActive())
  {
    app.Run([&]
            {
      ImGuiStyle& style = ImGui::GetStyle();
      style.WindowRounding = 10.0f;
      // Start new ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      // UI Stuff Here
      ImGui::Begin("Hello ImGui!");
      ImGui::Text("This is a simple example of ImGui.");
      static char inputText[200] = "";
      ImGui::InputText("Input Text", inputText, IM_ARRAYSIZE(inputText));

      if(ImGui::Button("Click Me"))
      {
        std::cout << "Button Clicked! Text: " << inputText << std::endl;
      }
      ImGui::End(); // End of UI Stuff

      //Rendering
      ImGui::Render(); // Render all UI Elements on screen

      // Clear Screen with Violet Color
      glClearColor(0.6f, 0.2f, 0.5f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // Finalize UI Elements into Vertex Data and Draw on Screen
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); });
  }

  ImGui_ImplOpenGL3_Shutdown(); // Close UI Windows
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  app.Exit();
  return 0;
}
