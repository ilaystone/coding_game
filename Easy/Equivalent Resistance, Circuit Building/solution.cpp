#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cctype>

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

double parallel(const std::vector<double>& valuesToEvaluate) {
    if (valuesToEvaluate.empty()) return 0.0; // Avoid division by zero
    double sumOfReciprocals = 0.0;
    for (double value : valuesToEvaluate) {
        sumOfReciprocals += 1.0 / value;
    }
    return 1.0 / sumOfReciprocals;
}

double series(const std::vector<double>& valuesToEvaluate) {
    double total = 0.0;
    for (double value : valuesToEvaluate) {
        total += value;
    }
    return total;
}

double eval_circuit_expr(string &expr, vector<pair<string, double>> &resistors)
{
    cerr << "eval_circuit_expr: " << expr << endl;
    double (*op)(const vector<double> &);
    expr = trim(expr);

    // check current expression type
    if (expr[0] == '(')
        op = series;
    else if (expr[0] == '[')
        op = parallel;

    // remove the first and last characters
    string new_expr = expr.substr(1, expr.size() - 2);
    new_expr = trim(new_expr);

    vector<double> valuesToEvaluate;
    int pos = 0;

    while (pos < new_expr.length())
    {
        if (new_expr[pos] == '(' || new_expr[pos] == '[')
        {
            int balance = 1;
            int startIndex = pos;
            string temp = "";
    
            while (balance > 0)
            {
                temp += new_expr[pos];
                pos++;
                if (new_expr[pos] == ')' || new_expr[pos] == ']')
                    balance--;
                if (new_expr[pos] == '(' || new_expr[pos] == '[')
                    balance++;
            };
            temp += new_expr[pos];
            valuesToEvaluate.push_back(eval_circuit_expr(temp, resistors));
            pos++;
        }
        else
        {
            cerr << "value: ";
            int startIndex = pos;
            string temp = "";
            while (isalpha(new_expr[pos])) {
                temp += new_expr[pos];
                pos++;
            }
            valuesToEvaluate.push_back(find_resistor_value(temp, resistors));
            cerr << "*" << temp << '*' << endl;
        }

        // bypass whitespaces
        while (new_expr[pos] == ' ') pos++;
    }

    return op(valuesToEvaluate);
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