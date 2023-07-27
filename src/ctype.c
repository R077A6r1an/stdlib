#include <stdbool.h>

bool is_letter(int c) {
  if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
    return true;
  }
  return false;
}

int toupper(int c) {
  if(c >= 'a' && c <= 'z') {
    return c + ('A' - 'a');
  }else{
    return c;
  }
}
