#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

class NFA {
 public:
  std::set<int> Q;
  std::set<char> alp;
  std::map<int, std::map<char, std::set<int>>> delta;
  int s;
  std::set<int> F;

  void AddEdge(int q1, char c, int q2);
  void RemoveEps();
  void Scan();

 private:
  static void DFS(NFA& nfa, int q);
};

class DFA {
 public:
  std::set<std::set<int>> Q;
  std::set<char> alp;
  std::set<int> s;
  std::map<std::set<int>, std::map<char, std::set<int>>> delta;
  std::set<std::set<int>> F;

  DFA() = default;
  DFA(NFA& nfa);
  void BuildFromNFA(NFA& nfa);
};

class CDFA {
 public:
  int S;
  std::set<char> alp;
  std::set<int> F;
  std::set<int> Q;
  std::map<int, std::map<char, int>> delta;
  std::map<int, std::map<char, std::set<int>>> reverse_delta;

  CDFA() = default;
  CDFA(DFA& dfa);
  void BuildFromDFA(DFA& dfa);
  void Visualize();
  void Minimize();

 private:
  void DFS(int q, std::vector<bool>& isReachable);
  std::vector<std::vector<bool>> BuildEqTable();
};
