--[[------------------------------------------------------------------------
curses.lua
support code for curses library
usage lua -lcurses ...

Author: Tiago Dionizio (tngd@mega.ist.utl.pt)
$Id: curses.lua,v 1.4 2004/07/22 19:13:42 tngd Exp $
--]]------------------------------------------------------------------------

--[[ Documentation ---------------------------------------------------------



--]]------------------------------------------------------------------------

require('requirelib')

curses = requirelib('lcurses', 'luaopen_curses', true)
