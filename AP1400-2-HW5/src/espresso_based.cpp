#include "espresso_based.h"

EspressoBased::~EspressoBased() {
  for (const auto& i : ingredients) delete i;
  ingredients.clear();
}