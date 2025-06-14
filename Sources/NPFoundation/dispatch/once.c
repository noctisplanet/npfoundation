//
//  once.c
//  npfoundation
//
//  Created by Jonathan Lee on 6/14/25.
//

#include <NPFoundation/dispatch/once.h>

void NPDispatchOnce(dispatch_once_t *predicate, void(*func)(void)) {
    dispatch_once(predicate, ^{
        func();
    });
}
