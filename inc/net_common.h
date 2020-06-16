#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>

#pragma once

#ifdef NET_SPACE_NAME
#define NETSPACE_BEGIN namespace SPACE_NAME {
#define NETSPACE_END }
#define NETSPACE_USE using namespace SPACE_NAME;
#else
#define NETSPACE_BEGIN
#define NETSPACE_END
#define NETSPACE_USE
#endif


