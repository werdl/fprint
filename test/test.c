#include <stdio.h>
#include "../src/fprint.h"

int main() {
    printf("%s", fmt("$s $s", "hey", "baby"));
    return 0;
} 