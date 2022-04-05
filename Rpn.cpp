//---------------------------------------------------------------------
// Name: Saikiran Nuthakki
// Email: sqn5261@psu.edu
//
// Description: Reverse Polish Notation Calculator
//---------------------------------------------------------------------
#include "stack.h"
#include<iostream>
#include<string>
#include<math.h>
#include <sstream>
#include <cstdlib>


using namespace std;
class RPN { // Reverse Polish Notation class

public:
   RPN();
    
    string finalpostfix(string expression);
    
    bool priority(int, int);
    bool Open(string);
    bool Closed(string);
    bool IsOperator(string);
    bool IsOperand(string);
    bool Accept(string);
    bool order(int);
    int operatororder(int);
    int solution(string);
};

RPN::RPN() // default constructor 
{
    
}


bool RPN::IsOperand(string ch) // checks to see if user's string is anything but an operator
{
    if (ch >= "0" && ch <= "9")
    {
        return true;
    }
    return false;
}


bool RPN::IsOperator(string C) { // checks to see if user's input is an operator
    if (C == "+" || C == "-" || C == "*" || C == "/" || C == "^") {
        return true;
    }
    return false;
}


bool RPN::Open(string ch) { // checks to see if user's input is an open parenthesis
    if (ch == "(") {
        return true;
    }
    return false;
}


bool RPN::Closed(string ch) { // checks to see if user's input is a closed parenthesis
    if (ch == ")") {
        return true;
    }
    return false;
}


bool RPN::Accept(string ch) { // checks to see if user's input is acceptable, then returns false
    if (!IsOperand(ch) || !IsOperator(ch) || !Open(ch) ||
        !Closed(ch) || ch != " ") {
        return false;
    }
    return true;
}

bool RPN::order(int oper) // function for correct order to solve problem
{
    if (oper == '^') {
        return true;
    }
    return false;
}



int RPN::operatororder(int oper) // another priority function to determine the operator order
{
    int weight = -1;
    
    if (oper == '+' || oper == '-')
        weight = 1;
    
    if (oper == '*' || oper == '/')
        weight = 2;
    
    if (oper == '^')
        weight = 3;
    return weight;
}

bool RPN::priority(int fo, int so) // checks for priority in problem with operators
{
    int foWeight = operatororder(fo); // int fo represents the the first operator
    int soWeight = operatororder(so);// int so represents the second operator
    
    if (foWeight == soWeight) {
        if (order(fo)) {
            return false;
        }
        else {
            return true;
        }
    }
    return foWeight > soWeight ? true : false;
}

string RPN::finalpostfix(string expression) // function that converts infix to postfix notation
{
    Stack S;
    string postfix = "";
    string elem;
    istringstream stream(expression);
    while(stream >> elem) {
        if (Accept(elem))
        {
            cout << "Invalid expression" << endl;
            exit(1);
        }
        
        else if (IsOperator(elem))
        {
            while (!S.isEmpty() && S.top() != '(' &&priority(S.top(), elem[0]))
            {
                postfix += S.top();
                postfix += " ";
                S.pop();
            }
            S.push(elem[0]);
        }
        else if (elem == "(") {
            S.push(elem[0]);
            
        }
        else if (elem == ")") {
            while (!S.isEmpty() && S.top() != '(') {
                postfix += S.top();
                postfix += " ";
                
                S.pop();
            }
            S.pop();
        }
        else if (IsOperand(elem)) {
            postfix += elem;
            postfix += " ";
        }
    }
    
    while (!S.isEmpty()) {
        postfix += S.top();
        postfix += " ";
        
        S.pop();
    }
    
    return postfix; // returns the postfix notation
}



int RPN::solution(string expression) // function that solves the original problem that the user inputs
{
    //cout << "expression: " << expression << endl;
    Stack stack;
    int a, b, div, expo;
    string token;
    istringstream stream(expression);
    while(stream >> token)
    {
        //cout << "token=" <<token << endl;
        if (token == "+")
        {
            a = stack.pop();
            b = stack.pop();
            stack.push(a + b);
        }
        else if (token == "-")
        {
            a = stack.pop() ;
            b = stack.pop();
            stack.push(-a + b);
        }
        else if(token=="*")
        {
            a = stack.pop() ;
            b = stack.pop() ;
            stack.push(a * b);
        }
        else if(token=="/")
        {
            div = stack.pop() ;
            b = stack.pop() ;
            stack.push(b / div);
        }
        else if(token=="^")
        {
            expo = stack.pop() ;
            b = stack.pop() ;
            stack.push(pow(b, expo));
        }
        else
        {
            stringstream stream(token);
            int value = 0;
            stream >> value;
            //cout << "\n The value which is pushed is " << value;
            stack.push(value);
            
        }
        
    }
    
    
    return stack.pop();
    
}
int main() // main function
{
    string s;
    RPN obj;
    cout << "Enter an infix expression: "; // prompts user to enter an infix problem
    getline(cin, s);
    string postfix = obj.finalpostfix(s);
    cout << " " << endl;
    cout << " The equivalent postfix expression of " <<s<< " is: " <<postfix << endl; // returns the problem in a postfix notation
    cout << " " << endl;
    cout << " The result of " << postfix << " is:" << obj.solution(postfix) << endl; // returns the correct answer for the problem
}
