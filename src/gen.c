#include "gen.h"
#include "cg.h"

void gen_preamble() {
  cg_preamble();
}
void gen_postamble() {
  cg_postamble();
}
void gen_gen_free_regs() {
  free_all_registers();
}
void gen_print_int(int reg) {
  cg_print_int(reg);
}
