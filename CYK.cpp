1include "CYK.hpp"

bool CFG::isCNF() {
  bool ok = true;
  for (auto rule : P) {
    if (!ok) {
      break;
    }
    if (!N.contains(rule.first)) {
      ok = false;
      break;
    }
    for (auto rpart : rule.second) {
      if (rpart.size() > 2) {
        ok = false;
        break;
      }
      if (rpart.size() == 1 && (!alp.contains(rpart[0]) || (rpart == "1" && rule.first != S))) {
        ok = false;
        break;
      }
      if (rpart.size() == 2 && (!N.contains(rpart[0]) || !N.contains(rpart[1]))) {
        ok = false;
        break;
      }
    }
  }
  return ok;
}

void CFG::Scan() {
  cout << "Enter size of sigma: ";
  size_t sz = 0;
  char c = 0;
  string s;
  cin >> sz;
  cout << endl << "Enter symbols:" << endl;
  for (size_t i = 0; i < sz; ++i) {
    cin >> c;
    alp.insert(c);
  }
  cout << endl << "Enter size of N: ";
  cin >> sz;
  cout << endl << "Enter symbols:" << endl;
  for (size_t i = 0; i < sz; ++i) {
    cin >> c;
    N.insert(c);
  }
  cout << endl << "Enter start symbol: ";
  cin >> S;
  if (!N.contains(S)) {
    throw runtime_error("N does not contain start symbol!!!");
  }
  cout << endl << "Enter size of set of prod rules: ";
  cin >> sz;
  for (size_t i = 0; i < sz; ++i) {
    cin >> c;
    if (!N.contains(c)) {
      throw runtime_error("Context free grammar can not contain terminal in left part of the rule!!!");
    }
    cout << "right part: ";
    cin >> s;
    cout << endl;
    P[c].insert(s);
  }
}

bool CFG::Recognize(const string &w) {
  if (!isCNF()) {
    throw runtime_error("Not in CNF!!!");
  }
  if (P[S].contains("1") && w.size() == 0) {
    return true;
  } else if (w.size() == 0 && !P[S].contains("1")) {
    return false;
  }
  return CYK(w);
}

bool CFG::CYK(const string &w) {
  map<char, vector<vector<bool>>> tb;
  for (char A : N) {
    tb[A] = vector<vector<bool>>(w.size() + 1, vector<bool>(w.size() + 1, false));
    for (size_t i = 0; i <= w.size(); ++i) {
      for (size_t j = 0; j <= w.size(); ++j) {
        if (j == i + 1) {
          for (auto rule_rp : P[A]) {
            if (rule_rp.size() == 1 && rule_rp[0] == w[i]) {
              tb[A][i][j] = true;
            }
          }
        }
      }
    }
  }
  for (size_t l = 2; l <= w.size(); ++l) {
    for (size_t i = 0; i <= w.size() - l; ++i) {
      size_t j = i + l;
      for (size_t k = i + 1; k <= j - 1; ++k) {
        for (auto A : N) {
          for (auto rule_rp : P[A]) {
            if (rule_rp.size() == 2 && tb[rule_rp[0]][i][k] && tb[rule_rp[1]][k][j]) {
              tb[A][i][j] = true;
            }
          }
        }
      }
    }
  }
  return tb[S][0][w.size()];
}
