
#include "bn.h"
#include <fstream>
#include <chrono>
#include <iostream>


const std::unordered_map<long, Note> &BN::GetNotesMap()
{
    return notes_map;
}


long BN::CreateNewNote()
{
    long id = GetTimeInmillis();
    notes_map[id] = {id,"",""};
    selected_id = id;
    return id;
}

void BN::LoadNotesInMap()
{
    std::string filepath = "some_default_path";
    std::string title, content;

    std::ifstream file(filepath);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filepath << std::endl;
        return;
    }

    std::getline(file, title);

    std::string line;
    content.clear();
    while (std::getline(file, line))
    {
        content += line + "\n";
    }

    file.close();
}

Note *BN::GetNote(long id)
{
    auto it = notes_map.find(id);
    return (it != notes_map.end()) ? &it->second : nullptr;
}

void BN::DeleteNote(long id)
{
    auto it = notes_map.find(id);
    if (it != notes_map.end())
    {
        notes_map.erase(it);
        std::string file_path = notes_path + "Note_" + std::to_string(id) + ".txt";
        remove(file_path.c_str());
    }
}

void BN::SaveNote(const Note *note)
{
    std::string path = BN::notes_path + "Note_" + std::to_string(note->id) + ".txt";
    std::ofstream file(path);
    file << note->title << "\n";
    file << note->description;
    file.close();
}

long BN::GetTimeInmillis()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}


int BN::InputTextCallback(ImGuiInputTextCallbackData *data)
{
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
    {
        std::string *str = (std::string *)data->UserData;
        str->resize(data->BufTextLen);
        data->Buf = str->empty() ? nullptr : &(*str)[0];  
    }
    return 0;
}