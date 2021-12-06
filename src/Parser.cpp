#include "../headers/Parser.hpp"

EarleyParser::Situation::Situation(const Rule& rule, size_t dot_position,
                                   size_t start_posistion)
    : rule(rule), dot_pos(dot_position), start_pos(start_posistion) {}

bool EarleyParser::Situation::Completed() const {
  return dot_pos == rule.GetRight().size();
}

char EarleyParser::Situation::GetSymbol() const {
  return rule.GetRight()[dot_pos];
}

bool EarleyParser::Situation::operator<(const Situation& other) const {
  /*if (rule == other.rule) {
    if (dot_pos == other.dot_pos) {
      return start_pos < other.start_pos;
    }
    return dot_pos < other.dot_pos;
  }
  return rule < other.rule;*/
  if (rule.left_ < other.rule.left_) {
    return true;
  }
  if (rule.left_ > other.rule.left_) {
    return false;
  }
  if (rule.right_ < other.rule.right_) {
    return true;
  }
  if (rule.right_ > other.rule.right_) {
    return false;
  }
  if (dot_pos < other.dot_pos) {
    return true;
  }
  if (dot_pos > other.dot_pos) {
    return false;
  }
  return (start_pos < other.start_pos);

}

bool EarleyParser::Situation::operator==(const Situation& other) const {
  return rule == other.rule && dot_pos == other.dot_pos && start_pos == other.start_pos;
}

bool EarleyParser::Situation::operator!=(const Situation& other) const {
  return !(*this == other);
}

bool EarleyParser::Recognize(const string& w, Grammar grammar) {
  string mock_rule = mock_non_term_str + rule_separator + string(1, grammar.GetStart());
  grammar.SetStart(mock_non_term);
  grammar.AddRule(mock_rule);
  Earley(w, grammar);
  Situation final(mock_rule, 1, 0);
  return sit_sets_[w.size()].contains(final);
}

void EarleyParser::Earley(const string& w, const Grammar& grammar) {
  sit_sets_.clear();
  sit_sets_.resize(w.size() + 1);

  Rule start_rule = grammar.RulesWithLeftSide(mock_non_term)[0];
  sit_sets_[0].emplace(start_rule, 0, 0);

  int64_t prev_sz = -1;
  while (prev_sz != sit_sets_[0].size()) {
    prev_sz = sit_sets_[0].size();

    Predict(0, grammar);
    Complete(0);
  }

  for (size_t i = 1; i <= w.size(); ++i) {
    Scan(i - 1, w[i - 1]);

    prev_sz = -1;
    while (prev_sz != sit_sets_[i].size()) {
      prev_sz = sit_sets_[i].size();

      Predict(i, grammar);
      Complete(i);
    }
  }
}

void EarleyParser::Scan(size_t i, char c) {
  for (const auto& sit : sit_sets_[i]) {
    if (c == sit.GetSymbol()) {
      sit_sets_[i + 1].emplace(sit.rule, sit.dot_pos + 1, sit.start_pos);
    }
  }
}

void EarleyParser::Predict(size_t i, const Grammar& grammar) {
  for (const auto& sit : sit_sets_[i]) {
    char start = sit.GetSymbol();
    for (const auto& new_rule : grammar.RulesWithLeftSide(start)) {
      Situation s(new_rule, 0, i);
      sit_sets_[i].insert(s);
    }
  }
}

void EarleyParser::Complete(size_t i) {
  for (const auto& situation : sit_sets_[i]) {
    if (situation.Completed()) {
      for (const auto& possible_situation :
        sit_sets_[situation.start_pos]) {
        if (possible_situation.GetSymbol() ==
          situation.rule.GetLeft()) {
          sit_sets_[i].emplace(
            possible_situation.rule, possible_situation.dot_pos + 1,
            possible_situation.start_pos);
        }
      }
    }
  }
}

