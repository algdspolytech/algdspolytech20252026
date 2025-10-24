#pragma once
#include<stdio.h>

int* ReadFile(const char* File, const int* H, const int* W);
int GetParts(int* M, const int H, const int W);
void DrawPicture(const int* M, const int H, const int W);
void DrawGroups(const int* M, const int H, const int W);