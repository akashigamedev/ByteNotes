#pragma once
#include <imgui.h>
#include <memory>
#include <unordered_map>

namespace BN {
enum FontType {
  Ubuntu_Regular_16,
  Ubuntu_Regular_18,
  Ubuntu_Bold_16,
  Ubuntu_Bold_18,
  Ubuntu_Bold_32,
  Lucide_Icon_16
};

class FontManager {
private:
  std::unordered_map<FontType, std::unique_ptr<ImFont>> fonts;
  ImGuiIO &io;

public:
  FontManager();
  void LoadDefaultFont();
  ImFont* GetFont(const FontType &type) const;
};
} // namespace BN
