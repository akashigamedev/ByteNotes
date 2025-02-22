#include <unordered_map>
#include <memory>
#include <string>
#include <imgui.h>
#include<note.h>

namespace BN
{
    static const std::string notes_path = BUILD_DIR + std::string("/notes/");
    static std::unordered_map<long, Note> notes_map;
    static long selected_id = -1;
    const std::unordered_map<long, Note> &GetNotesMap();

    void LoadNotesInMap();
    long CreateNewNote();
    Note *GetNote(long id);
    void DeleteNote(long id);
    void SaveNote(const Note *note);
    long GetTimeInmillis();

    int InputTextCallback(ImGuiInputTextCallbackData *data);
}