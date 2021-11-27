#include "CDFA.h"
// 3 1 a b 4 0 2 1 3 0 1 0 1 0 2 1 2 1 3 2 0 1 1 2 2 3 3 0 1 3 0 1 3
int main() {
  NFA nfa;
  nfa.Scan();
  nfa.RemoveEps();
  DFA dfa(nfa);
  CDFA cdfa(dfa);
  cdfa.Visualize();
}
