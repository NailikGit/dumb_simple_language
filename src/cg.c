#include "data.h"
#include "cg.h"
#include <stdio.h>
#include <stdlib.h>

static int free_reg[4];
static char* reg_list[4] = {"r8", "r9", "r10", "r11"};

void free_all_registers() {
  free_reg[0] = free_reg[1] = free_reg[2] = free_reg[3] = 1;
}

static int alloc_register() {
  for(int i = 0; i < 4; i++) {
    if(free_reg[i]) {
      free_reg[i] = 0;
      return i;
    }
  }
  fprintf(stderr, "[ERROR] out of registers\n");
  exit(1);
}

static void free_register(int reg) {
  if(free_reg[reg] != 0) {
    fprintf(stderr, "[ERROR] trying to free register that's already free %d\n", reg);
    exit(1);
  }

  free_reg[reg] = 1;
}

void cg_preamble() {
  free_all_registers();
  fputs("\tglobal\tmain\n"
        "\textern\tprintf\n"
        "\tsection\t.text\n"
        "LC0:\tdb\t\"%d\",10,0\n"
        "printint:\n"
        "\tenter\t0,0\n"
        "\tsub\trsp, 16\n"
        "\tmov\t[rbp-4], edi\n"
        "\tmov\teax, [rbp-4]\n"
        "\tmov\tesi, eax\n"
        "\tlea	rdi, [rel LC0]\n"
        "\tmov	eax, 0\n"
        "\tcall	printf\n"
        "\tnop\n"
        "\tleave\n"
        "\tret\n"
        "\n"
        "main:\n"
        "\tpush\trbp\n"
        "\tmov	rbp, rsp\n",
        out_file
  );
}

void cg_postamble() {
  fputs("\tmov	eax, 0\n"
        "\tpop	rbp\n"
        "\tret\n",
        out_file
  );
}

int cg_load(int value) {
  int r = alloc_register();

  fprintf(out_file, "\tmov\t%s, %d\n", reg_list[r], value);
  return r;
}

int cg_add(int r1, int r2) {
  fprintf(out_file, "\tadd\t%s, %s\n", reg_list[r1], reg_list[r2]);
  free_register(r2);
  return r1;
}

int cg_sub(int r1, int r2) {
  fprintf(out_file, "\tsub\t%s, %s\n", reg_list[r1], reg_list[r2]);
  free_register(r2);
  return r1;
}

int cg_mul(int r1, int r2) {
  fprintf(out_file, "\timul\t%s, %s\n", reg_list[r1], reg_list[r2]);
  free_register(r2);
  return r1;
}

int cg_div(int r1, int r2) {
  fprintf(out_file, "\tmov\trax, %s\n", reg_list[r1]);
  fprintf(out_file, "\tcqo\n");
  fprintf(out_file, "\tidiv\t%s\n", reg_list[r2]);
  fprintf(out_file, "\tmov\t%s, rax\n", reg_list[r1]);

  free_register(r2);
  return r1;
}

void cg_print_int(int r) {
  fprintf(out_file, "\tmov\trdi, %s\n", reg_list[r]);
  fprintf(out_file, "\tcall\tprintint\n");
  free_register(r);
}
