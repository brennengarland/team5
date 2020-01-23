
--
-- Lua-based game logic
-- read this script (using sol2) and call the update() function
-- on each iteration of the game loop's C++-based update()
--
count = 0

function update()
   count = count + 1
   return count
   end
