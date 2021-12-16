#include "../headers/LR0.hpp"
#include <gtest/gtest.h>

TEST(INDIAN_LECTURES_TEST, YEASY_NO) {
  set<char> alp = {'a' , 'b' };
  vector<Rule> rules = {
    Rule("S->AA"),
    Rule("A->aA"),
    Rule("A->b")
  };
  Grammar gr('S', rules, alp);
  LR0 parser(gr);
  string w = "";
  EXPECT_FALSE(parser.Recognize(w));
}

TEST(INDIAN_LECTURES_TEST, YEASY_YES) {
  set<char> alp = { 'a' , 'b' };
  vector<Rule> rules = {
    Rule("S->AA"),
    Rule("A->aA"),
    Rule("A->b")
  };
  Grammar gr('S', rules, alp);
  LR0 parser(gr);
  string w = "abb";
  EXPECT_TRUE(parser.Recognize(w));
}

TEST(INDIAN_LECTURES_TEST, MEDIUM_YES) {
  set<char> alp = { 'a' , 'b' };
  vector<Rule> rules = {
    Rule("S->AA"),
    Rule("A->aA"),
    Rule("A->b")
  };
  Grammar gr('S', rules, alp);
  LR0 parser(gr);
  string w = "aabb";
  EXPECT_TRUE(parser.Recognize(w));
}

TEST(INDIAN_LECTURES_TEST, MEDIUM_NO) {
  set<char> alp = { 'a' , 'b' };
  vector<Rule> rules = {
    Rule("S->AA"),
    Rule("A->aA"),
    Rule("A->b")
  };
  Grammar gr('S', rules, alp);
  LR0 parser(gr);
  string w = "baabb";
  EXPECT_FALSE(parser.Recognize(w));
}

TEST(INDIAN_LECTURES_TEST, HARD_YES) {
  set<char> alp = { 'a' , 'b' };
  vector<Rule> rules = {
    Rule("S->A"),
    Rule("A->aA"),
    Rule("A->b")
  };
  Grammar gr('S', rules, alp);
  LR0 parser(gr);
  string w = "";
  for (size_t i = 0; i < 100000; ++i) {
    w += "a";
  }
  w += "b";
  EXPECT_TRUE(parser.Recognize(w));
}

TEST(INDIAN_LECTURES_TEST, HARD_NO) {
  set<char> alp = { 'a' , 'b' };
  vector<Rule> rules = {
    Rule("S->A"),
    Rule("A->aA"),
    Rule("A->b")
  };
  Grammar gr('S', rules, alp);
  LR0 parser(gr);
  string w = "";
  for (size_t i = 0; i < 100000; ++i) {
    w += "a";
  }
  w += "ba";
  EXPECT_FALSE(parser.Recognize(w));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
