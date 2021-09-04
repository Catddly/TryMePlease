#pragma once

const     int a = 5;
constexpr int b = 8;

extern const int k;
//extern constexpr int j; // [ERROR]! constexpr can not cross translation unit.

void PrintTranslationUnit();