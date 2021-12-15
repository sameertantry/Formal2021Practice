#include "Grammar.hpp"

class Parser {
 public:
  virtual bool Recognize(const string& w, Grammar grammar) = 0;
  virtual ~Parser() = default;
};

class LR0;

