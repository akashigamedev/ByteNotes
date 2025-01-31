#include <bn.h>
#include <imgui.h>
#include <string> 
#include <icons.h>

void BN::LoadDefaultFont(ImGuiIO& io) {
  io.Fonts->AddFontDefault();
  
  ImFontConfig config;
  config.OversampleH = 3;
  config.OversampleV = 3;
  config.PixelSnapH = true;
  config.MergeMode = true;
  const std::string file_path = std::string(BUILD_DIR) + std::string("/assets/fonts/lucide.ttf");

  static const ImWchar icons_ranges[] = { ICON_MIN_LC, ICON_MAX_16_LC , 0 };

  ImFont* font = io.Fonts->AddFontFromFileTTF(file_path.c_str(), 16.0f, &config, icons_ranges);
}
