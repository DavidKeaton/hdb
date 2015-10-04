--[[------------------------------------------------------------------------
Author: Tiago Dionizio (tngd@mega.ist.utl.pt)
$Id: requirelib.lua,v 1.1 2004/07/22 19:13:42 tngd Exp $
----------------------------------------------------------------------------
helper to load a shared module - see below for more information
--]]------------------------------------------------------------------------

--[[------------------------------------------------------------------------
locate module name in LUALIB_PATH
entries in LUALIB_PATH are separated by ';'
--]]------------------------------------------------------------------------
local function locate (name)
    local path = LUALIB_PATH
    if type (path) ~= "string" then
        path = os.getenv "LUALIB_PATH" or "./?;./?.so;./?.dll"
    end
    for path in string.gfind (path, "[^;]+") do
        path = string.gsub (path, "?", name)
        local f = io.open(path, "r")
        if (f) then
            f:close()
            return path
        end
    end
    return nil
end

--[[------------------------------------------------------------------------
load a shared module present in the LUALIB_PATH directory entries

name    : name of the file (module)
fun_name: name of the exported C function in the library
load    : if true, calls the function right away, throwing an error message
          in case of error returning any value returned by the function

if load is false, it returns the values returned by the loadlib function

if the file was not found, an error message is thrown
--]]------------------------------------------------------------------------
function requirelib(name, fun_name, load)
    local path = locate(name)
    if (path) then
        local l, msg, stage = loadlib(path, fun_name)
        if (load) then
            if (not l) then
                error(msg..' ['..stage..']')
            end
            return l()
        end
        return l, msg, stage
    end
    error("file module not found - "..name)
end
