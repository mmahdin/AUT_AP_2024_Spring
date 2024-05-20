#ifndef CAPPUCCINO
#define CAPPUCCINO

#include <string>
#include <vector>

#include "espresso_based.h"
#include "sub_ingredients.h"

class Cappuccino : public EspressoBased {
 public:
  Cappuccino();
  Cappuccino(const Cappuccino& cap);
  ~Cappuccino();
  void operator=(const Cappuccino& cap);

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

#endif  // CAPPUCCINO