#include <stack>
#include <cctype>
#include <map>
#include <string>
#include <cstdio>
#include <sstream>
#include <windows.h>
#include <stdio.h>
#include <cmath>
#include <tchar.h>

#define ID_EDIT 100
#define ID_BUTTON_0 200
#define ID_BUTTON_1 201
#define ID_BUTTON_2 202
#define ID_BUTTON_3 203
#define ID_BUTTON_4 204
#define ID_BUTTON_5 205
#define ID_BUTTON_6 206
#define ID_BUTTON_7 207
#define ID_BUTTON_8 208
#define ID_BUTTON_9 209
#define ID_BUTTON_DOT 210
#define ID_BUTTON_AC 211
#define ID_BUTTON_DEL 212
#define ID_BUTTON_PL 213
#define ID_BUTTON_M 214
#define ID_BUTTON_ZV 215
#define ID_BUTTON_PR 216
#define ID_BUTTON_S1 217
#define ID_BUTTON_S2 218
#define ID_BUTTON_Decision 219
#define ID_BUTTON_X 220
#define ID_BUTTON_Q 221
#define ID_BUTTON_POW 222
#define ID_BUTTON_SIN 223
#define ID_BUTTON_COS 224
#define ID_BUTTON_TAN 225
using namespace std;

TCHAR* Calculate(TCHAR* buf)
{
    basic_string<TCHAR> s(buf), srpn, sres;
    basic_string<TCHAR>::size_type ind;
    while ((ind = s.find(TEXT(' '))) != basic_string<TCHAR>::npos)
    {
        s.erase(ind, 1);
    }
    map<TCHAR, size_t> map;
    map.insert(make_pair(TEXT('s'), 5));
    map.insert(make_pair(TEXT('c'), 5));
    map.insert(make_pair(TEXT('t'), 5));
    map.insert(make_pair(TEXT('√'), 4));
    map.insert(make_pair(TEXT('^'), 4));
    map.insert(make_pair(TEXT('*'), 3));
    map.insert(make_pair(TEXT('/'), 3));
    map.insert(make_pair(TEXT('+'), 2));
    map.insert(make_pair(TEXT('-'), 2));
    map.insert(make_pair(TEXT('('), 1));
    stack<TCHAR> stack;
    for (basic_string<TCHAR>::iterator ib = s.begin(); ib != s.end(); ++ib)
    {
        if (!isdigit(*ib) && (TEXT('.') != *ib) && !(s.begin() == ib && '-' == *ib))
        {
            srpn += TEXT(' ');
            if (TEXT(')') == *ib)
            {
                while (stack.top() != TEXT('('))
                {
                    srpn += stack.top();
                    stack.pop();
                    srpn += TEXT(' ');
                }
                stack.pop();
            }
            else if (TEXT('(') == *ib)
            {
                stack.push(*ib);
            }
            else if (stack.empty() || (map[stack.top()] < map[*ib]))
            {
                stack.push(*ib);
            }
            else
            {
                do
                {
                    srpn += stack.top();
                    srpn += TEXT(' ');
                    stack.pop();
                } while (!(stack.empty() || (map[stack.top()] < map[*ib])));
                stack.push(*ib);
            }
        }
        else
        {
            srpn += *ib;
        }
    }
    while (!stack.empty())
    {
        srpn += stack.top();
        srpn += TEXT(' ');
        stack.pop();
    }
    std::stack<double> dstack;
    basic_stringstream<TCHAR> ss(srpn);
    double d, d1;
    TCHAR c;
    while (ss.get(c))
    {
        if (isdigit(c) || TEXT('.') == c || (1 == ss.tellg() && TEXT('-') == c))
        {
            ss.unget();
            ss >> d;
                dstack.push(d);
        }
        else if (!isspace(c))
        {
            d1 = dstack.top();
            dstack.pop();
            
            if (!dstack.empty()) 
            {
                d = dstack.top();
                dstack.pop();
            }

            switch (c)
            {
          
            case TEXT('+'):
                dstack.push(d + d1);
                break;
            case TEXT('-'):
                dstack.push(d - d1);
                break;
            case TEXT('*'):
                dstack.push(d * d1);
                break;
            case TEXT('/'):
                dstack.push(d / d1);
                break;
            case TEXT('^'):
                dstack.push(pow(d, d1));
                break;
            case TEXT('√'):
                dstack.push(sqrt(d1));
                break;
            case TEXT('s'):
                dstack.push(sin(d1));
                break;
            case TEXT('c'):
                dstack.push(cos(d1));
                break;
            case TEXT('t'):
                dstack.push(tan(d1));
                break;
            }
        }
    }
    if (1 == dstack.size())
    {
        _stprintf(buf, TEXT("%lf"), dstack.top());
        char* p = buf + strlen(buf) - 1;
        while (*p == '0')
            *(p--) = 0;
        if (*p == '.')
            *p = 0;
        dstack.pop();
    }
    else
    {
        _stprintf(buf, TEXT("error"));
        
    }

    return buf;
}
