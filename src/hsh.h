/*
 * =====================================================================================
 *
 *       Filename:  hsh.h
 *
 *    Description:  Hacker's SHell
 *
 *        Created:  10/07/2015 02:47:16 PM
 *
 *         Author:  David Keaton (davek), DavekDOS@gmail.com
 *
 * =====================================================================================
 */

#ifndef  HSH_INC
#define  HSH_INC

enum ERROR_TYPE {
	E_NOPARAM = 0,
	NUM_ERROR
};

const char *e_msg[NUM_ERROR] = {
	"expected parameter for [%s], but got nothing!"
};

int e_code[NUM_ERROR] = {
	2,		// E_NOPARAM
};


#endif   /* ----- #ifndef HSH_INC  ----- */
/* vim: set ft=c : */
