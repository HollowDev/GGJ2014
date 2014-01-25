#ifndef _MEMORY_MACROS_H_
#define _MEMORY_MACROS_H_

#define SAFE_DELETE(x) if( x != nullptr ) { delete(x); (x) = nullptr; }
#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }

#endif