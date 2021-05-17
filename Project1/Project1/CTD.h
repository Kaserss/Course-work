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
#define ID_BUTTON_POW 220
#define ID_BUTTON_SIN 221
#define ID_BUTTON_COS 222
#define ID_BUTTON_TAN 223
#define ID_BUTTON_ABS 224
#define ID_BUTTON_AT 225
#define ID_BUTTON_OP1 226
#define ID_BUTTON_OP2 227
#define ID_BUTTON_OP3 228
#define ID_BUTTON_LEFT 229
#define ID_BUTTON_RIGHT 230
#define ID_BUTTON_LOG 231
#define ID_BUTTON_PI 232
#define ID_BUTTON_E 233
using namespace std;

TCHAR* Option1(TCHAR* buf)
{
    
    basic_string<TCHAR> s(buf), srpn, sres;
    basic_string<TCHAR>::size_type ind;
    while (s.find(TEXT('si')) != basic_string<TCHAR>::npos)
    {
        s.erase(s.find(TEXT('i')), 2);
    }
    while (s.find(TEXT('co')) != basic_string<TCHAR>::npos)
    {
        s.erase(s.find(TEXT('o')), 2);
    }
    while (s.find(TEXT('tan')) != basic_string<TCHAR>::npos)
    {
        s.replace(s.find("tan"), 3, "a");
    }
    while (s.find(TEXT('ctg')) != basic_string<TCHAR>::npos)
    {
        s.replace(s.find("ctg"), 3, "o");
    }
    while (s.find(TEXT('log')) != basic_string<TCHAR>::npos)
    {
        s.replace(s.find("log"), 3, "l");
    }   
    while (s.find(TEXT('sqrt')) != basic_string<TCHAR>::npos)
    {
        s.replace(s.find("sqrt"), 4, "q");
    }
    
    while ((ind = s.find(TEXT(' '))) != basic_string<TCHAR>::npos) // удаление пробелов из входной строки
    {
        s.erase(ind, 1);
    }
   
    map<TCHAR, size_t> map; // карата весов символов
    map.insert(make_pair(TEXT('|'), 6));
    map.insert(make_pair(TEXT('l'), 6));
    map.insert(make_pair(TEXT('s'), 5));
    map.insert(make_pair(TEXT('c'), 5));
    map.insert(make_pair(TEXT('a'), 5));
    map.insert(make_pair(TEXT('o'), 5));
    map.insert(make_pair(TEXT('q'), 4));
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
    double num1, num2;
    TCHAR c;
    while (ss.get(c))
    {
        if (isdigit(c) || TEXT('.') == c || (1 == ss.tellg() && TEXT('-') == c))
        {
            ss.unget();
            ss >> num1;
                dstack.push(num1);
        }
        else if (!isspace(c))
        {
            num2 = dstack.top();
            dstack.pop();
            
            if (!dstack.empty()) 
            {
                num1 = dstack.top();
                dstack.pop();
            }

            switch (c)
            {
          
            case TEXT('+'):
                dstack.push(num1 + num2);
                break;
            case TEXT('-'):
                dstack.push(num1 - num2);
                break;
            case TEXT('*'):
                dstack.push(num1 * num2);
                break;
            case TEXT('/'):
                dstack.push(num1 / num2);
                break;
            case TEXT('^'):
                dstack.push(pow(num1, num2));
                break;
            case TEXT('q'):
                dstack.push(sqrt(num2));
                break;
            case TEXT('s'):
                dstack.push(sin(num2));
                break;
            case TEXT('c'):
                dstack.push(cos(num2));
                break;
            case TEXT('a'):
                dstack.push(tan(num2));
                break;
            case TEXT('o'):
                dstack.push(1/tan(num2));
                break;
            case TEXT('|'):
                dstack.push(abs(num2));
                break;
            case TEXT('l'):
                dstack.push(log2(num2));
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

TCHAR* Option2(TCHAR* buf)
{
    float a,b,c,x1,x2;
            _stscanf(buf, TEXT("(%f)*x^2+(%f)*x+(%f)=0"), &a, &b, &c);
            if ((pow(b, 2) - 4 * a * c) >= 0) 
            {
                x1 = (-1 * b - sqrt(b * b - 4 * a * c)) / (2 * a);
                x2 = (-1 * b + sqrt(b * b - 4 * a * c)) / (2 * a);
                _stprintf(buf, TEXT("x1 = %f; x2 = %f"), x1, x2);
            }
            else if ((b * b - 4 * a * c) < 0)
            {
                _stprintf(buf, TEXT("The discriminant is less than 0, the roots are immaterial."));
            }

    return buf;
}
TCHAR* Option3(TCHAR* buf)
{
    float a, b, x;
    _stscanf(buf, TEXT("(%f)*x+(%f)=0"), &a, &b);
        if (a == 0) {
            if (b == 0)  
                _stprintf(buf, TEXT("Infinite set of roots"));
            else         
                _stprintf(buf, TEXT("No roots"));
        }
        else {
            x = (-b / a == -0) ? b / a : -b / a;
            _stprintf(buf, TEXT("x = %f"), x);
            char* p = buf + strlen(buf) - 1;
            while (*p == '0')
                *(p--) = 0;
            if (*p == '.')
                *p = 0;
        }


    return buf;
}