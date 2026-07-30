print("[ErrorStorm] loaded")
local n = 0
RegisterHook("/Script/Engine.PlayerController:ServerRestartPlayer", function(self)
    n = n + 1
    if n % 2 == 1 then
        local ok, err = pcall(function() error("errorstorm callback failure", 0) end)
        if not ok then print("[ErrorStorm] pcall caught: " .. tostring(err)) end
    end
end)
LoopAsync(1000, function()
    local ok, err = pcall(function() error("errorstorm async failure", 0) end)
    if not ok then print("[ErrorStorm] async caught: " .. tostring(err)) end
    return false
end)
ExecuteWithDelay(1000, function()
    local ok, err = pcall(function() error("errorstorm delayed failure", 0) end)
    if not ok then print("[ErrorStorm] delayed caught: " .. tostring(err)) end
    print("[ErrorStorm] about to throw unprotected")
    error("errorstorm unprotected-after-pcall", 0)
end)
print("[ErrorStorm] armed")
