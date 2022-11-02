//
//  eval.cpp
//  Homework-2-Problem-5
//
//  Created by Ashvin Bondada on 1/28/22.
//



#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

string infixToPostfix (string infix);
bool checkPrecendence (char a, char b);
bool isOperator (char op);
bool validChar (char test);

int evaluate(string infix, const Map& values, string& postfix, int& result) {
    
    stack<int> opStack;
    int operand1, operand2;
    int ans = 0;
    int getv = 0;
    int chrep = 0;
    int parcount = 0;
    // check the infix for basic erros
    for (int i = 0; i + 1 < infix.size(); i++) {        //  check uses () as multiplcation
        if (isalpha(infix[i]) && infix[i + 1] == '(')  {    //  )a case
            return 1;
        }
        if (infix[i] == ')' && isalpha(infix[i + 1]))  {    //  a( case
            return 1;
        }
        if (infix[i] == ')' && infix[i + 1] == '(')  {    //  )( case
            return 1;
        }
        if (isOperator((infix[i])) && isOperator((infix[i + 1])))  {    //  if there are operators right after eachother "++" "--"
            return 1;
        }
        if (isalpha((infix[i])) && isalpha((infix[i + 1])))  {    //  if there are operands right after eachother "aa" "bb"
            return 1;
        }
        if (isalpha(infix[i])) {                            //  if there are any upper case characters;
            if (isupper(infix[i])) {
                return 1;
            }
        }
    }
    
    if (isOperator((infix.back()))) {  //  if last char of infix is a operator
        return 1;
    }
    if (isOperator((infix[0]))) {  //  if first char of infix is a operator
        return 1;
    }
  
    for (int j = 0; j < infix.size(); j++) {
        if (!validChar(infix[j])) {                 //  if invalid characters
            return 1;
        }
      
        if (infix[j] == '(' || infix[j] == ')') {     // check amount of paranthesis
            parcount++;
        }
    }
    if (parcount % 2 == 1) {            // if an odd amount of parantheses, invalid
        return 1;
    }
    
    
    // start checking postfix for more errors
    postfix = infixToPostfix(infix);
    if (postfix.size() == 1 && isalpha(postfix[0])) {       //  check if theres only 1  operand in expression
        if (!values.get(to_string(postfix[0]), chrep)) {               //      but operand is invalid, return 2
            return 2;
        }
        result = chrep;
        return 0;
    }
    
    if (postfix.size() < 3) {                       // after passing edge cases, if its not valid expression, return 1
        return 1;
    }
    

    
    for (int i = 0; i < postfix.size(); i++) {      // if values dont map
        if (isalpha(postfix[i])) {
            if (!values.get(to_string(postfix[0]), chrep)) {
                return 2;
            }
        }
    }
    
    
    for (int i = 0; i < postfix.size(); i++) {
        // bool checked
        // go thru if loop
        if (isalpha(postfix[i])) {
            values.get(to_string(postfix[0]), getv);
            opStack.push(getv);
        }
        else {
            if (opStack.size() < 2) {   //  if not enough elements to do operation
                return 1;
            }
            operand2 = opStack.top();
            opStack.pop();
            operand1 = opStack.top();
            opStack.pop();
            // get map value for the operands
            if (postfix[i] == '+')
                ans = operand1 + operand2;
            if (postfix[i] == '-')
                ans = operand1 - operand2;
            if (postfix[i] == '*')
                ans = operand1 * operand2;
            if (postfix[i] == '/') {
                if (operand2 == 0) {        //  if dividing by 0
                    return 3;
                }
                ans = operand1 / operand2;
            }
            opStack.push(ans);
        }
    }
    if (opStack.size() != 1) {      //  if eval did not happen properly, then func is invalid
        return 1;
    }
    result = opStack.top(); //  if after all the checks, modify result.
    return 0;
    
};

bool validChar (char test) {
    
    if (isOperator(test))
        return true;
    if (isalpha(test))
        return true;
    if (isblank(test) != 0)
        return true;
    if (test == '(')
        return true;
    if (test == ')')
        return true;
    return false;
}

bool isOperator (char op) {
    if (op == '+')
        return true;
    if (op == '-')
        return true;
    if (op == '*')
        return true;
    if (op == '/')
        return true;
    else
        return false;
}

          
string infixToPostfix (string infix) {
    string postfix = "";
    stack<char> opStack;
    for (int i = 0; i <infix.size(); i++) {
        switch (infix[i]) {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                postfix += infix[i];
                break;
            case '(':
                opStack.push(infix[i]);
                break;
            case ')':
                while (opStack.top() != '(') {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.pop();
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                while (!opStack.empty() && opStack.top() != '(' && checkPrecendence(infix[i], opStack.top())) {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.push(infix[i]);
                break;
            default:
                break;
        }
    }
    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }
    return postfix;
}

bool checkPrecendence (char a, char b){
    if (a == b)
        return true;
    if (a == '+' && b == '*')
        return true;
    if (a == '+' && b == '/' )
        return true;
    if (a == '+' && b == '-' )
        return true;
    if (a == '-' && b == '*')
        return true;
    if (a == '-' && b == '/')
        return true;
    if (a == '-' && b == '+')
        return true;
    if (a == '*' && b == '+')
        return false;
    if (a == '*' && b == '-' )
        return false;
    if (a == '*' && b == '/' )
        return true;
    if (a == '/' && b == '+')
        return false;
    if (a == '/' && b == '-' )
        return false;
    if (a == '/' && b == '*' )
        return true;
    else
        return false;
}


int main()
       {
           char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
           int  vals[] = {  3,  -9,   6,   2,   4,   1  };
           Map m;
           for (int k = 0; vars[k] != '#'; k++)
               m.insert(to_string(vars[k]), vals[k]);
           string pf;
           int answer;
           assert(evaluate("a+ e", m, pf, answer) == 0  &&
                                   pf == "ae+"  &&  answer == -6);
           answer = 999;
           assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
        assert(evaluate("+a+i", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("(5+6+)", m, pf, answer) == 1  &&  answer == 999);
        assert(evaluate("(a+e+)", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("y(*o)", m, pf, answer) == 1  &&  answer == 999);
        assert(evaluate("y*(-o)", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
        assert(evaluate("(i-o)()", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
        assert(evaluate("(i-o))", m, pf, answer) == 1  &&  answer == 999);
        assert(evaluate("a+(i-o))*i-h", m, pf, answer) == 1  &&  answer == 999);
        assert(evaluate("(a+b))", m, pf, answer) == 1  &&  answer == 999);
        assert(evaluate("(a+b)", m, pf, answer) == 2  &&  answer == 999);
        assert(evaluate("(a+++b)", m, pf, answer) == 1  &&  answer == 999);
        assert(evaluate("(ac +( b)", m, pf, answer) == 1  &&  answer == 999);
             // unary operators not allowed:
           assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
        assert(evaluate("a*b", m, pf, answer) == 2  && pf == "ab*"  &&  answer == 999);
        assert(evaluate("a*bcjdfh+", m, pf, answer) == 1  &&  answer == 999);
    
        assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  && pf == "yoau-*+"  &&  answer == -1);
        answer = 999;
       assert(evaluate("o/(y-y)", m, pf, answer) == 3  && pf == "oyy-/"  &&  answer == 999);
        assert(evaluate(" a  ", m, pf, answer) == 0  && pf == "a"  &&  answer == 3);
        assert(evaluate("((a))", m, pf, answer) == 0  && pf == "a"  &&  answer == 3);
    
    cout << "Passed all tests" << endl;
}

