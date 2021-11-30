#include "RecognizeTestCase.hpp"

TEST_F(RecognizeTestCase, EmptyWordRec) {
	string w = "1";
	CFG gr;
	gr.alp.insert('1');
	gr.alp.insert('a');
	gr.N.insert('S');
	gr.S = 'S';
  gr.P['S'].insert(w);
  ASSERT_EQ(gr.Recognize(w), true);
}

TEST_F(RecognizeTestCase, EmptyWordNotRec) {
	string w = "1";
	CFG gr;
	gr.alp.insert('1');
	gr.alp.insert('a');
	gr.N.insert('S');
	gr.S = 'S';
  gr.P['S'].insert("a");
  ASSERT_EQ(gr.Recognize(w), false);
}

TEST_F(RecognizeTestCase, CBS_true_01) {
  string w = "()()(()())";
  CFG gr;
  gr.alp.insert('1');
  gr.alp.insert('(');
  gr.alp.insert(')');
  gr.S = 'A';
  gr.N.insert('A');
  gr.N.insert('B');
  gr.N.insert('C');
  gr.N.insert('E');
  gr.N.insert('D');
  gr.P['A'].insert("1");
  gr.P['A'].insert("BB");
  gr.P['A'].insert("CD");
  gr.P['B'].insert("BB");
  gr.P['B'].insert("CD");
  gr.P['C'].insert("(");
  gr.P['D'].insert("BE");
  gr.P['D'].insert(")");
  gr.P['E'].insert(")");
  ASSERT_EQ(gr.Recognize(w), true);
}

TEST_F(RecognizeTestCase, CBS_true_02) {
  string w = "(())()(()())";
  CFG gr;
  gr.alp.insert('1');
  gr.alp.insert('(');
  gr.alp.insert(')');
  gr.S = 'A';
  gr.N.insert('A');
  gr.N.insert('B');
  gr.N.insert('C');
  gr.N.insert('E');
  gr.N.insert('D');
  gr.P['A'].insert("1");
  gr.P['A'].insert("BB");
  gr.P['A'].insert("CD");
  gr.P['B'].insert("BB");
  gr.P['B'].insert("CD");
  gr.P['C'].insert("(");
  gr.P['D'].insert("BE");
  gr.P['D'].insert(")");
  gr.P['E'].insert(")");
  ASSERT_EQ(gr.Recognize(w), true);
}


TEST_F(RecognizeTestCase, CBS_true_03) {
  string w = "(()()(()())(((())))())";
  CFG gr;
  gr.alp.insert('1');
  gr.alp.insert('(');
  gr.alp.insert(')');
  gr.S = 'A';
  gr.N.insert('A');
  gr.N.insert('B');
  gr.N.insert('C');
  gr.N.insert('E');
  gr.N.insert('D');
  gr.P['A'].insert("1");
  gr.P['A'].insert("BB");
  gr.P['A'].insert("CD");
  gr.P['B'].insert("BB");
  gr.P['B'].insert("CD");
  gr.P['C'].insert("(");
  gr.P['D'].insert("BE");
  gr.P['D'].insert(")");
  gr.P['E'].insert(")");
  ASSERT_EQ(gr.Recognize(w), true);
}
TEST_F(RecognizeTestCase, CBS_true_04_stresstest) {
  string w = "(()()(()())(((())))())(((((((((((((((((((()())))))))))))()))))))))()()()((((((((((((((((((((((((((((((((((((((()))))))))))))))))))))))))))))))))))))))(((((((((())))))))))()()()";
  CFG gr;
  gr.alp.insert('1');
  gr.alp.insert('(');
  gr.alp.insert(')');
  gr.S = 'A';
  gr.N.insert('A');
  gr.N.insert('B');
  gr.N.insert('C');
  gr.N.insert('E');
  gr.N.insert('D');
  gr.P['A'].insert("1");
  gr.P['A'].insert("BB");
  gr.P['A'].insert("CD");
  gr.P['B'].insert("BB");
  gr.P['B'].insert("CD");
  gr.P['C'].insert("(");
  gr.P['D'].insert("BE");
  gr.P['D'].insert(")");
  gr.P['E'].insert(")");
  ASSERT_EQ(gr.Recognize(w), true);
}
TEST_F(RecognizeTestCase, CBS_true_05_stresstest) {
  string w = "((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((()))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))";
  CFG gr;
  gr.alp.insert('1');
  gr.alp.insert('(');
  gr.alp.insert(')');
  gr.S = 'A';
  gr.N.insert('A');
  gr.N.insert('B');
  gr.N.insert('C');
  gr.N.insert('E');
  gr.N.insert('D');
  gr.P['A'].insert("1");
  gr.P['A'].insert("BB");
  gr.P['A'].insert("CD");
  gr.P['B'].insert("BB");
  gr.P['B'].insert("CD");
  gr.P['C'].insert("(");
  gr.P['D'].insert("BE");
  gr.P['D'].insert(")");
  gr.P['E'].insert(")");
  ASSERT_EQ(gr.Recognize(w), true);
}
TEST_F(RecognizeTestCase, CBS_false_01) {
  string w = "(()()(()())(((())))(())";
  CFG gr;
  gr.alp.insert('1');
  gr.alp.insert('(');
  gr.alp.insert(')');
  gr.S = 'A';
  gr.N.insert('A');
  gr.N.insert('B');
  gr.N.insert('C');
  gr.N.insert('E');
  gr.N.insert('D');
  gr.P['A'].insert("1");
  gr.P['A'].insert("BB");
  gr.P['A'].insert("CD");
  gr.P['B'].insert("BB");
  gr.P['B'].insert("CD");
  gr.P['C'].insert("(");
  gr.P['D'].insert("BE");
  gr.P['D'].insert(")");
  gr.P['E'].insert(")");
  ASSERT_EQ(gr.Recognize(w), false);
}


