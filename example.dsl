// function declaration
fuc int a -> something -> int {
  a + 1 |>; // return
}

// to pass multiple parameters you put them in brackets
fuc (int a, int b) -> something_else -> int { 
  a + b |>;
}

fuc start -> int {
  int a; // declaration for a & b
  int b;

  5 | a; // store 5 in a

  a | something | b; // call function something with input a and store in b
  b | print; // call print with b as input

  (a, b) | something_else | print; // call function something_else with two inputs & pass return to print

  0 |>; // return 0
}
