// Copyright 2021 NNTU-CS
#include <math.h>
#include <iostream>
#include <string>
#include <map>
#include "tstack.h"

bool isInt(char x) {
    if (static_cast<int>(x) >= 48 && static_cast<int>(x) <= 57) {
        return true;
    }
    return false;
}

int priority(char x) {
    if (x == '(')
        return 0;
    if (x == ')')
        return 1;
    if (x == '+' || x == '-')
        return 2;
    if (x == '*' || x == '/')
        return 3;
    else
        return -1;
}

void action(char x, TStack<char, 100>* stack, std::string *ostr) {
    bool flag = false;
    int code;
    char symb;
    code = priority(x);
    std::string str;
    if (code == 0) {
        stack->push(x);
    } else if (code == 1) {
        while (!stack->isEmpty()) {
            symb = stack->get();
            if (flag)
                *ostr += " ";
            if (symb != '(') {
                *ostr += symb;
                flag = false;
            } else {
                flag = true;
            }
            stack->pop();
        }
    } else if (code == 2 || code == 3) {
        if (code > priority(stack->get()) || stack->isEmpty()) {
            stack->push(x);
        } else {
            while (!stack->isEmpty()) {
                symb = stack->get();
                if (priority(symb) >= code) {
                    *ostr += symb;
                    stack->pop();
                }
                stack->push(x);
            }
        }
    }
}

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack1;
    std::string res = "";
    std::string res1 = "";
    int code;
    for (int i = 0; i < inf.length(); ++i) {
        if (isInt(inf[i])) {
            res += inf[i];
        } else {
            if (priority(inf[i]) != 0)
                res += " ";
            action(inf[i], &stack1, &res);
        }
    }
    while (!stack1.isEmpty()) {
        res += " ";
        res += stack1.get();
        stack1.pop();
    }
    return res;
}

int calculator(int a, int b, char act) {
    if (act == '+')
        return a + b;
    if (act == '-')
        return a - b;
    if (act == '*')
        return a * b;
    if (act == '/')
        return a / b;
    return -1000000;
}

int toInt(char x) {
    return x - '0';
}

int StrToInt(std::string str) {
    int res = 0;
    for (int i = str.length(); i > 0; --i) {
        res += (str[str.length() - i] - '0') * pow(10, i - 1);
    }
    return res;
}

int eval(std::string pref) {
    TStack<int, 100> stack2;
    std::string str = "";
    int a, b, res;
    for (int i = 0; i < pref.length(); ++i) {
        if (isInt(pref[i])) {
            str += pref[i];
            if (pref[i + 1] == ' ') {
                stack2.push(StrToInt(str));
                str = "";
            }
        } else if (pref[i] != ' ') {
            a = stack2.get();
            stack2.pop();
            b = stack2.get();
            stack2.pop();
            res = calculator(b, a, pref[i]);
            stack2.push(res);
        }
    }
    return stack2.get();
}
