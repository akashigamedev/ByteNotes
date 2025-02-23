#include <imgui.h>
#include <note.h>
#include <string>
#include <unordered_map>

namespace BN {
static const std::string notes_path = BUILD_DIR + std::string("/notes/");
static std::unordered_map<long, Note> notes_map;
static std::unordered_map<long, Note> filtered_notes_map;
static long selected_id = -1;

const std::unordered_map<long, Note> &GetNotesMap();
const std::unordered_map<long, Note> &GetFilteredNotesMap();
void LoadNotesInMap();
long CreateNewNote();
Note *GetNote(long id);
void DeleteNote(long id);
void SaveNote(long id);
void Search(const std::string &query);
void ClearSearch();
long GetTimeInmillis();

int InputTextCallback(ImGuiInputTextCallbackData *data);
} // namespace BN
