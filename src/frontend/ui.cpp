#include <font_manager.h>
#include <icons.h>
#include <imgui.h>
#include <string>
#include <vector>
#include <iostream>
#include <ui.h>

void Titlebar(const BN::FontManager &font_manager) {

  ImGui::PushFont(font_manager.GetFont(BN::FontType::Ubuntu_Bold_18));

  unsigned int flags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
      ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize;

  if (ImGui::BeginChild("Notes_Menu_Title", ImVec2(300.0f, ImGui::GetTextLineHeight() + 20.0f), 0, flags)) {

    ImGui::SetCursorPosY(8.0f);
    ImGui::Dummy(ImVec2(8.0f, 0));
    ImGui::SameLine();
    ImGui::Button(ICON_LC_MENU);
    ImGui::SameLine(0, 75.0f);
    ImGui::Text("All Notes");
    ImGui::SameLine(0, 75.0f);
    ImGui::Button(ICON_LC_SQUARE_PLUS);
    ImGui::Dummy(ImVec2(0, 0));
  }
  ImGui::PopFont();
  ImGui::EndChild();
}

void Searchbar(const BN::FontManager &font_manager) {
  ImGui::PushFont(font_manager.GetFont(BN::FontType::Ubuntu_Regular_16));

  unsigned int flags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
      ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize;

  ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.21f, 0.22f, 0.30f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.21f, 0.22f, 0.30f, 1.0f));
  if (ImGui::BeginChild("Searchbar", ImVec2(300.0f, ImGui::GetTextLineHeight() + 20.0f), ImGuiChildFlags_Borders, flags)) {

    ImGui::SetCursorPosY(8.0f);
    ImGui::Dummy(ImVec2(8.0f, 0));
    ImGui::SameLine();
    ImGui::TextDisabled(ICON_LC_SEARCH);
    ImGui::SameLine(0.0f, 16.0f);

    static char search_text[100] = "";
    if (ImGui::InputTextWithHint("##search_input_text", "Search for notes and tags", search_text, sizeof(search_text))) {
      // call backend function here later
    }
  }
  ImGui::PopFont();
  ImGui::EndChild();
  ImGui::PopStyleColor(2);
}


struct Note
{
  std::string title;
  std::string description;
};

void NotesList(const BN::FontManager &font_manager) {
  static std::vector<struct Note> notes = {
  {"Favourite Foods", "Pizza (Italy) - A flatbread topped with sauce, cheese, ..."},
  {"Trip to Goa", "This summer in 2024, We went on a vacation in GOA. It was  .."},
  {"Akash’s Birthday Party", "Akash’s birthday party was awesome, everyone had fun..."},
  {"Game night 2024", "Thursday, 21 Jan 2024, We had a game night with all of my fri.."}
  };

  for(const auto& note : notes)
  {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.14f, 0.15f, 0.22f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10.0f);
    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 12.0f, ImGui::GetCursorPosY() + 12.0f));
    if(ImGui::BeginChild(note.title.c_str(), ImVec2(268.0f, 100.0f), 0, ImGuiWindowFlags_AlwaysUseWindowPadding))
    {
      ImGui::SetCursorPos(ImVec2(16, 16));
      ImGui::TextWrapped("%s", note.title.c_str());
      ImGui::SetCursorPos(ImVec2(16, ImGui::GetCursorPosY()+16));
      ImGui::TextWrapped("%s", note.description.c_str());
      
      ImGui::SetCursorPos(ImVec2(0, 0));
      if(ImGui::InvisibleButton(note.title.c_str(), ImVec2(268.0f, 100.0f)))
      {
        std::cout << note.title << "\n" << note.description << std::endl;
      }
     
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }
}

void BN_UI::ShowNodeEditor(const BN::FontManager& font_manager) {
  
  unsigned int flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoDecoration;

  ImVec2 display_size = ImGui::GetIO().DisplaySize;

  ImGui::SetNextWindowPos(ImVec2(300.0f, 0.0f));
  ImGui::SetNextWindowSize(ImVec2(display_size.x-300.0f, display_size.y));
  if(ImGui::Begin("##NodeEditor", NULL, flags))
  {
    if(ImGui::BeginChild("##Editor_Menu", ImVec2(-1.0f, ImGui::GetTextLineHeight() + 20.0f), ImGuiChildFlags_Borders))
    {
      ImGui::PushFont(font_manager.GetFont(BN::FontType::Ubuntu_Regular_18));
      ImGui::SetCursorPos(ImVec2(24.0f, 8.0f));
      if(ImGui::Button(ICON_LC_TRASH_2))
      {

      }
      ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize(ICON_LC_X).x-24.0f);
      if(ImGui::Button(ICON_LC_X))
      {

      }
      ImGui::PopFont();
    } 
    ImGui::EndChild();
  

  }
  ImGui::End();
}

void BN_UI::ShowNotesList(const BN::FontManager &font_manager) {
  float max_y = ImGui::GetIO().DisplaySize.y;
  
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::SetNextWindowSizeConstraints(ImVec2(300.0f, max_y), ImVec2(400.0f, max_y));

  unsigned int flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoDecoration;

  if (ImGui::Begin("##Notes_List", NULL, flags)) {
    Titlebar(font_manager);
    Searchbar(font_manager);
    NotesList(font_manager);
  }
  ImGui::End();
}
