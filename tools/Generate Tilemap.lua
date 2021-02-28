function deepcopy(orig)
    local orig_type = type(orig)
    local copy
    if orig_type == 'table' then
        copy = {}
        for orig_key, orig_value in next, orig, nil do
            copy[deepcopy(orig_key)] = deepcopy(orig_value)
        end
        setmetatable(copy, deepcopy(getmetatable(orig)))
    else -- number, string, boolean, etc
        copy = orig
    end
    return copy
end


local is_test = false
local offset = 0
local data = Dialog():entry{
    id = "offset_value",
    label = "Offset:",
    text = "104"
}:check{
    id = "is_test_value",
    label = "Output to test folder?",
    text = "",
    selected = is_test,
    onclick = function()
        is_test = not is_test
    end
}:button{
    id = "ok",
    text = "Generate"
}:button{
    id = "cancel",
    text = "Cancel"
}:show().data

if data.ok then
    offset = data.offset_value - 1
else
    do
        return
    end
end

folder_root = app.fs.filePath(app.activeSprite.filename) .. "\\..\\"

if is_test then
    folder_root = folder_root .. ".tests\\autogen\\"
end

function readAll(file)
    local f = assert(io.open(file, "rb"), "Unable to find " .. file)
    local content = f:read("*a")
    f:close()
    return content
end

local spr = app.activeSprite
if not spr then
    app.alert("There is no sprite to export")
    return
end

layer_map = {}

for group_index, layer_group in ipairs(spr.layers) do

    if layer_group.isVisible then
        sprite_index = 1
        sprites = {}
        -- sprites[1] = "0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\n\t0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"
        sprite_lookup = {}
        -- sprite_lookup[sprites[1]] = "1"

        local layer_name, layer_bank = layer_group.name:match("([%w_]*).bank(%d*)")
        layer_map[layer_name] = {}
        layer_map[layer_name]["bank"] = layer_bank
        for _, attr_layer in ipairs(layer_group.layers) do
            if attr_layer.isGroup then
                for _, area in ipairs(attr_layer.layers) do

                    if area.isVisible then

                        local area_name, area_bank = area.name:match("([%w_]*).bank(%d*)")
                        layer_map[layer_name][area_name] = {}
                        layer_map[layer_name][area_name]["bank"] = area_bank
                        layer_map[layer_name][area_name]["x"] = area:cel(1).bounds.x // 8
                        layer_map[layer_name][area_name]["y"] = area:cel(1).bounds.y // 8
                        layer_map[layer_name][area_name]["w"] = area:cel(1).bounds.width // 8
                        layer_map[layer_name][area_name]["h"] = area:cel(1).bounds.height // 8

                        tile_map = {}
                        -- loop all cells in this area
                        for i = 1, area:cel(1).bounds.height // 8 do
                            for j = 1, area:cel(1).bounds.width // 8 do
                                sprite_data = ""

                                for y = 1, 8 do

                                    upper = 0
                                    lower = 0
                                    for x = 1, 8 do
                                        color = area:cel(1).image:getPixel(((j - 1) * 8) + (x - 1),
                                                    ((i - 1) * 8) + (y - 1))
                                        if color == 1 then
                                            -- white, skip
                                        elseif color == 2 then
                                            -- light grey, increase upper
                                            upper = upper + (2 ^ (8 - x))
                                        elseif color == 3 then
                                            -- dark grey, increase lower
                                            lower = lower + (2 ^ (8 - x))
                                        elseif color == 4 then
                                            -- black, increase both
                                            upper = upper + (2 ^ (8 - x))
                                            lower = lower + (2 ^ (8 - x))

                                        end
                                    end
                                    sprite_data = sprite_data .. "0x" .. ('%02X'):format(upper) .. ",0x" ..
                                                      ('%02X'):format(lower) .. ","

                                    if y == 4 then
                                        sprite_data = sprite_data .. "\n\t"
                                    end
                                end
                                -- app.alert(sprite_data)
                                -- do return end

                                if sprite_lookup[sprite_data] == nil then
                                    sprite_lookup[sprite_data] = sprite_index
                                    sprites[sprite_index] = sprite_data
                                    sprite_index = sprite_index + 1
                                end

                                -- do return end

                                table.insert(tile_map, ("0x" .. ('%02X'):format(sprite_lookup[sprite_data] + offset)))
                            end
                        end

                        layer_map[layer_name][area_name]["tilemap"] = tile_map

                    end
                end
            end
        end

        layer_map[layer_name]["sprites"] = deepcopy(sprites)
        layer_map[layer_name]["tile_count"] = sprite_index - 1
    end
end

layer_index = 0

map_area_items = ""
map_area_includes = ""

