function reset()
    time = 0
    money = 0
    level = 1
    clicks = 0
    interval = 1
end

function love.load()
    math.randomseed(os.time())
    love.graphics.setDefaultFilter("nearest", "nearest")
    backgroundsky = love.graphics.newImage("images/background.png")
    backgroundhills = love.graphics.newImage("images/terrain.png")
    background = love.graphics.newImage("images/ground")
    level1 = love.graphics.newImage("images/level1.png")
    level2 = love.graphics.newImage("images/level2.png")
    level3 = love.graphics.newImage("images/level3.png")
    level4 = love.graphics.newImage("images/level4.png")
    level5 = love.graphics.newImage("images/level5.png")
    level6 = love.graphics.newImage("images/level6.png")
    music = love.audio.newSource("music/rumble.mp3", "stream")
    music:setLooping(true)
    musix = love.audio.newSource("music/jazz.ogg", "stream")
    musix:setLooping(true)
    upgrade1 = love.graphics.newImage("images/upgrade-sign1.png")
    upgrade2 = love.graphics.newImage("images/upgrade-sign2.png")
    upgrade3 = love.graphics.newImage("images/upgrade-sign3.png")
    upgrade4 = love.graphics.newImage("images/upgrade-sign4.png")
    upgrade5 = love.graphics.newImage("images/upgrade-sign5.png")
    splash = love.graphics.newImage("images/splashscreen.png")
    playing = false
    time = 0
    money = 0
    if math.random(1, 2) == 1 then
        music:play()
    else
        musix:play()
    end
    level = 1
    clicks = 0
    interval = 1
    Font = love.graphics.newFont("fonts/freesansbold.ttf", 35)
    love.graphics.setFont(Font)
end

function love.update(dt)
    if playing then
        time = time + dt
        if time >= interval and clicks >= (level * 4) then
            clicks = clicks - level * 4
            interval = 0.8
            money = money + level
            time = 0
        end
    end
end

function love.mousepressed(x, y, button)
    if playing then
        if button == 1 then
            if x > 150 and x < 650 then
                if y > 220 and y < 600 then
                    clicks = clicks + level
                end
            end
            if x > 250 and x < 550 then
                if y > 50 and y < 100 then
                    if level == 1 then
                        if money >= 70 then
                            level = level + 1
                            money = money - 70
                        end
                    end
                    if level == 2 then
                        if money >= 140 then
                            level = level + 1
                            money = money - 140
                        end
                    end
                    if level == 3 then
                        if money >= 210 then
                            level = level + 1
                            money = money - 210
                        end
                    end
                    if level == 4 then
                        if money >= 280 then
                            level = level + 1
                            money = money - 210
                        end
                    end
                    if level == 5 then
                        if money >= 350 then
                            level = level + 1
                            money = money - 350
                        end
                    end
                end
            end
        end
    end
end

function love.draw()
    love.graphics.draw(backgroundsky, 0, 0, 0, 10)
    love.graphics.draw(backgroundhills, 0, 400, 0, 10)
    love.graphics.draw(background, 0, 500, 0, 10)
    if playing then
        love.graphics.print("Stock: "..clicks, 5, 5)
        local text = "Funds: "..money
        love.graphics.print(text, 800 - Font:getWidth(text) - 5, 5)
        if level == 1 then
            love.graphics.draw(level1, 150, 220, 0, 10)
            love.graphics.draw(upgrade1, 250, 50, 0, 5, 5)
        elseif level == 2 then
            love.graphics.draw(level2, 150, 220, 0, 10)
            love.graphics.draw(upgrade2, 250, 50, 0, 5, 5)
        elseif level == 3 then
            love.graphics.draw(level3, 150, 220, 0, 10)
            love.graphics.draw(upgrade3, 250, 50, 0, 5, 5)
        elseif level == 4 then
            love.graphics.draw(level4, 150, 220, 0, 10)
            love.graphics.draw(upgrade4, 250, 50, 0, 5, 5)
        elseif level == 5 then
            love.graphics.draw(level5, 150, 220, 0, 10)
            love.graphics.draw(upgrade5, 250, 50, 0, 5, 5)
        elseif level == 6 then
            love.graphics.draw(level6, 150, 220, 0, 10)
        end
    else
        love.graphics.draw(splash, 2, 2, 0, 10)
    end
end
function love.keypressed(k)
    if k == 'escape' then
       love.event.quit()
    end
    if k == "space" then
        if playing then
            reset()
        else
            playing = true  
        end
    end
end
