/*
 *
 * wes
 * A simple b-tree tokenizer for educational purposes
 * Copyright © 2005-2013 Alejandro Ricoveri <alejandroricoveri@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

/* Basic definitions */

// Argument flags
#define WES_ARG_VERBOSE 1 << 0
#define WES_ARG_HELP    1 << 1
#define WES_ARG_VERSION 1 << 2

// wes_error as a variadic macro
#define wes_error(fmt, ...) \
      __wes_err(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

// Limits
#define WES_MAX_COLS        8192
#define WES_MAX_LINES       UINT16_MAX
#define WES_MAX_TOKEN_SIZE  128
#define WES_TOKEN_DELIMIT " .,;-\n\t"

// Packaging information
#define WES_NAME "wes"
#define WES_VER_MAJOR 0
#define WES_VER_MINOR 1

/*
 * Type definitions
 */

/*
 * Each token holds a line list
 * which hold a line number
 * and the number of ocurrences
 * for the token on that line
 */
typedef struct _line_t
{
    // line number
    uint16_t number;
    
    // Number of ocurrences 
    uint8_t times;
    
    // Next line in the list
    struct _line_t *next;
} line_t;

/*
 * Each new found token is hold by
 * instances of token_t
 */
typedef struct _token_t
{
    // The actual string
    char *str;
    
    // a linked list of the lines where this token was found
    line_t  *lines;
    
    // left wing children
    struct _token_t *left;
    
     // right wing children
    struct _token_t *right; 
} token_t;

// Token b-tree root
token_t *g_btree =  NULL;

// A octet holding argument flags
uint8_t g_args = 0;

// This holds the total number of tokens
// found on the input file
uint16_t g_token_count = 0;

// A string holding the file name to be tokenized
char *g_filename;

/*
 * Print error
 */
int
__wes_err ( char *file, uint32_t line, char *fmt, ... )
{
    va_list ap;

    va_start (ap, fmt);
        fprintf (stderr, "Error at %s@%d: ", file, line);
        vfprintf(stderr, fmt, ap);
        fprintf (stderr, "\n");
    va_end(ap);

    return EXIT_FAILURE;
}

/*
 * Parse command line arguments
 */
void
wes_parsecmdline ( int argc, char ** argv )
{
    uint8_t i; // counter

    if ( argc == 1 ) {
        // Activate help flag
        g_args |= WES_ARG_HELP;
        return;
    }

    // Process every argument in the command line
    for ( i = 1; i < argc; i++ )
    {
        // Help
        if ( !strcmp("--help", argv[i]) )
            g_args |= WES_ARG_HELP;

        // Verbose mode
        else if ( !strcmp("--verbose", argv[i]) )
            g_args |= WES_ARG_VERBOSE;

        // Print version
        else if ( !strcmp("--version", argv[i]) )
            g_args |= WES_ARG_VERSION;

        // Everything else will be considered as the file name
        else g_filename = argv[i];
    }
}

/*
 * Print help information
 */
void
wes_help ()
{
    printf(
        "usage: wes <filename> <args>\n"
        "Arguments can be:\n"
        " --help\t\tPrint this help and exit\n"
        " --verbose\tRun with much more verbosity\n"
        );
}

/*
 * Print version and license info
 */
void
wes_version ()
{
    printf (
        "%s %d.%d\n"
        "Copyright (C) 2005-2013 Alejandro Ricoveri\n"
        "This is free software; see the source for "
        "copying conditions.  There is NO\n"
        "warranty; not even for MERCHANTABILITY or "
        "FITNESS FOR A PARTICULAR PURPOSE.\n\n"
        ,WES_NAME, WES_VER_MAJOR, WES_VER_MINOR
        );
}

/*
 * Create a new line
 * Returns a pointer to the new created line_t.
 * Otherwise returns NULL
 */
line_t *
wes_line_create ( uint16_t line_number )
{
    // The new line
     line_t *new_line;
     
    // Allocate some mem for the new line
    if ((new_line = (line_t *)malloc(sizeof(line_t))))
    {
        // Initial data might have ramdon bytes on it
        // so, we set it up right, fill it with zeros
        memset((void *)new_line, 0, sizeof(line_t));

        // Assign a number for this line
        new_line->number = line_number;

        // Initial ocurrence for this line is 1
        new_line->times = 1;
    }

    // ... and we're done
    return new_line;
}

/*
 * Delete a list of lines
 * A recursive algorithm
 */
void
wes_line_delete (line_t *line)
{
    // First, we delete the next line
    // before deleting this one
    if (line->next)
        wes_line_delete(line->next);

    // And that's it, we proceed to free that mem
    free(line); line = NULL;
}

/*
 * Append a line to a token line list
 */
int
wes_line_insert ( line_t **line_ptr, uint16_t line_number )
{
    if (*line_ptr)
    {
        if ((*line_ptr)->number == line_number)
            // At this point, the token has been found
            // more than once on this line number
            (*line_ptr)->times++;

        // There is no other ocurrence for the token
        // on this line number, so we try to seek for
        // it on the next one
        else wes_line_insert(&((*line_ptr))->next, line_number);
    }

    // At this point, the token has been found
    // for the first time on this line number
    else if (!(*line_ptr = wes_line_create(line_number)))
         return wes_error("Memory corruption!");
    
    // Line has been inserted succesfully
    return 0;
}

/*
 * Create a new token
 * Returns a pointer to the new created token_t.
 * Otherwise returns NULL
 */
token_t *
wes_token_create ( char *token_str, uint16_t line_number )
{
    // The new token
    token_t *new_token;
    
    // Allocate some mem for the new token
    if ((new_token = (token_t *)malloc(sizeof(token_t))))
    {
        // And set it up first
        memset((void *)new_token, 0, sizeof(token_t));

        // Allocate some mem for the new string
        if ( !(new_token->str = (char *) malloc(strlen(token_str)+1)) ) 
        {
            free(new_token);
            return NULL;
        }
        
        // Copy the string to the new token
        strcpy(new_token->str, token_str);

        // There's automatically a first ocurrence
        // of this token on this line number
        new_token->lines = wes_line_create (line_number);

        // Another token to the global count!
        g_token_count++;
    }

    // ... and we're done
    return new_token;
}

/*
 * Delete a token (and all of his children)
 * A recursive algorithm
 */
void
wes_token_delete ( token_t *token )
{
    if (token)
    {
        // First things first,
        // Delete left wing children
        wes_token_delete(token->left);

        // Delete right wing children
        wes_token_delete(token->right);

        // Deletes the line list for this token
        wes_line_delete(token->lines);
        
        // Free mem taken by string
        free(token->str);

        // ... And then, we can finally free this mem
        free(token); token = NULL;
    }
}

/*
 * Append a token to the token b-tree
 */
int
wes_token_insert ( token_t **token_ptr, char *token_str, uint16_t line_number )
{
    if (*token_ptr)
    {
        int32_t cmp ; // It hold string delta

        if (!(cmp = strcmp(token_str, (*token_ptr)->str)))
            // Token already exists on the b-tree, so
            // we proceed to append a new line ocurrence
            // for this token
            return wes_line_insert (&((*token_ptr))->lines, line_number);

        // Token may be not found here
        // Try to insert into whether its right or left wing
        else if (cmp < 0)
            return wes_token_insert(&(*token_ptr)->left, token_str, line_number);
        else
            return wes_token_insert(&(*token_ptr)->right, token_str, line_number);
    }

    // At this point, token doesn't exists
    // So, we create it ...
    else if (!(*token_ptr = wes_token_create(token_str, line_number)))
        return wes_error("Memory corruption!");
    
    // Token has been inserted succesfully
    return 0;
}

/*
 * Print the b-tree contents
 * A recursive algorithm
 */
void
wes_log_tree ( token_t *token )
{
    if (token)
    {
        line_t *line;

        // First things first,

        // We print left children contents
        wes_log_tree(token->left);

        // Print this token's info
        printf ("* %s: ", token->str);
        for (line = token->lines; line != NULL; line = line->next)
            printf (" %d(%d)", line->number, line->times);
        printf("\n");

        // Print right wing children info
        wes_log_tree(token->right);
    }
}

/*
 * Print the results summary
 */
void
wes_log_results (uint16_t lines)
{
    // Print the tree contents
    printf ("-- %s tokenizing statistics --\n\n", g_filename);
    printf ("Below you'll see the list of tokens found,\n"
            "followed by the line numbers where they were found\n"
            "with their respective number of ocurrences in parenthesis\n\n");
    wes_log_tree(g_btree);
    printf ("\n%6d token(s) found\n", g_token_count);
    printf ("%6d line(s) read\n", lines);
    printf ("\n-- End of execution --\n");
}

/*
 * Read the file contents
 * An iterative algorithm
 */
int
wes_readfile ()
{
    char *in_token = NULL; // This will hold each captured token
    char in_line[WES_MAX_COLS]; // This will hold each line in the file

    // Current line number
    uint16_t line_number;

    // The input file itself
    FILE *file;

    // Open the file
    if (!(file = fopen(g_filename, "r")))
        return wes_error("Couldn't open '%s'", g_filename);

    // Proceed to read each line and tokenize it
    for (line_number = 1; !feof(file); line_number++)
    {
        // Wes can leep line count until WES_MAX_LINES - 1
        if (line_number == WES_MAX_LINES)
            return wes_error("Max number of lines reached!");

        // Get the line as a string
        if (fgets(in_line, WES_MAX_COLS, file))
        {
            // Capture each token and insert it
            // into the b-tree
            for (
                in_token = strtok (in_line, WES_TOKEN_DELIMIT);
                in_token != NULL;
                in_token = strtok (NULL, WES_TOKEN_DELIMIT))
            {
                // insert a (maybe) new token into the btree of tokens
                wes_token_insert (&g_btree, in_token, line_number);
            }
        }
    }

    // Print the tree contents
    wes_log_results(line_number);

    // close the file
    fclose(file);

    // ... and we're done
    return EXIT_SUCCESS;
}

/* Entry point */
int
main ( int argc, char *argv[] )
{
    // File operation result
    int res;

    // Parse each argument in the command line
    wes_parsecmdline (argc ,argv);

    if (g_args & WES_ARG_HELP)
    {
        // Print help and exit
        wes_help();
        return EXIT_SUCCESS;
    }

    if (g_args & WES_ARG_VERSION)
    {
        // Print version and exit
        wes_version();
        return EXIT_SUCCESS;
    }

    // Else, we read the file then ...
    res = wes_readfile();
    
    // Do the house keeping!
    // House keeping is made no matter what
    wes_token_delete(g_btree);
    
    // ... and we're done
    return res;
}
