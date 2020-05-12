// Copyright (c) 2010, Zed A. Shaw.  All rights reserved.

// Copyright 2020 Jean-Francois Weber-Marx

// Modifications were made to the original file (see below)
// https://github.com/zedshaw/liblcthw/blob/master/tests/minunit.h

// This file (only used for unit testing) contains a few debugging
// macros used for a minimal C/C++ unit testing suite. Modifications
// were made to adpapt the orginal version (written only for C) to
// C++. Most of its content is inspired from the book "Learn C the
// Hard  Way: A Clear & Direct Introduction To Modern C Programming"
// by Zed A. Shaw

// Modifications performed and copyright retentiveness comply with
// the original licence (see below)
// https://github.com/zedshaw/liblcthw/blob/master/LICENSE

#undef NDEBUG
#ifndef VMINUT_H_
#define VMINUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define vminut_suite_start() char *message = NULL

/* We use a C-style cast below to allow the "string to be NULL" 
 * while processing C++ code. This code only run during testing.
*/
#define vminut_return(message) {\
    return (char*)message; }// NOLINT (C-style cast)

#define debug(M, ...) fprintf(stderr, "[DEBUG] %s:%d:%s " M "\n", \
                              __FILE__, __LINE__, __PRETTY_FUNCTION__, \
                              ##__VA_ARGS__)


#define log_err(M, ...) fprintf(stderr, \
    "[ERROR] (%s:%d: %s) " M "\n", \
                                __FILE__, __LINE__, __PRETTY_FUNCTION__, \
                                ##__VA_ARGS__)

#define vminut_assert(test, message) if (!(test)) {\
    log_err(message); vminut_return(message); }

#define vminut_assert_eq(got, exp, message) if ((got) != (exp)) { \
    log_err(message); \
    std::cerr << "[DEBUG] EXPECT: " << exp << std::endl \
              << "[DEBUG] GOT...: " << got << std::endl; \
    vminut_return(message); }

#define vminut_run_test(test) debug("\n-----%s", " " #test);\
  message = test(); tests_run++; if (message) { return message; }

#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
  if (argc != 1) argc = 1;\
  debug("----- RUNNING: %s", argv[0]);\
  printf("----\nRUNNING:: %s\n", argv[0]);\
  char *result = name();\
  if (result != 0) {\
    printf("FAILED: %s\n", result);\
  } else {\
    printf("ALL TESTS PASSED\n");\
  }\
  printf("Tests run: %d\n", tests_run);\
  exit(result != 0);\
}

static inline void vminut_hide_next_line() {
  std::cout << "[HIDETEST] ";
}

int tests_run;

#endif  // VMINUT_H_
