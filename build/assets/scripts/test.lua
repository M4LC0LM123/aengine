--test.lua

scaleSpeed = 50
currSpeed = scaleSpeed
maxScale = 100

pos = nil
scale = nil
rotation = nil
-- color = nil
-- color.r = 0
-- color.g = 255
-- color.b = 0
-- color.a = 255

function update(entity)
    pos = entity.pos
    scale = entity.scale
    rotation = entity.rotation

    entity.rotation.z = entity.rotation.z  + currSpeed * GetFrameTime()

    entity.scale.x = entity.scale.x + currSpeed * GetFrameTime()
    entity.scale.y = entity.scale.y + currSpeed * GetFrameTime()

    if entity.scale.x >= maxScale then
        currSpeed = -scaleSpeed
    end
    if entity.scale.x <= -100 then
        currSpeed = scaleSpeed
    end
    
    if entity.scale.y >= maxScale then
        currSpeed = -scaleSpeed
    end
    if entity.scale.y <= -100 then
        currSpeed = scaleSpeed
    end

end

function render()
    -- render
end

function dispose()
    -- dispose
end