
#include "bn.h"
#include <chrono>
#include <filesystem>
#include <fstream>

const std::unordered_map<long, Note> &BN::GetNotesMap() { return notes_map; }
const std::unordered_map<long, Note> &BN::GetFilteredNotesMap() { return filtered_notes_map; }

long BN::CreateNewNote() {
  long id = GetTimeInmillis();
  notes_map[id] = {id, "", ""};
  selected_id = id;
  return id;
}

void BN::LoadNotesInMap() {
  namespace fs = std::filesystem;

  if (!fs::exists(BN::notes_path)) {
    fs::create_directory(BN::notes_path);
  }

  for (const auto &p : fs::directory_iterator(BN::notes_path)) {
    if (!p.is_regular_file()) {
      continue;
    }

    std::string path = p.path().string().c_str();
    int start = path.find("Note_") + 5;
    int end = path.rfind(".txt");
    long id = std::stol(path.substr(start, end - start));

    std::ifstream file(p.path());

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string title = "";
    std::getline(buffer, title);

    std::string description = buffer.str().substr(title.size() + 1);

    Note note = {id, title, description};
    BN::notes_map[id] = note;
  }
  filtered_notes_map = notes_map;
}

Note *BN::GetNote(long id) {
  auto it = notes_map.find(id);
  return (it != notes_map.end()) ? &it->second : nullptr;
}

void BN::DeleteNote(long id) {
  auto it = notes_map.find(id);
  if (it != notes_map.end()) {
    notes_map.erase(it);
    std::string file_path = notes_path + "Note_" + std::to_string(id) + ".txt";
    remove(file_path.c_str());
  }
}

void BN::SaveNote(long id) {
  Note *note = BN::GetNote(id);
  if (note == nullptr) {
    return;
  }
  std::string path =
      BN::notes_path + "Note_" + std::to_string(note->id) + ".txt";
  std::ofstream file(path);
  file << note->title << "\n";
  file << note->description;
  file.close();
}

void BN::Search(const std::string &query) {
  filtered_notes_map.clear();
  for (const auto &[id, note] : notes_map) {
    if (note.title.find(query.c_str()) != std::string::npos ||
        note.description.find(query.c_str()) != std::string::npos) 
    {
      filtered_notes_map[id] = note;
    }
  }
}

void BN::ClearSearch()
{
  filtered_notes_map = notes_map;
}

long BN::GetTimeInmillis() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

int BN::InputTextCallback(ImGuiInputTextCallbackData *data) {
  if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
    std::string *str = (std::string *)data->UserData;
    str->resize(data->BufTextLen);
    data->Buf = str->empty() ? nullptr : &(*str)[0];
  }
  return 0;
}
