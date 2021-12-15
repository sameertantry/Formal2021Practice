#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::map;
using std::set;
using std::string;
using std::vector;

const string rule_separator = "->";
const string mock_non_term_str = "1";
const char mock_non_term = '1';
const set<char> alp = {'a', 'b', 'c'};

class Rule {
 public:
  Rule() = default;
  Rule(const Rule&) = default;
  Rule(const string&);

  Rule& operator=(const Rule&) = default;

  char GetLeft() const;
  string GetRight() const;

  bool operator<(const Rule&) const;
  bool operator==(const Rule&) const;

 private:
 public:
  char left_;
  string right_ = "";
};

class Grammar {
 public:
  Grammar() = default;
  Grammar(const set<char>& alphabet = alp);
  Grammar(const vector<Rule>& rules);
  Grammar(char start_, const vector<Rule>& rules,
          const set<char>& alphabet = alp);
  Grammar(const Grammar&) = default;

  Grammar& operator=(const Grammar&) = default;

  const vector<Rule>& GetRules() const;
  const set<char>& GetAlp() const;
  const set<char>& GetNonTerms() const;
  void AddRule(const Rule&);
  void AddLetter(char c) { alp_.insert(c); }
  vector<Rule> RulesWithLeftSide(char) const;
  void SetStart(char);
  char GetStart() const;

 private:
  set<char> alp_;
  set<char> nonterms_;
  char start_;
  vector<Rule> rules_;
};

