// Andrew Taylor - andrewt@unsw.edu.au
// 08/06/2020
// copy stdin to stdout xor'ing each byte with value given as argument
// XOR(^): Same number goes to 0, different number goes to 1.

/*```
$ echo Hello Andrew|xor 42
bOFFE
kDNXO] $ echo Hello Andrew|xor 42|cat -A
bOFFE$
kDNXO] $
$  echo Hello |xor 42
bOFFE $ echo -n 'bOFFE '|xor 42
Hello
$ echo Hello|xor 123|xor 123
Hello
$
```*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <xor-value>\n", argv[0]);
        return 1;
    }

    int xor_value = strtol(argv[1], NULL, 0);

    if (xor_value < 0 || xor_value > 255) {
        fprintf(stderr, "Usage: %s <xor-value>\n", argv[0]);
        return 1;
    }

    int c;
    while ((c = getchar()) != EOF) {
        //    exclusive-or
        //    ^  | 0  1
        //   ----|-----
        //    0  | 0  1
        //    1  | 1  0

        int xor_c = c ^ xor_value;

        putchar(xor_c);
    }

    return 0;
}