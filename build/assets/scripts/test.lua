--test.lua

scaleSpeed = 50
currSpeed = scaleSpeed
maxScale = 100

function update(entity)

    entity.scale.x = entity.scale.x + currSpeed * GetFrameTime()
    entity.scale.y = entity.scale.y + currSpeed * GetFrameTime()

    if entity.scale.x >= maxScale then
        currSpeed = -scaleSpeed
    end
    if entity.scale.x <= 0 then
        currSpeed = scaleSpeed
    end
    
    if entity.scale.y >= maxScale then
        currSpeed = -scaleSpeed
    end
    if entity.scale.y <= 0 then
        currSpeed = scaleSpeed
    end

end

function render()
    -- render
end

function dispose()
    -- dispose
end