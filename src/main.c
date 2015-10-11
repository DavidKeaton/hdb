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

#include <curses.h>

#include "hsh.h"
#include "options.h"


/* parse the command line options passed in */
int parse_args(int argc, char **argv);
/* return the index into `options' that `str' refers to */
int index_from_arg(const char *str);
/* turn a string from any case to lower case */
void lowercase(char *dest, const char *str, unsigned int len);

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
		int idx = index_from_arg(*(argv++));
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
					strncpy(opt->where, *(argv++), PATH_MAX);
					break;
				case ARG_INTEGER:
					*((int *)opt->where) = atoi(*(argv++));
					break;
				case ARG_BOOLEAN: {
					char lc[16]; // nice even size
					lowercase(lc, *argv, 16);
					if((strcmp(lc, "true") == 0)) {
						*((int *)opt->where) = TRUE;
					} else if((strcmp(lc, "false") == 0)) {
						*((int *)opt->where) = FALSE;
					} else { // invalid response
						*((int *)opt->where) = -1;
					}
					break;
				}
				default:
					return ERR;
			}
		}
	}
	return OK;
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

void lowercase(char *dest, const char *str, unsigned int len)
{
	assert(dest != NULL);
	assert(str != NULL);

	memset(dest, 0, len);
	for(int i = 0; i < len; ++i) {
		dest[i] = tolower(str[i]);
	}
}
