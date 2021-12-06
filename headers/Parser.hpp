#include "Grammar.hpp"

class Parser {
 public:
  virtual bool Recognize(const string& w, Grammar grammar) = 0;
  virtual ~Parser() = default;
};

class EarleyParser : public Parser {
 public:
  EarleyParser() = default;

  bool Recognize(const string& w, Grammar grammar) override;

 private:
  class Situation;

  void Earley(const string&, const Grammar&);
  void Scan(size_t, char);
  void Predict(size_t, const Grammar&);
  void Complete(size_t);

  vector<set<Situation>> sit_sets_;
};

class EarleyParser::Situation {
 public:
  Situation() = delete;
  Situation(const Rule&, size_t, size_t);

  bool Completed() const;
  char GetSymbol() const;

  bool operator==(const Situation&) const;
  bool operator!=(const Situation&) const;
  bool operator<(const Situation&) const;

  Rule rule;
  size_t dot_pos = 0;
  size_t start_pos = 0;
};

