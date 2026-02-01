#ifndef DEBUG_TEMPLATE_CPP
#define DEBUG_TEMPLATE_CPP
#include <bits/stdc++.h>

namespace __DEBUG_UTIL__
{
    using namespace std;
    
    // Toggle for colored output
    bool I_want_colored_output = false; // ONLY WORKS WITH TERMINAL
    
    // ANSI color codes based on toggling
    string white = I_want_colored_output ? "\033[0;m" : "";
    string outer = I_want_colored_output ? "\033[0;31m" : "";    // Red
    string varName = I_want_colored_output ? "\033[1;34m" : "";  // Blue
    string varValue = I_want_colored_output ? "\033[1;32m" : ""; // Green

    // Primitive Datatypes Print Functions
    void print(const char *x) { cerr << x; }
    void print(bool x) { cerr << (x ? "T" : "F"); }
    void print(char x) { cerr << '\'' << x << '\''; }
    void print(signed short int x) { cerr << x; }
    void print(unsigned short int x) { cerr << x; }
    void print(signed int x) { cerr << x; }
    void print(unsigned int x) { cerr << x; }
    void print(signed long int x) { cerr << x; }
    void print(unsigned long int x) { cerr << x; }
    void print(signed long long int x) { cerr << x; }
    void print(unsigned long long int x) { cerr << x; }
    void print(float x) { cerr << x; }
    void print(double x) { cerr << x; }
    void print(long double x) { cerr << x; }
    void print(string x) { cerr << '\"' << x << '\"'; }

    template <size_t N>
    void print(bitset<N> x) { cerr << x; }

    void print(vector<bool> v) {
        int f = 0;
        cerr << '{';
        for (auto &&i : v)
            cerr << (f++ ? "," : "") << (i ? "T" : "F");
        cerr << "}";
    }

    template <typename T>
    void print(T &&x);
    
    template <typename T>
    void print(vector<vector<T>> mat);
    
    template <typename T, size_t N, size_t M>
    void print(T (&mat)[N][M]);
    
    template <typename F, typename S>
    void print(pair<F, S> x);
    
    template <typename T, size_t N>
    struct Tuple;
    
    template <typename T>
    struct Tuple<T, 1>;
    
    template <typename... Args>
    void print(tuple<Args...> t);
    
    template <typename... T>
    void print(priority_queue<T...> pq);
    
    template <typename T>
    void print(stack<T> st);
    
    template <typename T>
    void print(queue<T> q);

    // Container-based Print Functions
    template <typename T>
    void print(T &&x) {
        int f = 0;
        cerr << '{';
        for (auto &&i : x)
            cerr << (f++ ? "," : ""), print(i);
        cerr << "}";
    }

    template <typename T>
    void print(vector<vector<T>> mat) {
        int f = 0;
        cerr << "\n~~~~~\n";
        for (auto &&i : mat) {
            cerr << setw(2) << left << f++, print(i), cerr << "\n";
        }
        cerr << "~~~~~\n";
    }

    template <typename T, size_t N, size_t M>
    void print(T (&mat)[N][M]) {
        int f = 0;
        cerr << "\n~~~~~\n";
        for (auto &&i : mat) {
            cerr << setw(2) << left << f++, print(i), cerr << "\n";
        }
        cerr << "~~~~~\n";
    }

    template <typename F, typename S>
    void print(pair<F, S> x) {
        cerr << '(';
        print(x.first);
        cerr << ',';
        print(x.second);
        cerr << ')';
    }

    template <typename T, size_t N>
    struct Tuple {
        static void printTuple(T t) {
            Tuple<T, N - 1>::printTuple(t);
            cerr << ",", print(get<N - 1>(t));
        }
    };

    template <typename T>
    struct Tuple<T, 1> {
        static void printTuple(T t) { print(get<0>(t)); }
    };

    template <typename... Args>
    void print(tuple<Args...> t) {
        cerr << "(";
        Tuple<decltype(t), sizeof...(Args)>::printTuple(t);
        cerr << ")";
    }

    template <typename... T>
    void print(priority_queue<T...> pq) {
        int f = 0;
        cerr << '{';
        while (!pq.empty())
            cerr << (f++ ? "," : ""), print(pq.top()), pq.pop();
        cerr << "}";
    }

    template <typename T>
    void print(stack<T> st) {
        int f = 0;
        cerr << '{';
        while (!st.empty())
            cerr << (f++ ? "," : ""), print(st.top()), st.pop();
        cerr << "}";
    }

    template <typename T>
    void print(queue<T> q) {
        int f = 0;
        cerr << '{';
        while (!q.empty())
            cerr << (f++ ? "," : ""), print(q.front()), q.pop();
        cerr << "}";
    }

    // Printer Functions for General Debugging
    void printer(const char *) {} // Base Recursive Case

    template <typename T, typename... V>
    void printer(const char *names, T &&head, V &&...tail) {
        int i = 0;
        for (size_t bracket = 0; names[i] != '\0' && (names[i] != ',' || bracket != 0); i++)
            if (names[i] == '(' || names[i] == '<' || names[i] == '{')
                bracket++;
            else if (names[i] == ')' || names[i] == '>' || names[i] == '}')
                bracket--;
        
        cerr << varName;
        cerr.write(names, i) << outer << " = " << varValue;
        print(head);

        if (sizeof...(tail))
            cerr << outer << " ||", printer(names + i + 1, tail...);
        else
            cerr << outer << "]\n" << white;
    }

    // Printer for Arrays
    void printerArr(const char *) {} // Base Recursive Case

    template <typename T, typename... V>
    void printerArr(const char *names, T arr[], size_t N, V... tail) {
        size_t ind = 0;
        cerr << varName;
        for (; names[ind] && names[ind] != ','; ind++)
            cerr << names[ind];
        for (ind++; names[ind] && names[ind] != ','; ind++);

        cerr << outer << " = " << varValue << "{";
        for (size_t i = 0; i < N; i++)
            cerr << (i ? "," : ""), print(arr[i]);
        cerr << "}";

        if (sizeof...(tail))
            cerr << outer << " ||", printerArr(names + ind + 1, tail...);
        else
            cerr << outer << "]\n" << white;
    }
}

// Debug Macros for Conditional Compilation
#ifndef ONLINE_JUDGE
    #define debug(...) std::cerr << __DEBUG_UTIL__::outer << __LINE__ << ": [", __DEBUG_UTIL__::printer(#__VA_ARGS__, __VA_ARGS__)
    #define debugArr(...) std::cerr << __DEBUG_UTIL__::outer << __LINE__ << ": [", __DEBUG_UTIL__::printerArr(#__VA_ARGS__, __VA_ARGS__)
#else
    #define debug(...)
    #define debugArr(...)
#endif

#endif
