/*
 * =====================================================================================
 *
 *       Filename:  term.h
 *
 *    Description:  hsh shell interface
 *
 *        Created:  10/07/2015 02:23:41 PM
 *
 *         Author:  David Keaton (davek), DavekDOS@gmail.com
 *
 * =====================================================================================
 */

#ifndef  TERM_INC
#define  TERM_INC

// initialize and start the shell
int sh_start(void);
// main() equivalent for shell itself
int sh_run(void);
// close and cleanup shell
int sh_stop(void);


#endif   /* ----- #ifndef TERM_INC  ----- */
