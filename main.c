
#include"lesson10.h"

#define TEST_CNT 10

char* tests[TEST_CNT] = {
  "()", "([])()", "{}()", "([{}])", ")(",
  "())({)", "(", "])})", "([(]", "([{}]){()}"
};

int main() {

  printf("Check brackets sequences:\n");
  for(unsigned i=0; i<TEST_CNT; ++i) {
      printf("The sequence %s is %s\n", tests[i],
             isCorrect(tests[i]) ? "correct": "incorrect");
  }

  listProcessing();
}
