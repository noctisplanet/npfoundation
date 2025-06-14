//
//  once.c
//  npfoundation
//
//  Created by Jonathan Lee on 6/14/25.
//

#include <NPFoundation/dispatch/once.h>

void NPDispatchOnce(dispatch_once_t * _Nullable predicate, void(* _Nullable func)(void)) {
    dispatch_once(predicate, ^{
        func();
    });
}
