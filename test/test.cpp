#include "../headers/Parser.hpp"
#include <gtest/gtest.h>

TEST(CBS, CORRECT_VERY_EASY) {
  set<char> alp = {'(' , ')' };
  vector<Rule> rules = {
    Rule("S->"),
    Rule("S->(S)S")
  };
  EarleyParser earley_parser;
  Grammar gr('S', rules, alp);
  string w = "";
  EXPECT_TRUE(earley_parser.Recognize(w, gr));
}

TEST(CBS, CORRECT_EASY) {
  set<char> alp = {'(' , ')' };
  vector<Rule> rules = {
    Rule("S->"),
    Rule("S->(S)S")
  };
  EarleyParser earley_parser;
  Grammar gr('S', rules, alp);
  string w = "()";
  EXPECT_TRUE(earley_parser.Recognize(w, gr));
}

TEST(CBS, CORRECT_MEDIUM) {
  set<char> alp = {'(' , ')' };
  vector<Rule> rules = {
    Rule("S->"),
    Rule("S->(S)S")
  };
  EarleyParser earley_parser;
  Grammar gr('S', rules, alp);
  string w = "()(())()()()";
  EXPECT_TRUE(earley_parser.Recognize(w, gr));
}

TEST(CBS, CORRECT_HARD) {
  set<char> alp = {'(' , ')' };
  vector<Rule> rules = {
    Rule("S->"),
    Rule("S->(S)S")
  };
  EarleyParser earley_parser;
  Grammar gr('S', rules, alp);
  string w = "()()()()((()))()()()()()((()))";
  EXPECT_TRUE(earley_parser.Recognize(w, gr));
}

TEST(CBS, CORRECT_STRESS_0) {
  set<char> alp = {'(' , ')' };
  vector<Rule> rules = {
    Rule("S->"),
    Rule("S->(S)S")
  };
  EarleyParser earley_parser;
  Grammar gr('S', rules, alp);
  string w = "";
  for (size_t i = 0; i < 250; ++i) {
    w += "()";
  }
  EXPECT_TRUE(earley_parser.Recognize(w, gr));
}

TEST(CBS, CORRECT_STRESS_1) {
  set<char> alp = {'(' , ')' };
  vector<Rule> rules = {
    Rule("S->"),
    Rule("S->(S)S")
  };
  EarleyParser earley_parser;
  Grammar gr('S', rules, alp);
  string w = "";
  for (size_t i = 0; i < 100000; ++i) {
    w += "(";
  }
  for (size_t i = 0; i < 100000; ++i) {
    w += ")";
  }

  EXPECT_TRUE(earley_parser.Recognize(w, gr));
}

TEST(CBS, INCORRECT_VERY_EASY) {
  set<char> alp = {'(' , ')' };
  vector<Rule> rules = {
    Rule("S->"),
    Rule("S->(S)S")
  };
  EarleyParser earley_parser;
  Grammar gr('S', rules, alp);
  string w = "(";
  EXPECT_FALSE(earley_parser.Recognize(w, gr));
}

TEST(CBS, INCORRECT_EASY) {
  set<char> alp = {'(' , ')' };
  vector<Rule> rules = {
    Rule("S->"),
    Rule("S->(S)S")
  };
  EarleyParser earley_parser;
  Grammar gr('S', rules, alp);
  string w = "(()";
  EXPECT_FALSE(earley_parser.Recognize(w, gr));
}

TEST(CBS, INCORRECT_MEDIUM) {
  set<char> alp = {'(' , ')' };
  vector<Rule> rules = {
    Rule("S->"),
    Rule("S->(S)S")
  };
  EarleyParser earley_parser;
  Grammar gr('S', rules, alp);
  string w = "()(()))()()()";
  EXPECT_FALSE(earley_parser.Recognize(w, gr));
}

TEST(CBS, INCORRECT_HARD) {
  set<char> alp = {'(' , ')' };
  vector<Rule> rules = {
    Rule("S->"),
    Rule("S->(S)S")
  };
  EarleyParser earley_parser;
  Grammar gr('S', rules, alp);
  string w = "()()()(()))((()))()()()()()((()))";
  EXPECT_FALSE(earley_parser.Recognize(w, gr));
}

TEST(CBS, INCORRECT_STRESS_0) {
  set<char> alp = {'(' , ')' };
  vector<Rule> rules = {
    Rule("S->"),
    Rule("S->(S)S")
  };
  EarleyParser earley_parser;
  Grammar gr('S', rules, alp);
  string w = "";
  for (size_t i = 0; i < 250; ++i) {
    w += "()";
  }
  w += ")";
  EXPECT_FALSE(earley_parser.Recognize(w, gr));
}

TEST(CBS, INCORRECT_STRESS_1) {
  set<char> alp = {'(' , ')' };
  vector<Rule> rules = {
    Rule("S->"),
    Rule("S->(S)S")
  };
  EarleyParser earley_parser;
  Grammar gr('S', rules, alp);
  string w = "";
  for (size_t i = 0; i < 100000; ++i) {
    w += "(";
  }
  w += ")";
  for (size_t i = 0; i < 100000; ++i) {
    w += ")";
  }

  EXPECT_FALSE(earley_parser.Recognize(w, gr));
}

TEST(TERMINATE, WRONG_RULE_START) {
  set<char> alp = {'(' , ')' };

  EarleyParser earley_parser;
  EXPECT_ANY_THROW(Rule("SS->SS"));
}

TEST(TERMINATE, WRONG_RULE_STRUCTURE_0) {
  set<char> alp = {'(' , ')' };

  EarleyParser earley_parser;
  EXPECT_ANY_THROW(Rule("S-SS"));
}

TEST(TERMINATE, WRONG_RULE_STRUCTURE_1) {
  set<char> alp = {'(' , ')' };

  EarleyParser earley_parser;
  EXPECT_ANY_THROW(Rule("S-SS"));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