TEST_F(RecognizeTestCase, CBS_false_02) {
  string w = "(()";
  CFG gr;
  gr.alp.insert('1');
  gr.alp.insert('(');
  gr.alp.insert(')');
  gr.S = 'A';
  gr.N.insert('A');
  gr.N.insert('B');
  gr.N.insert('C');
  gr.N.insert('E');
  gr.N.insert('D');
  gr.P['A'].insert("1");
  gr.P['A'].insert("BB");
  gr.P['A'].insert("CD");
  gr.P['B'].insert("BB");
  gr.P['B'].insert("CD");
  gr.P['C'].insert("(");
  gr.P['D'].insert("BE");
  gr.P['D'].insert(")");
  gr.P['E'].insert(")");
  ASSERT_EQ(gr.Recognize(w), false);
}

TEST_F(RecognizeTestCase, CBS_false_03) {
  string w = "((())())()()())))(";
  CFG gr;
  gr.alp.insert('1');
  gr.alp.insert('(');
  gr.alp.insert(')');
  gr.S = 'A';
  gr.N.insert('A');
  gr.N.insert('B');
  gr.N.insert('C');
  gr.N.insert('E');
  gr.N.insert('D');
  gr.P['A'].insert("1");
  gr.P['A'].insert("BB");
  gr.P['A'].insert("CD");
  gr.P['B'].insert("BB");
  gr.P['B'].insert("CD");
  gr.P['C'].insert("(");
  gr.P['D'].insert("BE");
  gr.P['D'].insert(")");
  gr.P['E'].insert(")");
  ASSERT_EQ(gr.Recognize(w), false);
}

TEST_F(RecognizeTestCase, CBS_false_04_stresstest) {
  string w = "((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((()()()((()))))))))))))))))))(((((((())))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))())))))))))))()))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))";
  CFG gr;
  gr.alp.insert('1');
  gr.alp.insert('(');
  gr.alp.insert(')');
  gr.S = 'A';
  gr.N.insert('A');
  gr.N.insert('B');
  gr.N.insert('C');
  gr.N.insert('E');
  gr.N.insert('D');
  gr.P['A'].insert("1");
  gr.P['A'].insert("BB");
  gr.P['A'].insert("CD");
  gr.P['B'].insert("BB");
  gr.P['B'].insert("CD");
  gr.P['C'].insert("(");
  gr.P['D'].insert("BE");
  gr.P['D'].insert(")");
  gr.P['E'].insert(")");
  ASSERT_EQ(gr.Recognize(w), false);
}

TEST_F(RecognizeTestCase, NotCNF_01) {
  CFG gr;
  gr.alp.insert('b');
  gr.alp.insert('a');
  gr.N.insert('S');
  gr.N.insert('P');
  gr.S = 'S';
  gr.P['S'].insert("ab");
  ASSERT_THROW(gr.Recognize("ab"), std::runtime_error);
}

TEST_F(RecognizeTestCase, NotCNF_02) {
  CFG gr;
  gr.alp.insert('a');
  gr.N.insert('S');
  gr.S = 'S';
  gr.P['S'].insert("Sa");
  ASSERT_EQ(gr.isCNF(), 0);
}

TEST_F(RecognizeTestCase, NotCNF_03) {
  CFG gr;
  gr.alp.insert('a');
  gr.N.insert('S');
  gr.S = 'S';
  gr.P['S'].insert("SSS");
  ASSERT_EQ(gr.isCNF(), 0);
}

TEST_F(RecognizeTestCase, NotCNF_04) {
  CFG gr;
  gr.alp.insert('a');
  gr.N.insert('S');
  gr.N.insert('N');
  gr.S = 'S';
  gr.P['N'].insert("#");
  ASSERT_EQ(gr.isCNF(), 0);
}
