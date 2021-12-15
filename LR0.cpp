#include "LR0.hpp"

LR0::LR0(const Grammar& grammar) : gr_(grammar) {
  gr_.AddRule(Rule(mock_non_term_str + rule_separator + gr_.GetStart()));
  gr_.SetStart(mock_non_term);
  gr_.AddLetter(mock_non_term);
  BuildNFA();
  BuildTable();
}

set<LR0::Situation> LR0::Closure(const set<Situation>& sit_set) {
  set<Situation> new_set = sit_set;
  int64_t prev_sz = -1;
  while (prev_sz != new_set.size()) {
    prev_sz = new_set.size();
    for (const auto& sit : new_set) {
      char symb = sit.GetSymbol();
      if (!gr_.GetNonTerms().contains(symb)) {
        continue;
      }
      for (const auto& rule : gr_.GetRules()) {
        if (rule.GetLeft() == symb) {
          new_set.emplace(rule, 0);
        }
      }
    }
  }
  return new_set;
}

LR0::Situation::Situation(const Rule& rule, size_t pos)
    : rule_(rule), dot_pos_(pos) {}

set<LR0::Situation> LR0::GoTo(const set<Situation>& sit_set, char c) {
  set<Situation> new_set;
  for (const auto& sit : sit_set) {
    if (sit.GetSymbol() == c) {
      new_set.emplace(sit.GetRule(), sit.GetDotPos() + 1);
    }
  }
  return Closure(new_set);
}

bool LR0::Situation::operator<(const Situation& other) const {
  /*if (rule_ == other.rule_) {
    return dot_pos_ < other.dot_pos_;
  }
  return rule_ < other.rule_;*/
  if (rule_.left_ < other.rule_.left_) {
    return true;
  }
  if (rule_.left_ > other.rule_.left_) {
    return false;
  }
  if (rule_.right_ < other.rule_.right_) {
    return true;
  }
  if (rule_.right_ > other.rule_.right_) {
    return false;
  }
  if (dot_pos_ < other.dot_pos_) {
    return true;
  }
  if (dot_pos_ > other.dot_pos_) {
    return false;
  }
  return false;
}

bool LR0::Situation::operator==(const Situation& other) const {
  return !(*this < other) && !(other < *this);
}

bool LR0::Situation::operator!=(const Situation& other) const {
  return !(*this == other);
}

bool LR0::Situation::Completed() const {
  return dot_pos_ == rule_.GetRight().size();
}

char LR0::Situation::GetSymbol() const {
  if (Completed()) {
    return '\0';
  }
  return rule_.GetRight()[dot_pos_];
}

const Rule& LR0::Situation::GetRule() const { return rule_; }

size_t LR0::Situation::GetDotPos() const { return dot_pos_; }

void LR0::BuildNFA() {
  nfa_.alp.insert(gr_.GetAlp().begin(), gr_.GetAlp().end());
  nfa_.alp.insert(gr_.GetNonTerms().begin(), gr_.GetNonTerms().end());
  nfa_.start = 0;
  nfa_.q.resize(0);
  int64_t prev_sz = -1;
  nfa_.q.push_back(
      Closure({Situation(gr_.RulesWithLeftSide(gr_.GetStart())[0], 0)}));
  nfa_.delta.push_back(map<char, int64_t>());
  while (prev_sz != nfa_.q.size()) {
    prev_sz = nfa_.q.size();
    for (size_t i = 0; i < nfa_.q.size(); ++i) {
      for (char c : nfa_.alp) {
        auto new_state = GoTo(nfa_.q[i], c);
        if (!new_state.empty() &&
            find(nfa_.q.begin(), nfa_.q.end(), new_state) == nfa_.q.end()) {
          nfa_.q.push_back(new_state);
        }
      }
    }
  }
  nfa_.delta.resize(nfa_.q.size());
  for (size_t i = 0; i < nfa_.q.size(); ++i) {
    for (char c : nfa_.alp) {
      auto new_state = GoTo(nfa_.q[i], c);
      if (new_state.empty()) {
        nfa_.delta[i][c] = -1;
        continue;
      }
      nfa_.delta[i][c] =
          find(nfa_.q.begin(), nfa_.q.end(), new_state) - nfa_.q.begin();
    }
  }
  for (size_t i = 0; i < nfa_.q.size(); ++i) {
    bool is_term = true;
    for (const auto& sit : nfa_.q[i]) {
      if (!sit.Completed()) {
        is_term = false;
        break;
      }
    }
    if (is_term) {
      nfa_.term_states.insert(i);
    }
  }
}

void LR0::BuildTable() {
  tb_.assign(nfa_.q.size(),
             vector<std::pair<char, int64_t>>(nfa_.alp.size() + 1, {'\0', -1}));
  l_.resize(nfa_.alp.size() + 1);
  l_[0] = '$';
  for (size_t i = 0; i < nfa_.q.size(); ++i) {
    size_t j = 1;
    for (auto a : gr_.GetAlp()) {
      int64_t num = nfa_.delta[i][a];
      if (num != -1) {
        tb_[i][j] = {'s', num};
      }
      l_[j] = a;
      ++j;
    }
    for (auto A : gr_.GetNonTerms()) {
      int64_t num = nfa_.delta[i][A];
      if (num != -1) {
        tb_[i][j] = {'t', num};
      }
      l_[j] = A;
      ++j;
    }
  }
  auto win_sit = Situation(gr_.RulesWithLeftSide(mock_non_term)[0], 1);
  auto win_state = Closure({win_sit});
  int64_t win_state_index =
      find(nfa_.q.begin(), nfa_.q.end(), win_state) - nfa_.q.begin();
  tb_[win_state_index][0] = win;

  for (size_t i : nfa_.term_states) {
    if (i != win_state_index) {
      auto sit = *(nfa_.q[i].begin());
      auto rule = sit.GetRule();
      auto f = find(gr_.GetRules().begin(), gr_.GetRules().end(), rule);
      int64_t rule_number = f - gr_.GetRules().begin();
      for (size_t j = 0; j <= gr_.GetAlp().size(); ++j) {
        tb_[i][j] = {'r', rule_number};
      }
    }
  }
}

bool LR0::Recognize(string& w) {
  w += '$';
  stack<string> st;
  st.push("0");
  size_t i = 0;
  while (i <= w.size()) {
    int64_t cur_st = stoi(st.top());
    if (tb_[cur_st][num_[w[i]]].first == 's') {
      st.push("" + w[i]);
      st.push(std::to_string(tb_[cur_st][num_[w[i]]].second));
      ++i;
    } else if (tb_[cur_st][num_[w[i]]] == win) {
      return true;
    } else if (tb_[cur_st][num_[w[i]]].first == 'r') {
      Rule rule = gr_.GetRules()[tb_[cur_st][num_[w[i]]].second];
      for (size_t k = 0; k < rule.GetRight().size(); ++k) {
        st.pop(), st.pop();
      }
      int64_t prev_st = stoi(st.top());
      st.push("" + rule.GetLeft());
      st.push(std::to_string(tb_[prev_st][num_[rule.GetLeft()]].second));
    } else {
      return false;
    }
  }
  return false;
}
