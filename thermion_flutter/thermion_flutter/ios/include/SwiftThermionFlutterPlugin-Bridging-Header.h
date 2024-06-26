#ifndef SwiftThermionFlutterPlugin_Bridging_Header_h
#define SwiftThermionFlutterPlugin_Bridging_Header_h

#include <stdint.h>

#include "ResourceBuffer.h"

void *make_resource_loader(LoadFilamentResourceFromOwner loadFn, FreeFilamentResourceFromOwner freeFn, void *const owner);

// ResourceLoaderWrapper *make_resource_loader(LoadFilamentResourceFromOwner loadFn, FreeFilamentResourceFromOwner freeFn, void *const owner)
// {
//     ResourceLoaderWrapper *rlw = (ResourceLoaderWrapper *)malloc(sizeof(ResourceLoaderWrapper));
//     rlw->loadFromOwner = loadFn;
//     rlw->freeFromOwner = freeFn;
//     rlw->owner = owner;
//     return rlw;
// }

#endif