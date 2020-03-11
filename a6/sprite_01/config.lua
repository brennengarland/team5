

assets = {}
assets["tank-image"] = "../assets/images/tank-big-right.png"
assets["chopper-image"] = "../assets/images/chopper-spritesheet"

entities = {}
entities["tank"] = {
   transform = { position_x = 0,  position_y = 0,
                 velocity_x = 20, velocity_y = 20,
                 width = 32, height = 32, scale = 1 },
   sprite =    { texture_id = "tank-image" }
}
entities["chopper"] = {
   transform = { position_x = 240, position_y= 106,
                 velocity_x = 0,   velocity_y = 0,
                 width = 32, height = 32, scale = 1 },
   sprite =    { texture_id = "chopper-image" }
}

function print_assets_table(tbl)
   print("-----------------------")
   print("Printing Assets Table")
   print("-----------------------")
   for k, filename in pairs(tbl) do
      print(k, "filename: " .. filename)
   end
end

function print_entities_table(tbl)
   print("-----------------------")
   print("Printing Entities Table")
   print("-----------------------")
   for name, entity in pairs(tbl) do
      print("entity name: " .. name)
      for name, component in pairs(entity) do
         print("  component name: " .. name)
         for attribute, value in pairs(component) do
            print("    " .. attribute, value)
         end
      end
   end
end

print("===================")
print("Config.lua Contents")
print("===================")
print_assets_table(assets)
print()
print_entities_table(entities)

