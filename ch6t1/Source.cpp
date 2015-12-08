#include <iostream>
#include <string>
#include <map>

using namespace std;

enum Token_value {
	PLUS = '+', MINUS = '-', MULT = '*', DIV = '/',
	PRINT = ';',ASSIGN='=', LP='(', RP=')', 
	END, NAME, NUMBER};



Token_value curr_tok = PRINT;
double num_val;
string nam_val;
map<string, double> table;
int err_numb;


Token_value get_token();
double expr(bool);
double term(bool);
double prim(bool);
int errr(const string & er_val);

int main()
{
	table["pi"] = 3.14;
	while (cin)
	{
		get_token();
		if (curr_tok == END) break;
		if (curr_tok == PRINT) continue;
		cout << expr(false) << endl;
	}
	return 0;

}

double expr(bool get)
{
	double left = term(get);
	for (;;)
	{
		switch (curr_tok)
		{
		case PLUS:
			left += term(true);
			break;
		case MINUS:
			left -= term(true);
			break;
		default:
			return left;
		}
	}
}

double term(bool get)
{
	double left = prim(get);
	for (;;)
	{
		switch (curr_tok)
		{
		case MULT:
			left *= prim(true);
			break;
		case DIV:
			if (double rvalue = prim(true))
			{
				left /= rvalue;
				break;
			}
			return errr("div by zerro");
		default:
			return left;
		}
	}
}

double prim(bool get)
{
	if (get) get_token();
	switch (curr_tok)
	{
	case NAME:
	{
		double &v = table[nam_val];
		if (get_token() == ASSIGN) v = expr(true);
		return v;
	}
	case NUMBER:
	{
		double v = num_val;
		get_token();
		return v;
	}
	case MINUS:
		return -prim(true);
	case LP:
	{
		double e = expr(true);
		if (curr_tok != RP) return errr("vait )");
		get_token();
		return e;
	}
	default:
		return errr("vait expression");
	}
}

Token_value get_token()
{
	char ch = 0;
	cin >> ch;

	switch (ch)
	{
	case 0:
		return curr_tok = END;
	case ';': case '+': case '-': case '*': case '/': case '=': case '(': case ')':
		return curr_tok = Token_value(ch);
	case '0': case '1': case '2': case '3': case '4': case '5': 
	case '6': case '7': case '8': case '9': case '.':
		cin.putback(ch);
		cin >> num_val;
		return curr_tok = NUMBER;
	default:
		if (isalpha(ch))
		{
			cin.putback(ch);
			cin >> nam_val;
			return curr_tok = NAME;
		}
		errr("not correct lexcem");
		return curr_tok = PRINT;
	}
}

int errr(const string & er_val)
{
	err_numb++;
	cerr << "error " << er_val << endl;
	return err_numb;
}
