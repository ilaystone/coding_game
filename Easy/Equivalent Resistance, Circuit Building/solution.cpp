#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

double roundToNearestTenth(double num)
{
    return std::round(num * 10.0) / 10.0;
}

// function to remove whitepaces from start and end
string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return ""; // no content
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

double find_resistor_value(const string &key, const vector<pair<string, double>> &resistors)
{
    for (const auto &resistor : resistors)
    {
        if (resistor.first == key)
        {
            return resistor.second;
        }
    }
    throw runtime_error("Resistor not found: " + key);
}

double parallel(double a, double b)
{
    return 1.0 / (1.0 / a + 1.0 / b);
}

double series(double a, double b)
{
    return a + b;
}

double eval_circuit_expr(string &expr, vector<pair<string, double>> &resistors)
{
    double (*op)(double, double);
    expr = trim(expr);

    // check current expression type
    if (expr[0] == '(')
        op = series;
    else if (expr[0] == '[')
        op = parallel;

    // remove the first and last characters
    string new_expr = expr.substr(1, expr.size() - 2);
    new_expr = trim(new_expr);

    cerr << new_expr << endl;

    double left = 0.0;
    double right = 0.0;
    int pos = 0;

    // determine left side
    if (new_expr[0] == '(' || new_expr[0] == '[')
    {
        int balance = 1;

        while (balance > 0)
        {
            pos++;
            if (new_expr[0] == ')' || new_expr[0] == ']')
                balance--;
            if (new_expr[0] == '(' || new_expr[0] == '[')
                balance++;
        };
        string temp = new_expr.substr(0, pos + 1);
        left = eval_circuit_expr(temp, resistors);
        cerr << "left is an expression: " << new_expr.substr(0, pos + 1) << endl;
    }
    else
    {
        left = find_resistor_value(string(1, new_expr[0]), resistors);
        cerr << "left is a value: " << string(1, new_expr[0]) << endl;
    }

    // skip white spaces
    pos++;
    while (new_expr[pos] == ' ')
        pos++;

    int start = pos;
    // determin right side
    if (new_expr[pos] == '(' || new_expr[pos] == '[')
    {
        int balance = 1;

        while (balance > 0)
        {
            pos++;
            if (new_expr[pos] == ')' || new_expr[pos] == ']')
                balance--;
            if (new_expr[pos] == '(' || new_expr[pos] == '[')
                balance++;
        };
        string temp = new_expr.substr(start, pos + 1);
        right = eval_circuit_expr(temp, resistors);
        cerr << "right is an expression: " << new_expr.substr(start, pos + 1) << endl;
    }
    else
    {
        right = find_resistor_value(string(1, new_expr[pos]), resistors);
        cerr << "left is a value: " << string(1, new_expr[pos]) << endl;
    }

    cerr << left << ' ' << right << endl;

    return op(left, right);
}

int main()
{
    int n;
    cin >> n;
    cin.ignore();
    // strore the resistors in map of string and double
    // where string is the name of the resistor and double is the resistance value
    vector<pair<string, double>> resistors(n);
    for (int i = 0; i < n; i++)
    {
        string name;
        int r;
        cin >> name >> r;
        cin.ignore();
        resistors[i] = make_pair(name, r);
    }
    string circuit;
    getline(cin, circuit);

    cout << std::fixed << std::setprecision(1) << roundToNearestTenth(eval_circuit_expr(circuit, resistors)) << endl;
    return 0;
}