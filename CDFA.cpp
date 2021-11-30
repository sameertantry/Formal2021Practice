#include "CDFA.h"

void NFA::AddEdge(int q1, char c, int q2) { delta[q1][c].insert(q2); }

void NFA::Scan() {
  size_t sz = 0;
  std::cout << "Enter alphabet size: ";
  std::cin >> sz;
  std::cout << "Enter symbols: ";
  for (size_t i = 0; i < sz; ++i) {
    char c;
    std::cin >> c;
    alp.insert(c);
  }

  std::cout << "Enter number of states: ";
  std::cin >> sz;
  std::cout << "Enter edges:" << std::endl;
  for (size_t i = 0; i < sz; ++i) {
    std::cout << " Enter q: ";
    int q;
    std::cin >> q;
    Q.insert(q);

    for (auto c : alp) {
      std::cout << "  Enter number of edges(" << q << ", " << c << "): ";
      int n;
      std::cin >> n;
      if (n != 0) {
        std::cout << "   Enter destination: ";
      }
      for (int j = 0; j < n; ++j) {
        int y;
        std::cin >> y;
        AddEdge(q, c, y);
      }
      std::cout << std::endl;
    }
  }
  std::cout << "Enter number of final states: ";
  std::cin >> sz;
  std::cout << " Enter final states: ";
  for (size_t i = 0; i < sz; ++i) {
    int x;
    std::cin >> x;
    F.insert(x);
  }
}

void NFA::RemoveEps() {
  for (auto q : Q) {
    while (!delta[q]['1'].empty()) {
      std::set<int> dest = delta[q]['1'];
      delta[q]['1'].clear();
      bool is_final = false;
      for (auto q_dest : dest) {
        if (!is_final && F.find(q_dest) != F.end()) {
          F.insert(q);
          is_final = true;
        }
        for (auto chr : alp) {
          delta[q][chr].insert(delta[q_dest][chr].begin(),
                               delta[q_dest][chr].end());
        }
        delta[q]['1'].erase(q_dest);
      }
    }
  }
  alp.erase('1');
  Q.clear();
  DFS(*this, s);
}

void NFA::DFS(NFA& nfa, int q) {
  nfa.Q.insert(q);
  for (auto chr : nfa.alp) {
    for (auto q_dest : nfa.delta[q][chr]) {
      if (nfa.Q.find(q_dest) == nfa.Q.end()) {
        DFS(nfa, q_dest);
      }
    }
  }
}

DFA::DFA(NFA& nfa) { BuildFromNFA(nfa); }

void DFA::BuildFromNFA(NFA& nfa) {
  alp = nfa.alp;
  std::queue<std::set<int>> q;
  Q.insert({nfa.s});
  s = {nfa.s};
  q.push({nfa.s});
  while (!q.empty()) {
    std::set<int> s = q.front();
    for (const auto& c : nfa.alp) {
      std::set<int> new_state;
      for (const auto& cnd : s) {
        for (const auto& x : nfa.delta[cnd][c]) {
          new_state.insert(x);
        }
      }
      if (!new_state.empty()) {
        if (!Q.contains(new_state)) {
          q.push(new_state);
          Q.insert(new_state);
        }
        delta[s][c] = new_state;
      }
    }
    q.pop();
  }

  for (const auto& q_dfa : Q) {
    for (const auto& q : q_dfa) {
      if (nfa.F.contains(q)) {
        F.insert(q_dfa);
      }
    }
  }
}

CDFA::CDFA(DFA& dfa) { BuildFromDFA(dfa); }

void CDFA::BuildFromDFA(DFA& dfa) {
  bool is_cdfa = true;
  std::set<int> empty;
  for (auto q : dfa.Q) {
    for (auto chr : dfa.alp) {
      if (dfa.delta[q][chr] == empty) {
        is_cdfa = false;
        break;
      }
    }
  }

  if (is_cdfa) {
    return;
  }

  std::set<int> mock_state = {-1};
  dfa.Q.insert(mock_state);
  for (auto state_in_set : dfa.Q) {
    for (auto c : dfa.alp) {
      if (dfa.delta[state_in_set][c] == empty) {
        dfa.delta[state_in_set][c] = mock_state;
      }
    }
  }

  int i = 0;
  std::map<std::set<int>, int> table;
  alp = dfa.alp;
  for (auto q : dfa.Q) {
    if (q == mock_state) {
      Q.insert(-1);
      if (dfa.F.contains(q)) {
        F.insert(-1);
      }
      table[q] = -1;
      continue;
    }
    Q.insert(i);
    if (dfa.F.contains(q)) {
      F.insert(i);
    }
    table[q] = i;
    ++i;
  }

  S = table[dfa.s];
  for (auto q : dfa.Q) {
    for (auto chr : dfa.alp) {
      delta[table[q]][chr] = table[dfa.delta[q][chr]];
      reverse_delta[table[dfa.delta[q][chr]]][chr] = table[q];
    }
  }
}

void CDFA::Visualize() {
  std::ofstream file;
  file.open("CDFA.dot");
  file << "digraph G {\n";
  for (auto q : Q) {
    for (auto chr : alp) {
      std::string s = "\t";
      if (q == -1) {
        s += "mock";
      } else if (q == S) {
        s += "start";
      } else {
        s += std::to_string(q);
      }
      s += " -> ";
      int v = delta[q][chr];
      if (v == -1) {
        s += "mock";
      } else if (v == S) {
        s += "start";
      } else {
        s += std::to_string(v);
      }
      s += "\t";
      s += "[label=\"" + std::string(1, chr) + "\"];\n";
      file << s;
    }
  }
  for (auto f : F) {
    std::string s = "\t";
    if (f == 0) {
      s += "start";
    } else {
      s += std::to_string(f);
    }
    s += " [shape=doublecircle];\n";
    file << s;
  }
  file << "}";
  file.close();
}
