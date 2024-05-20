#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H

#include <vector>

#include "ingredient.h"

class EspressoBased {
 public:
  virtual std::string get_name() = 0;
  virtual double price() = 0;

  void brew();
  std::vector<Ingredient*>& get_ingredients();

  ~EspressoBased();

 protected:
  EspressoBased();
  EspressoBased(const EspressoBased& esp);
  void operator=(const EspressoBased& esp);

  std::vector<Ingredient*> ingredients;
  std::string name;
};

// EspressoBased::~EspressoBased() {
//   for (const auto& i : ingredients) delete i;
//   ingredients.clear();
// }

#endif  // ESPRESSO_BASED_H