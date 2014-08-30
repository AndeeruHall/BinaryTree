#pragma once

typedef struct prec
{
  int prefix;     //first three
  int ph_num;     //last four
  char lname[15]; //last name
  char fname[10]; //first name
}PREC;

typedef struct phones
{
  int prefix;
  int ph_num;
  char lname[15];
  char fname[10];
  struct phones *left;
  struct phones *right;
}PLNK;

