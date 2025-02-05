#include<imgui.h>
#include<style.h>

void BN_UI::SetStyleCatppuccin()
{
  ImGuiStyle& style = ImGui::GetStyle();
  style.WindowPadding = ImVec2(0, 0);
  style.WindowRounding = 0;
  style.FrameRounding = 0;
  style.ScrollbarRounding = 0;
  style.ItemSpacing = ImVec2(0, 0);
  style.ChildBorderSize = 1.0f;

  style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.79f, 0.82f, 0.96f, 1.0f);
  style.Colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.12f, 0.18f, 1.0f);
  style.Colors[ImGuiCol_ChildBg] = ImVec4(0.11f, 0.12f, 0.18f, 1.0f);
  style.Colors[ImGuiCol_PopupBg] = ImVec4(0.14f, 0.15f, 0.22f, 1.0f);
  style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 0.38f, 1.0f);
  style.Colors[ImGuiCol_FrameBg] = ImVec4(0.11f, 0.12f, 0.18f, 1.0f);
  style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.21f, 0.22f, 0.3f, 1.0f);
  style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.21f, 0.22f, 0.3f, 1.0f);
  style.Colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.09f, 0.14f, 1.0f);
  style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.09f, 0.09f, 0.14f, 1.0f);
  style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.09f, 0.09f, 0.14f, 1.0f);
  style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.21f, 0.22f, 0.3f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.21f, 0.22f, 0.3f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.12f, 0.14f, 0.21f, 1.0f);
  style.Colors[ImGuiCol_Button] = ImVec4(0.54f, 0.83f, 0.79f, 0.0f);
  style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.37f, 0.67f, 0.73f, 0.0f);
  style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.37f, 0.67f, 0.73f, 0.0f);
}

// Other themes may go here
