#define NOB_IMPLEMENTATION
#include "nob.h"

int gettok();

enum Token {
  tok_eof = -1,

  // function declaration
  tok_fuc = -2,
  
  tok_type = -3,
  tok_id = -4,
  tok_num = -5
};

static Nob_String_Builder id_str = {0};
static int num_val;
