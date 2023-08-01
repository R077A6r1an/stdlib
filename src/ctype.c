#include <stdbool.h>

bool is_letter(int c) {
  if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
    return true;
  }
  return false;
}

int toupper(int c) {
  if(c >= 'a' && c <= 'z') {
    return c + ('a' - 'A');
  }else{
    return c;
  }
}

int isspace(int c) {
  switch(c) {
    case ' ':
    case '\f':
    case '\n':
    case '\v':
    case '\r': return true;
  }
  return false;
}

int tolower(int c) {
  if(c >= 'A' && c <= 'Z') {
    return c - ('a' - 'A');
  }
  return c;
}
