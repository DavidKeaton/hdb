/*
 * =====================================================================================
 *
 *       Filename:  options.h
 *
 *    Description:  Argument definitions for `hsh' invocation
 *
 *        Created:  10/07/2015 02:49:33 PM
 *
 *         Author:  David Keaton (davek), DavekDOS@gmail.com
 *
 * =====================================================================================
 */

#ifndef  OPTIONS_INC
#define  OPTIONS_INC

#include "const.h"

struct settings_t {
	int verbose;					// verbosity of program
	char config[PATH_MAX];			// config file to use
	char session[PATH_MAX];			// session information
};

struct settings_t settings;

enum arg_type {
	ARG_NULL = 0,
	ARG_BOOLEAN,
	ARG_INTEGER,
	ARG_STRING
};

// describes program option
struct opt_t {
	enum arg_type type;				// what type of param does it have?
	char *sname;					// short name of the argument
	char *lname;					// long name of the argument
	char *vname;					// value name/type (optional)
	void *where;					// where to store the value
	char *desc;						// description of the argument
};

struct opt_t options[] = {
/*	  arg type	  shortname	  longname		 value name		 where|description */
	{ARG_BOOLEAN,	"-v",	"--verbose",		NULL,		&settings.verbose,
		"increase the verbosity"},
	{ARG_STRING,	"-c",	"--config",			"<file>",	&settings.config,
		"load config <file> instead of default"},
	{ARG_STRING,	"-S",	"--session",		"<file>",	&settings.session,
		"load session from <file>"},
	{ARG_NULL,		"-s",	"--silent",			NULL,		NULL,
		"decrease program output"},
	{ARG_NULL,		"",	"",			"",		"", ""},
	{ARG_NULL,		"",	"",			"",		"", ""},
	{ARG_NULL,		"",	"",			"",		"", ""},
	{ARG_NULL,		"",	"",			"",		"", ""},
	{ARG_NULL,		"",	"",			"",		"", ""},
	{ARG_NULL,		"",	"",			"",		"", ""},
	{ARG_NULL,		"",	"",			"",		"", ""},
	{ARG_NULL,		"",	"",			"",		"", ""},
	{ARG_NULL,		"",	"",			"",		"", ""},
};

#endif   /* ----- #ifndef OPTIONS_INC  ----- */
/* vim: set ft=c : */
