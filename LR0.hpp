#include "Parser.hpp"

class LR0 : public Parser {
 public:
  LR0() = delete;
  LR0(const Grammar&);

  bool Recognize(const string& w, Grammar grammar) override {return true;}
  //bool Recognize(const string& w);

  ~LR0() {}

 private:
  class Situation {
  public:
    Situation() = delete;
    Situation(const Rule&, size_t);

    bool operator==(const Situation&) const;
    bool operator!=(const Situation&) const;
    bool operator<(const Situation&) const;

    bool Completed() const;
    char GetSymbol() const;
    const Rule& GetRule() const;
    size_t GetDotPos() const;

  private:
    Rule rule_;
    size_t dot_pos_;
  };
  class NFA {
  public:
    NFA() = default;
    set<char> alp;
    vector<set<Situation>> q;
    set<size_t> term_states;
    size_t start;
    vector<map<char, int64_t>> delta;
  };
  Grammar gr_;
  NFA nfa_;
  vector<vector<std::pair<char, int64_t>>> tb_;
  const std::pair<char, int64_t> win = { 'w', 1 };
  vector<char> l_;
  void BuildTable();
  void BuildNFA();

  void ReBuild(const Grammar&);

  set<Situation> Closure(const set<Situation>&);
  set<Situation> GoTo(const set<Situation>&, char);
};

