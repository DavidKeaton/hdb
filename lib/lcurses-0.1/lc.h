#ifndef  LC_INC
#define  LC_INC

#include <string.h>

#include <lua.h>
#include <lauxlib.h>

#include <curses.h>
#include <panel.h>



/*
** =======================================================
** known 'issues' with PDCURSES library...
** =======================================================
*/
#if defined(PDCURSES)

/* incorretcly defined, missing return value (OK) */
/* in PDCURSES:
#define nl()                    (SP->autocr = TRUE)
#define nonl()                  (SP->autocr = FALSE)
*/
#undef nl
#undef nonl
#define nl()                    (SP->autocr = TRUE), OK
#define nonl()                  (SP->autocr = FALSE), OK

/* they are there... just not defined?? */
extern int has_ic(void);
extern int has_il(void);

/* PDCURSES doesn't seem to define these */
#if !defined(mvwgetnstr)
#define mvwgetnstr(win,y,x,buf,n)  (wmove(win,y,x) == ERR ? ERR : wgetnstr(win,buf,n))
#endif
#if !defined(mvwhline)
#define mvwhline(win,y,x,c,n)		(wmove(win,y,x) == ERR ? ERR : whline(win,c,n))
#endif
#if !defined(mvwvline)
#define mvwvline(win,y,x,c,n)		(wmove(win,y,x) == ERR ? ERR : wvline(win,c,n))
#endif

#endif /* defined(PDCURSES) */

/*
** =======================================================
** addon libraries
** =======================================================
*/
#define INCLUDEPANEL 1

#define PANELMETA           "curses:panel"
#define UPINDEX             lua_upvalueindex(1)

/* ======================================================= */

#define LCP_BOOLOK(n)                       \
    static int lcp_ ## n(lua_State *L)      \
    {                                       \
        PANEL *p = lcp_check(L, 1);         \
        lua_pushboolean(L, B(n(p)));        \
        return 1;                           \
    }

#define B(v) ((v == ERR) ? 0 : 1)

static const char *WINDOWMETA          = "curses:window";

/* pdcurses passes some variables as (char*) instead of
** (const char*)... bummer */
#if defined(PDCURSES)
#define CCHAR_CAST (char*)
#define CCHTYPE_CAST (chtype*)
#else
#define CCHAR_CAST
#define CCHTYPE_CAST
#endif

/* ======================================================= */

#define LC_NUMBER(v)                        \
    static int lc_ ## v(lua_State *L)       \
    {                                       \
        lua_pushnumber(L, v());             \
        return 1;                           \
    }

#define LC_NUMBER2(n,v)                     \
    static int lc_ ## n(lua_State *L)       \
    {                                       \
        lua_pushnumber(L, v);               \
        return 1;                           \
    }

/* ======================================================= */

#define LC_STRING(v)                        \
    static int lc_ ## v(lua_State *L)       \
    {                                       \
        lua_pushstring(L, v());             \
        return 1;                           \
    }

#define LC_STRING2(n,v)                     \
    static int lc_ ## n(lua_State *L)       \
    {                                       \
        lua_pushstring(L, v);               \
        return 1;                           \
    }

/* ======================================================= */

#define LC_BOOL(v)                          \
    static int lc_ ## v(lua_State *L)       \
    {                                       \
        lua_pushboolean(L, v());            \
        return 1;                           \
    }

#define LC_BOOL2(n,v)                       \
    static int lc_ ## n(lua_State *L)       \
    {                                       \
        lua_pushboolean(L, v);              \
        return 1;                           \
    }

/* ======================================================= */

#define LC_BOOLOK(v)                        \
    static int lc_ ## v(lua_State *L)       \
    {                                       \
        lua_pushboolean(L, B(v()));         \
        return 1;                           \
    }

#define LC_BOOLOK2(n,v)                     \
    static int lc_ ## n(lua_State *L)       \
    {                                       \
        lua_pushboolean(L, B(v));           \
        return 1;                           \
    }

/* ======================================================= */

#define LCW_BOOLOK(n)                       \
    static int lcw_ ## n(lua_State *L)      \
    {                                       \
        WINDOW *w = lcw_check(L, 1);        \
        lua_pushboolean(L, B(n(w)));        \
        return 1;                           \
    }


#ifdef DEBUG

#include <stdarg.h>
int clog(char* f, ...)
{
    va_list args;
    FILE *l;

    va_start(args, f);
    l = fopen("lcurses.log", "a");
    vfprintf(l, f, args);
    fclose(l);
    va_end(args);
    return 1;
}

#endif /* DEBUG */

static WINDOW **lcw_get(lua_State *L, int index)
{
    WINDOW **w = (WINDOW**)luaL_checkudata(L, index, WINDOWMETA);
    if (w == NULL) luaL_argerror(L, index, "bad curses window");
    return w;
}

static WINDOW *lcw_check(lua_State *L, int index)
{
    WINDOW **w = lcw_get(L, index);
    if (*w == NULL) luaL_argerror(L, index, "attempt to use closed curses window");
    return *w;
}
/*
** =======================================================
** panel
** =======================================================
*/
static PANEL **lcp_get(lua_State *L, int index)
{
    PANEL **p = (PANEL**)luaL_checkudata(L, 1, PANELMETA);
    if (p == NULL) luaL_argerror(L, index, "bad curses panel");
    return p;
}

static void lcp_new(lua_State *L, PANEL *np)
{
    if (np)
    {
        PANEL **p = (PANEL**)lua_newuserdata(L, sizeof(PANEL*));
        luaL_getmetatable(L, PANELMETA);
        lua_setmetatable(L, -2);
        *p = np;
    }
    else
    {
        lua_pushliteral(L, "failed to create panel");
        lua_error(L);
    }
}

static PANEL *lcp_check(lua_State *L, int index)
{
    PANEL **p = (PANEL**)luaL_checkudata(L, 1, PANELMETA);
    if (p == NULL) luaL_argerror(L, index, "bad curses panel");
    if (*p == NULL) luaL_argerror(L, index, "attempt to use closed curses panel");
    return *p;
}


static int lcp_tostring(lua_State *L)
{
    PANEL **p = lcp_get(L, 1);
    char buff[34];
    if (*p == NULL)
        strcpy(buff, "closed");
    else
        sprintf(buff, "%p", lua_touserdata(L, 1));
    lua_pushfstring(L, "curses panel (%s)", buff);
    return 1;
}
#endif   /* ----- #ifndef LC_INC  ----- */
