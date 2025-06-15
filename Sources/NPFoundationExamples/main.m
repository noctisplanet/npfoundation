//
//  main.cpp
//  npfoundation
//
//  Created by Jonathan Lee on 5/6/25.
//

#include <stdio.h>
#include <NPFoundation/NPFoundation.h>
#include <Foundation/Foundation.h>

static void NPDispatchOnceTest(void) {
    static int value = 0;
    value ++;
    if (value != 1)
        printf("%s error: %d\n", __func__, value);
    else
        printf("%s\n", __func__);
}

int main(int argc, const char * argv[]) {
    static dispatch_once_t onceToken;
    NPDispatchOnce(&onceToken, NPDispatchOnceTest);
    return 0;
}
