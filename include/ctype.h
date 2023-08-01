#ifndef _ctype_std_included
#define _ctype_std_included

#include <stdbool.h>

/**
 * The isspace function tests for any character that is a standard white-space character or
 * is one of a locale-specific set of characters for which isalnum is false. The standard white-space
 * characters are the following:
 * 
 * space (' '), form feed ('\f'), new-line('\n'), carriage return ('\r'),
 * horizontal tab ('\t'), and vertical tab ('\v').
 * In the "C" locale, isspace returns true only for the standard white-space characters.
 */
extern int isspace(int c);

/**
 * Description
 * The tolower function converts an uppercase letter to a corresponding lowercase letter.
 * 
 * Returns
 * If the argument is a character for which isupper is true and there are one or more
 * corresponding characters, as specified by the current locale, for which islower is true,
 * the tolower function returns one of the corresponding characters (always the same one
 * for any given locale); otherwise, the argument is returned unchanged.
 */
extern int tolower(int c);

/**
 * Description
 * The toupper function converts a lowercase letter to a corresponding uppercase letter.
 * 
 * Returns
 * If the argument is a character for which islower is true and there are one or more
 * corresponding characters, as specified by the current locale, for which isupper is true,
 * the toupper function returns one of the corresponding characters (always the same one
 * for any giv en locale); otherwise, the argument is returned unchanged.
 */
extern int toupper(int c);

/**
 * Proofs, if the character is a letter (lowercase or uppercase).
 * Not a offical standard function, but needed in Operator.
 */
extern bool is_letter(int c);

static inline int isdigit(int ch)  {
  return (ch >= '0') && (ch <= '9');
}

static inline int isxdigit(int ch)  {
  if (isdigit(ch)) {
    return true;
  }
  if ((ch >= 'a') && (ch <= 'f')) {
    return true;
  }
  return (ch >= 'A') && (ch <= 'F');
}

#endif
