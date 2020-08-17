#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

/** Individual tests */

#include "tests/framework.cpp"
#include "tests/sdfparser.cpp"

int main(int argc, char *argv[]) {
  return Catch::Session().run(argc, argv);
}
