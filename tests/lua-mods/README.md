# Regression Test Mods (Lua)

E2E Lua mods used to verify UE4SS-Linux behavior against a live Palworld
server. Deploy by copying a mod directory into `<server>/Mods/` and enabling
it in `Mods/mods.txt`, then restart and read `UE4SS.log`.

## ErrorStorm

Verifies the Lua error-handling contract on Linux:

1. Protected errors (`pcall`) inside a `RegisterHook` callback — logged and
   swallowed by the mod.
2. Errors inside `LoopAsync` iterations (mod thread) — logged.
3. Errors inside delayed one-shot actions — logged.
4. **Unprotected** error from a delayed action — must NOT crash the server:
   expected log line
   `[DelayedAction] [Lua::call_function] lua_pcall returned LUA_ERRRUN => ...`
   with a Lua traceback, and the server stays up.

History: before the value-returning error seam
(`LuaMadeSimple::Lua::call_function_report`), stage 4 crashed the process —
the C++ exception could not safely travel through the exception machinery in
a process whose executable vendors a different C++ runtime (see
`UE4SS-PALWORLD-LINUX-STATUS.md`, "Lua error handling").

## LuaStress

Verifies Lua thread safety under real contention:

- `LoopAsync` performing continuous table/GC churn on the mod thread.
- A self-requeueing `ExecuteInGameThread` callback executing Lua on the game
  thread every engine tick.

Both threads share the mod's `lua_State` global state. Before the
process-wide recursive `m_thread_actions_mutex` coverage, this was an
unprotected data race. Expected: 118+ FPS sustained, stable RSS, no
SIGSEGV/SIGABRT in `UE4SS-stderr.log` over a multi-minute soak.
