#include "../headers/Grammar.hpp"

Rule::Rule(const string& s) {
  size_t sep = s.find(rule_separator);
  if (sep == string::npos) {
    throw std::runtime_error("Incorrect rule!");
  }
  auto start = s.substr(0, sep);
  if (start.size() > 1 || start.size() == 0) {
    throw std::runtime_error("Incorrect left side for Context-free grammar!");
  }
  left_ = start[0];
  right_ = s.substr(sep + rule_separator.size(), s.size());
}

char Rule::GetLeft() const { return left_; }

string Rule::GetRight() const { return right_; }

bool Rule::operator<(const Rule& other) const {
  if (left_ == other.left_) {
    return right_ < other.right_;
  }
  return left_ < other.left_;
}

bool Rule::operator==(const Rule& other) const {
  return !(*this < other) && !(other < *this);
}

Grammar::Grammar(const set<char>& alphabet) : alp_(alphabet) {}

Grammar::Grammar(const vector<Rule>& rules) : alp_(alp), rules_(rules) {
  for (const auto& rule : rules_) {
    nonterms_.insert(rule.GetLeft());
  }
}

Grammar::Grammar(char start, const vector<Rule>& rules,
                 const set<char>& alphabet)
    : Grammar(rules) {
  start_ = start;
}

const vector<Rule>& Grammar::GetRules() const { return rules_; }

const set<char>& Grammar::GetAlp() const { return alp_; }

const set<char>& Grammar::GetNonTerms() const { return nonterms_; }

void Grammar::AddRule(const Rule& rule) { rules_.emplace_back(rule); }

vector<Rule> Grammar::RulesWithLeftSide(char left) const {
  vector<Rule> v;
  for (const Rule& rule : rules_) {
    if (rule.GetLeft() == left) {
      v.emplace_back(rule);
    }
  }
  return v;
}

void Grammar::SetStart(char c) { start_ = c; }

char Grammar::GetStart() const { return start_; }
