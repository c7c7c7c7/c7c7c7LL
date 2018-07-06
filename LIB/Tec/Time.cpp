#include<bits/stdc++.h>
using namespace std;


std::chrono::system_clock::time_point start;
std::chrono::system_clock::time_point owari;

start = std::chrono::system_clock::now();
owari = std::chrono::system_clock::now();

// erapsed = ms
double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(owari-start).count();
