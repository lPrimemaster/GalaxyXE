#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <array>
#include <vmath.h>



#ifdef DEBUG
#define SDEBUG(x) std::cerr << "[DEBUG] " << x << std::endl;
#else
#define SDEBUG(x) if(0){ std::cerr << "[DEBUG] " << x << std::endl; }
#endif

#ifdef DEBUG
#define SDEBUGIF(x, val) if(val) {std::cerr << "[DEBUG] " << x << std::endl;}
#else
#define SDEBUGIF(x, val) if(0){ if(val) {std::cerr << "[DEBUG] " << x << std::endl;} }
#endif

#ifdef DEBUG
#define SDEBUGVAL(x) x
#else
#define SDEBUGVAL(x) if(0){ x }
#endif

#define CANCEL_BLOCK(x) if(0){ x }

#define ONCE(x) {								\
					static int z = 0;			\
					if(!z){ x }					\
					z = 1;						\
				}								\

#define STRINGISE_IMPL(x) #x
#define STRINGISE(x) STRINGISE_IMPL(x)

// Use: #pragma message WARN("My message")
#if _MSC_VER
#   define FILE_LINE_LINK __FILE__ "(" STRINGISE(__LINE__) ") : "
#   define WARN(exp) (FILE_LINE_LINK "WARNING: " exp)
#else//__GNUC__
#   define WARN(exp) ("WARNING: " exp)
#endif

using namespace std;
