#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

double     eval_circuit_expr(string expr)
{
    double  res;
    int     balance;
    int     split_pos;
    string  sub_expr;
    char    first_char;
    string  left_side;
    string  right_side;
    
    res = 0.0f;
    balance = 0;
    split_pos = 0;
    sub_expr = expr.substr(1, expr.length() - 2);
    first_char = expr[0];
    cerr << sub_expr << endl;

    for (int i = 0; i < sub_expr.length(); i++)
    {
        if (sub_expr[i] == '(' || sub_expr[i] == '[')
            balance++;
        else if (sub_expr[i] == ')' || sub_expr[i] == ']')
            balance--;
        else if (balance == 0)
            split_pos = i;
    }

    left_side = sub_expr.substr(0, split_pos);
    right_side = sub_expr.substr(split_pos + 1, sub_expr.length());


    if (first_char == '(')
        return eval_circuit_expr(left_side);
    else if (first_char == '[')
        return eval_circuit_expr(right_side);
}

int     main()
{
    int n;
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        string name;
        int r;
        cin >> name >> r; cin.ignore();
    }
    string circuit;
    getline(cin, circuit);

    eval_circuit_expr(circuit);

    cout << "Equivalent Resistance" << endl;
    return 0;
}