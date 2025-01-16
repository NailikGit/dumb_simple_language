#define NOB_IMPLEMENTATION
#include "nob.h"

const char* modules[] = {
  "lexer"
};

void build_objects() {
  Nob_Cmd cmd = {0};
  Nob_String_Builder source = {0};
  Nob_String_Builder out = {0};
  for(int i = 0; i < NOB_ARRAY_LEN(modules); i++) {
    nob_cmd_append(&cmd, "clang", "-Wall", "-Wextra", "-g", "-c");

    nob_sb_append_cstr(&source, "src/");
    nob_sb_append_cstr(&source, modules[i]);
    nob_sb_append_cstr(&source, ".c");
    nob_sb_append_null(&source);
    nob_cmd_append(&cmd, source.items);
    source.count = 0;

    nob_sb_append_cstr(&out, "build/");
    nob_sb_append_cstr(&out, modules[i]);
    nob_sb_append_cstr(&out, ".o");
    nob_sb_append_null(&out);
    nob_cmd_append(&cmd, "-o", out.items);
    out.count = 0;

    nob_cmd_run_sync_and_reset(&cmd);
  }

  nob_sb_free(source);
  nob_sb_free(out);
  nob_cmd_free(cmd);
}

int main(int argc, char** argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);

  nob_mkdir_if_not_exists("build");
  build_objects();
  Nob_Cmd cmd = {0};
  Nob_String_Builder sb = {0};

  nob_cmd_append(&cmd, "clang", "src/main.c");
  for(int i = 0; i < NOB_ARRAY_LEN(modules); i++) {
    nob_sb_append_cstr(&sb, "build/");
    nob_sb_append_cstr(&sb, modules[0]);
    nob_sb_append_cstr(&sb, ".o");
  }
  nob_cmd_append(&cmd, "-o", "build/main");

  return 0;
}
