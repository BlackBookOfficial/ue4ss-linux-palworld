print("[LuaStress] loaded")
LoopAsync(1, function()
    local t = {}
    for i = 1, 300 do t[#t + 1] = ("x"):rep(i % 32 + 1) .. i end
    return false
end)
local function spin()
    local acc = 0
    for i = 1, 200 do acc = acc + #tostring(i * (acc + 1)) end
    ExecuteInGameThread(spin)
end
ExecuteInGameThread(spin)
print("[LuaStress] armed")