for layer_name, areas in pairs(layer_map) do
    print(layer_name .. " (" .. areas["tile_count"] .. " tiles)")
    -- file:write(layer_name .. "\n")
    tiles_h_template = readAll(folder_root .. "res\\templates\\tiles_template.h")
    tiles_c_template = readAll(folder_root .. "res\\templates\\tiles_template.c")

    tiles_h_template = tiles_h_template:gsub("#NAME#", layer_name)
    tiles_c_template = tiles_c_template:gsub("#NAME#", layer_name)
    tiles_h_template = tiles_h_template:gsub("#BANK#", areas["bank"])
    tiles_c_template = tiles_c_template:gsub("#BANK#", areas["bank"])
    
    tiles_h_template = tiles_h_template:gsub("#LAYER_INDEX#", layer_index)

    tiles_h_template = tiles_h_template:gsub("#LENGTH#", areas["tile_count"])

    col_count = 1
    tiles_sprites = ""
    for t_i, spr in pairs(areas["sprites"]) do
        tiles_sprites = tiles_sprites .. "\t//" .. t_i .. "\n" .. spr .. "\n"
    end

    tiles_sprites = tiles_sprites:sub(1, -2)

    tiles_c_template = tiles_c_template:gsub("#SPRITES#", tiles_sprites)

    tiles_h_file = io.open(folder_root .. "res\\tiles\\" .. layer_name .. ".h", "w")
    tiles_c_file = io.open(folder_root .. "res\\tiles\\" .. layer_name .. ".c", "w")

    local area_index = 0
    for i, v in pairs(areas) do
        if i ~= "bank" and i ~= "sprites" and i ~= "tile_count" then

            local name_length = string.len(i)
            local padding = 40 - name_length
            print("     - "..i .. string.format("%" .. padding .. "s", " ") .. "x:" .. v["x"] .. "   y:" .. v["y"] .. "   w:" ..
                      v["w"] .. "   h:" .. v["h"])

            map_area_item_template = readAll(folder_root .. "res\\templates\\map_area_item_template.c")

            map_area_item_template = map_area_item_template:gsub("#NAME#", i)
            map_area_item_template = map_area_item_template:gsub("#BANK#", v["bank"])
            map_area_item_template = map_area_item_template:gsub("#XS#", v["x"])
            map_area_item_template = map_area_item_template:gsub("#YS#", v["y"])
            map_area_item_template = map_area_item_template:gsub("#XE#", v["x"] + v["w"] - 1)
            map_area_item_template = map_area_item_template:gsub("#YE#", v["y"] + v["h"] - 1)
            map_area_item_template = map_area_item_template:gsub("#ROW_LENGTH#", v["w"])
            map_area_item_template = map_area_item_template:gsub("#LAYER#", layer_index)
            map_area_item_template = map_area_item_template:gsub("#AREA_INDEX#", area_index)

            map_area_items = map_area_items .. map_area_item_template .. "\n\t"
            map_area_includes = map_area_includes .. "\n" .. "#include \"../res/maps/" .. i .. "_map.h\""

            map_h_file = io.open(folder_root .. "res\\maps\\" .. i .. "_map.h", "w")
            map_c_file = io.open(folder_root .. "res\\maps\\" .. i .. "_map.c", "w")

            map_h_template = readAll(folder_root .. "res\\templates\\map_template.h")
            map_c_template = readAll(folder_root .. "res\\templates\\map_template.c")

            map_h_template = map_h_template:gsub("#NAME#", i)
            map_h_template = map_h_template:gsub("#BANK#", v["bank"])
            map_h_template = map_h_template:gsub("#OFFSET#", offset)
            map_h_template = map_h_template:gsub("#WIDTH#", v["w"])
            map_h_template = map_h_template:gsub("#HEIGHT#", v["h"])
            map_h_template = map_h_template:gsub("#AREA_INDEX#", area_index)

            map_c_template = map_c_template:gsub("#NAME#", i)
            map_c_template = map_c_template:gsub("#BANK#", v["bank"])
            map_c_template = map_c_template:gsub("#OFFSET#", offset)
            map_c_template = map_c_template:gsub("#WIDTH#", v["w"])
            map_c_template = map_c_template:gsub("#HEIGHT#", v["h"])

            tiles_str = "\t"
            for i, tile in ipairs(v["tilemap"]) do
                tiles_str = tiles_str .. tile .. ","
                if i % 8 == 0 then
                    tiles_str = tiles_str .. "\n\t"
                end
            end

            map_c_template = map_c_template:gsub("#TILES#", tiles_str)

            map_c_file:write(map_c_template)
            map_h_file:write(map_h_template)

            map_h_file:close()
            map_c_file:close()
            area_index = area_index + 1
        end

    end

    tiles_c_file:write(tiles_c_template)
    tiles_h_file:write(tiles_h_template)

    tiles_c_file:close()
    tiles_h_file:close()

    layer_index = layer_index + 1
end

map_area_file = io.open(folder_root .. "src\\map_area.c", "w")

map_area_template = readAll(folder_root .. "res\\templates\\map_area_template.c")

map_area_template = map_area_template:gsub("#MAP_AREA_ITEMS#", map_area_items)
map_area_template = map_area_template:gsub("#INCLUDES#", map_area_includes)
map_area_file:write(map_area_template)
map_area_file:close()
