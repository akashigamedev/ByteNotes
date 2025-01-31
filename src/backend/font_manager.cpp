#include "imgui.h"
#include<font_manager.h>
#include<icons.h>
#include <string>
#include <memory>

BN::FontManager::FontManager() : io(ImGui::GetIO()) {}

void BN::FontManager::LoadDefaultFont()
{

  const std::string build_dir = std::string(BUILD_DIR);

  const std::string ubuntu_regular_path = build_dir + std::string("/assets/fonts/ubuntu/Ubuntu-Regular.ttf");
  const std::string ubuntu_bold_path    = build_dir + std::string("/assets/fonts/ubuntu/Ubuntu-Bold.ttf");
  const std::string lucide_icon_path    = build_dir + std::string("/assets/fonts/lucide/lucide.ttf");
  
  ImFontConfig lucide_icon_config;
  lucide_icon_config.PixelSnapH = true;
  lucide_icon_config.MergeMode = true;
  static const ImWchar lucide_icon_ranges[] = { ICON_MIN_LC, ICON_MAX_16_LC , 0 };

  this->fonts[FontType::Ubuntu_Regular_16] = std::unique_ptr<ImFont>(io.Fonts->AddFontFromFileTTF(ubuntu_regular_path.c_str(), 16.0f));
  this->fonts[FontType::Ubuntu_Regular_18] = std::unique_ptr<ImFont>(io.Fonts->AddFontFromFileTTF(ubuntu_regular_path.c_str(), 18.0f));
  this->fonts[FontType::Ubuntu_Bold_16]    = std::unique_ptr<ImFont>(io.Fonts->AddFontFromFileTTF(ubuntu_bold_path.c_str(),    16.0f));
  this->fonts[FontType::Ubuntu_Bold_18]    = std::unique_ptr<ImFont>(io.Fonts->AddFontFromFileTTF(ubuntu_bold_path.c_str(),    18.0f));
  this->fonts[FontType::Ubuntu_Bold_32]    = std::unique_ptr<ImFont>(io.Fonts->AddFontFromFileTTF(ubuntu_bold_path.c_str(),    32.0f));
  this->fonts[FontType::Lucide_Icon_16]    = std::unique_ptr<ImFont>(io.Fonts->AddFontFromFileTTF(lucide_icon_path.c_str(),    16.0f, &lucide_icon_config, lucide_icon_ranges));
 
  this->io.Fonts->Build();
}

ImFont* BN::FontManager::GetFont(const FontType &type) const
{
  auto it = fonts.find(type);
  if(it != fonts.end())
  {
    return it->second.get();
  }
  else return nullptr;
}
