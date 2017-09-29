
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


class IRecord
{
public:
    bool save(void);
    bool find( void * data);
    bool del(void);
};


