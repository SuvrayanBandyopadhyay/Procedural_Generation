#pragma once
#define UPDOWN 0
#define LEFTRIGHT 1
#include<iostream>
#include<vector>


//2D map generation function
std::vector<std::vector<double>> gen_map(int n);

//Display function
void display(std::vector < std::vector<double>>a);


//One D terrain gen function
std::vector<double> genoned(int n);


//Merge Function
std::vector<std::vector<double>> mergemap(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b,int overlap);


//Normalization function
std::vector<std::vector<double>> normalize(std::vector <std::vector<double>> a);