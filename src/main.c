/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Program startup!
 *
 *        Created:  10/07/2015 02:47:22 PM
 *
 *         Author:  David Keaton (davek), DavekDOS@gmail.com
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdarg.h>

#include <curses.h>

#include "hsh.h"
#include "options.h"


/* parse the command line options passed in */
int parse_args(int argc, char **argv);
/* add tabs to a buffer */
void tabulate(char *dest, unsigned int len, char *src, int amount);
/* print the program usage */
void usage(void);
/* return the index into `options' that `str' refers to */
int index_from_arg(const char *str);
/* display error message according to ERROR_TYPE given */
int error(enum ERROR_TYPE etype, const char * fmt, ...);

int main(int argc, char **argv)
{
	if(parse_args(argc, argv)) {
		// TODO: usage?
		exit(2);
	}
	exit(0);
}

int parse_args(int argc, char **argv)
{
	while(--argc > 0) {
		int idx = index_from_arg(*(++argv));
		if(idx == -1) {
			// invalid index for argument, chances are it isn't one
			return ERR;
		}
		struct opt_t *opt = &options[idx];
		if(opt->type == ARG_NULL) {
			break;
		} else {
			switch(opt->type) {
				case ARG_STRING:
					if(--argc > 0) {
						strncpy(opt->where, *(++argv), PATH_MAX);
					} else {
						error(E_NOPARAM, *argv);
					}
					break;
				case ARG_INTEGER:
					*((int *)opt->where) = atoi(*(++argv));
					break;
				case ARG_BOOLEAN:
					*((int *)opt->where) = (strcmp("+", *(argv++)) != 0);
					break;
				default:
					return ERR;
			}
		}
	}
	return OK;
}

void tabulate(char *dest, unsigned int len, char *src, int amount)
{
}
 
void usage(void)
{
	int pos = 0;
	// standard terminal width
	const int len = 80;
	char msg[len];
	// print usage header
	printf("Usage: hsh [options] [<program>]\n");
	memset(msg, 0, sizeof(msg));
	// show options and their descriptions
	for(int i = 0; options[i].type != ARG_NULL; ++i) {
		struct opt_t *o = &options[i];
		char *p	= msg + pos;
		int n = len - pos;
		// sname + lname
		char *name = (o->sname && !o->lname) ? o->sname :
			(o->lname && !o->sname) ? o->lname : NULL;
		if(name) {
			snprintf(p, n, "%s", name);
			pos += strlen(name);
		} else {
			snprintf(p, n, "%s,%s", o->sname, o->lname);
			pos += (1 + strlen(o->sname) + strlen(o->lname));
		}
	}
}

int index_from_arg(const char *str)
{
	assert(str != NULL);

	for(int i = 0; options[i].type != ARG_NULL; ++i) {
		if(strcmp(options[i].sname, str) == 0 
		|| strcmp(options[i].lname, str) == 0) {
			return i;
		}
	}
	// no results found, drop invalid index
	return -1;
}

int error(enum ERROR_TYPE etype, const char *fmt, ...)
{
	const char *msg = (fmt == NULL) ? e_msg[etype] : fmt;
	va_list va;
	va_start(va, fmt);
	vfprintf(stderr, msg, va);
	va_end(va);
	return e_code[etype];
}
