#pragma once

//include

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>


//define
#define BOOL bool
#define MAX_SIZE 1000
#define PAUSE system("pause");
#define SPLITE 256
#define MATCH 257
//enum

enum STATUS
{
	SUCCESS = 1,
	FAIL = 0,
	ERROR = -1
};

enum STATE 
{
	EPSILON,
	END
};


