

#include <iostream>
#include "sol/sol.hpp"

int main() {

   std::cout << "=== opening a state ===" << std::endl;

   sol::state lua;
   lua.open_libraries(sol::lib::base, sol::lib::package);
   lua.script("print('bark bark bark!')");
   std::cout << std::endl;
   return 0;
}


