
#include <iostream>
#include "SDL2/SDL.h"

int fib(int n) {
   if (n<=1) return n;
   return fib(n-1)+fib(n-2);
}

int main(int, char**) {

   if (SDL_Init(SDL_INIT_TIMER) != 0) std::exit(0);

   std::cout << "Timer test" << std::endl;

   Uint32 ticks{SDL_GetTicks()};
   Uint64 count{SDL_GetPerformanceCounter()};
   Uint64 freq{SDL_GetPerformanceFrequency()};

   std::cout << "SDL_GetTicks(): " << ticks << std::endl;
   std::cout << "SDL_GetPerformanceCounter(): " << count << std::endl;
   std::cout << "SDL_GetPerformanceFrequency(): " << freq << std::endl;
   const int x{fib(40)}; std::cout << "fib(40): " << x << std::endl;
   std::cout << "Elasped [SDL_GetTick]: " << (SDL_GetTicks()-ticks)/1000.0f << " secs\n";
   std::cout << "Elasped [SDL_GetPerformanceCounter]: "
      << (SDL_GetPerformanceCounter()-count)/float(SDL_GetPerformanceFrequency()) << " secs\n";

   return 0;
}

