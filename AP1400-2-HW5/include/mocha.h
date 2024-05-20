#ifndef MOCHA_H
#define MOCHA_H

#include <string>
#include <vector>

#include "espresso_based.h"
#include "sub_ingredients.h"

class Mocha : public EspressoBased {
 public:
  Mocha();
  Mocha(const Mocha& cap);
  ~Mocha();
  void operator=(const Mocha& cap);

  virtual std::string get_name();
  virtual double price();

  void add_side_item(Ingredient* side);
  std::vector<Ingredient*>& get_side_items();

 private:
  std::vector<Ingredient*> side_items;
  unsigned* cnt;
  void release() {
    if (cnt) {
      if (--(*cnt) == 0) {
        for (auto& item : side_items) delete item;
        side_items.clear();
        for (const auto& i : ingredients) delete i;
        ingredients.clear();
        delete cnt;
      }
    }
    cnt = nullptr;
  }
};

#endif  // MOCHA_H