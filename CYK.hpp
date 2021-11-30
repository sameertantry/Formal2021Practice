#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

class CFG {
public:
    set<char> alp;
    set<char> N;
    char S;
    map<char, set<string>> P;

    CFG() = default;

    void Scan();

    bool isCNF();

    bool Recognize(const string& w);

    bool CYK(const string& w);
};
