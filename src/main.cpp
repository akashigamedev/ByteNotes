#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <application.h>
#include <frontend/ui.h>
#include <backend/bn.h>
#include <backend/font_manager.h>
#include <frontend/style.h>

int main()
{
  Application app(800, 600, "ByteNotes");

  // ImGUI Configuration
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  BN::FontManager font_manager;
  font_manager.LoadDefaultFont();

  BN_UI::SetStyleCatppuccin();
  // Initialize ImGui With OpenGL
  ImGui_ImplGlfw_InitForOpenGL(app.GetWindow(), true);
  ImGui_ImplOpenGL3_Init("#version 330");


  BN::LoadNotesInMap();

  while (app.IsActive())
  {
    app.Run([&]
            {
      // Start new ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      // UI Stuff Here
     BN_UI::ShowNotesList(font_manager);
     BN_UI::ShowNodeEditor(font_manager);     

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
