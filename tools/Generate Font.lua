function readAll(file)
    local f = assert(io.open(file, "rb"), "Unable to find " .. file)
    local content = f:read("*a")
    f:close()
    return content
end

local characters = " !?'0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

local offset = 0
local bank = 0
local data = Dialog():entry{
    id = "offset_value",
    label = "Offset:",
    text = "0"
}:entry{
    id = "bank_value",
    label = "Bank:",
    text = "0"
}:button{
    id = "ok",
    text = "Generate"
}:button{
    id = "cancel",
    text = "Cancel"
}:show().data

if data.ok then
    offset = data.offset_value - 1
    offset = data.bank_value
else
    do
        return
    end
end

folder_root = app.fs.filePath(app.activeSprite.filename) .. "\\..\\"
font_chars = {}
font_index = 1
local spr = app.activeSprite
if not spr then
    app.alert("There is no sprite to export")
    return
end

for _,layer in ipairs(spr.layers) do

    for i = 1, (layer:cel(1).bounds.height // 8) + 1 do
        for j = 1, (layer:cel(1).bounds.width // 8) + 1 do

            sprite_data = ""
            has_char = false
            total_upper = 0
            total_lower = 0

            for y = 1, 8 do

                upper = 0
                lower = 0
                for x = 1, 8 do
                    color = layer:cel(1).image:getPixel(((j - 1) * 8) + (x - 1),
                                ((i - 1) * 8) + (y - 1))
                    
                    if color == 1 then 
                        has_char = true
                        upper = upper + (2 ^ (8 - x))
                        lower = lower + (2 ^ (8 - x))
                        total_lower = total_lower + lower
                        total_upper = total_upper + upper

                    end
                end
                sprite_data = sprite_data .. "0x" .. ('%02X'):format(upper) .. ",0x" ..
                                    ('%02X'):format(lower) .. ","

                if y == 4 then
                    sprite_data = sprite_data .. "\n\t"
                end
            end
            
            if font_index == 1 or has_char then
                font_chars[font_index] = sprite_data
                font_index = font_index + 1
            end
        end
    end
end

tiles_h_template = readAll(folder_root .. "res\\templates\\tiles_template.h")
tiles_c_template = readAll(folder_root .. "res\\templates\\tiles_template.c")

tiles_h_template = tiles_h_template:gsub("#NAME#", "font")
tiles_c_template = tiles_c_template:gsub("#NAME#", "font")
tiles_h_template = tiles_h_template:gsub("#BANK#", bank)
tiles_c_template = tiles_c_template:gsub("#BANK#", bank)

tiles_h_template = tiles_h_template:gsub("#LAYER_INDEX#", bank)

tiles_h_template = tiles_h_template:gsub("#LENGTH#", font_index - 1)

local sprite_str = ""

for c_i,char in pairs(font_chars) do

    local char_name = characters:sub(c_i,c_i)
    if char_name == " " then
        char_name = "{space}"
    end

    sprite_str = sprite_str .. "\t//" .. char_name .. " - " .. c_i  .. "\n\t" .. char .. "\n"
end

tiles_c_template = tiles_c_template:gsub("#SPRITES#", sprite_str)


tiles_h_file = io.open(folder_root .. "res\\ui\\font.h", "w")
tiles_c_file = io.open(folder_root .. "res\\ui\\font.c", "w")

tiles_c_file:write(tiles_c_template)
tiles_h_file:write(tiles_h_template)

tiles_c_file:close()
tiles_h_file:close()