#include <backend/bn.h>
#include <backend/font_manager.h>
#include <frontend/icons.h>
#include <frontend/ui.h>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <string>
#include <unordered_map>

void Titlebar(const BN::FontManager &font_manager) {

  ImGui::PushFont(font_manager.GetFont(BN::FontType::Ubuntu_Bold_18));

  unsigned int flags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
      ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize;

  if (ImGui::BeginChild("Notes_Menu_Title",
                        ImVec2(300.0f, ImGui::GetTextLineHeight() + 20.0f), 0,
                        flags)) {

    ImGui::SetCursorPosY(8.0f);
    ImGui::Dummy(ImVec2(8.0f, 0));
    ImGui::SameLine();
    ImGui::Button(ICON_LC_MENU);
    ImGui::SameLine(0, 75.0f);
    ImGui::Text("All Notes");
    ImGui::SameLine(0, 75.0f);
    if (ImGui::Button(ICON_LC_SQUARE_PLUS)) {
      BN::CreateNewNote();
    }

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

  ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.25f, 0.28f, 0.40f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.25f, 0.28f, 0.40f, 1.0f));
  if (ImGui::BeginChild("Searchbar",
                        ImVec2(300.0f, ImGui::GetTextLineHeight() + 20.0f),
                        ImGuiChildFlags_Borders, flags)) {
  
    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + 16.0f, ImGui::GetCursorPos().y + 10.0f));
    ImVec2 pos = ImGui::GetCursorPos(); 
    ImGui::TextDisabled(ICON_LC_SEARCH); 
    ImGui::SetCursorPos(ImVec2(ImGui::CalcTextSize(ICON_LC_SEARCH).x+20.0f, pos.y-5.0f));

    static std::string search_text;
    if (ImGui::InputTextWithHint("##search_input_text",
                                 "Search for notes and tags", &search_text)) {
      // call backend function here later
      BN::Search(search_text);
    }
    if (search_text.empty()) {
      BN::ClearSearch();
    }
  }
  ImGui::EndChild();
  ImGui::PopFont();
  ImGui::PopStyleColor(2);
}

void NotesList(const BN::FontManager &font_manager) {

  auto notes_map = BN::GetFilteredNotesMap();
  for (const auto &[id, note] : notes_map) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.14f, 0.15f, 0.23f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10.0f);
    ImGui::SetCursorPos(
        ImVec2(ImGui::GetCursorPosX() + 12.0f, ImGui::GetCursorPosY() + 12.0f));

    std::string note_id = "##" + std::to_string(id);
    std::string note_title = note.title.empty() ? "New Note" : note.title;
    std::string note_description =
        note.description.empty() ? "New Description" : note.description;

    if (ImGui::BeginChild(note_id.c_str(), ImVec2(268.0f, 100.0f), 0,
                          ImGuiWindowFlags_AlwaysUseWindowPadding)) {
      ImGui::SetCursorPos(ImVec2(16, 16));
      ImGui::PushFont(font_manager.GetFont(BN::FontType::Ubuntu_Bold_16));
      ImGui::TextWrapped("%s", note_title.c_str());
      ImGui::PopFont();
      ImGui::SetCursorPos(ImVec2(16, ImGui::GetCursorPosY() + 10));
      ImGui::TextWrapped("%s", note_description.c_str());

      ImGui::SetCursorPos(ImVec2(0, 0));
      if (ImGui::InvisibleButton("##", ImVec2(268.0f, 100.0f))) {
        BN::selected_id = note.id;
      }
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }
}

void BN_UI::ShowNodeEditor(const BN::FontManager &font_manager) {

  unsigned int flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoDecoration |
                       ImGuiWindowFlags_NoResize;

  ImVec2 display_size = ImGui::GetIO().DisplaySize;

  ImGui::SetNextWindowPos(ImVec2(300.0f, 0.0f));
  ImGui::SetNextWindowSize(ImVec2(display_size.x - 300.0f, display_size.y));
  // Main Right Panel
  if (ImGui::Begin("##NodeEditor", NULL, flags)) {
    // Top Editor Menu with Icon Buttons
    if (ImGui::BeginChild("##Editor_Menu",
                          ImVec2(-1.0f, ImGui::GetTextLineHeight() + 20.0f),
                          ImGuiChildFlags_Borders)) {
      ImGui::PushFont(font_manager.GetFont(BN::FontType::Ubuntu_Regular_18));
      ImGui::SetCursorPos(ImVec2(24.0f, 8.0f));
      if (ImGui::Button(ICON_LC_TRASH_2)) {
        BN::DeleteNote(BN::selected_id);
      }
      ImGui::SameLine(ImGui::GetWindowWidth() -
                      ImGui::CalcTextSize(ICON_LC_X).x - 24.0f);
      if (ImGui::Button(ICON_LC_X)) {
        BN::selected_id = -1;
      }
      ImGui::PopFont();
    }
    ImGui::EndChild();

    // Title and Description Editing Panel
    if (ImGui::BeginChild("##Editor_Panel", ImVec2(-1.0f, -1.0f))) {

      Note *note = BN::GetNote(BN::selected_id);
      if (note == nullptr) {
        ImGui::PushFont(font_manager.GetFont(BN::FontType::Ubuntu_Bold_32));
        float text_width = ImGui::CalcTextSize("Nothing to show").x;
        ImGui::SetCursorPos(ImVec2((display_size.x - 300.0f - text_width) / 2,
                                   display_size.y / 2));
        ImGui::TextDisabled("Nothing to show");
        ImGui::PopFont();
        ImGui::EndChild();
        ImGui::End();
        return;
      }

      // TITLE: InputTextWithHint()
      ImGui::SetCursorPos(ImVec2(16, 16));
      ImGui::PushFont(font_manager.GetFont(BN::FontType::Ubuntu_Bold_32));

      if (ImGui::InputTextWithHint("##Editor_Note_Title", "Note Title",
                                   &note->title,
                                   ImGuiInputTextFlags_CallbackEdit |
                                       ImGuiInputTextFlags_EnterReturnsTrue,
                                   BN::InputTextCallback, note)) {
        // move cursor to description input on enter key press for better user
        // experience
        ImGui::SetKeyboardFocusHere(1);
      }
      ImGui::PopFont();

      // DESCRIPTION: InputTextMultiline() with manual hint implementation
      float description_input_pos = ImGui::GetCursorPosY() + 16.0f;
      ImGui::SetCursorPos(ImVec2(16, description_input_pos));
      ImGui::PushFont(font_manager.GetFont(BN::FontType::Ubuntu_Regular_18));
      ImGui::InputTextMultiline("##Editor_Desc", &note->description,
                                ImVec2(-1.0f, -1.0f), 0, BN::InputTextCallback,
                                note);

      // show placeholder if description is empty
      if (note->description.empty()) {
        ImGui::SetCursorPos(ImVec2(20, description_input_pos));
        ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f),
                           "Write your note here");
      }
      ImGui::PopFont();
    }
    ImGui::EndChild();
  }
  ImGui::End();

  // Save note every frame (TEMP)
  BN::SaveNote(BN::selected_id);
}

void BN_UI::ShowNotesList(const BN::FontManager &font_manager) {
  float max_y = ImGui::GetIO().DisplaySize.y;

  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::SetNextWindowSizeConstraints(ImVec2(300.0f, max_y),
                                      ImVec2(400.0f, max_y));

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
