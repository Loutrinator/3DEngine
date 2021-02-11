#ifndef LOADEROBJ_H
#define LOADEROBJ_H

#include <iostream>
#include "LoadedObj.h"

class LoaderObj {
public:
    static LoadedObj Load(const std::string& file);
};

#endif //LOADEROBJ_H
