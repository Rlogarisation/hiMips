# struct details { uint16_t postcode; char first_name[7]; uint32_t zid; };
# offset in bytes of fields of struct details
DETAILS_POSTCODE   = 0
DETAILS_FIRST_NAME = 2
DETAILS_ZID        = 9

main:
    la   $t0, student           # printf("%d", student.zid);
    add  $t1, $t0, DETAILS_ZID
    lw   $a0, ($t1)
    li   $v0, 1
    syscall

    li   $a0, ' '               #   putchar(' ');
    li   $v0, 11
    syscall

    la   $t0, student           # printf("%s", student.first_name);
    add  $a0, $t0, DETAILS_FIRST_NAME
    li   $v0, 4
    syscall

    li   $a0, ' '               #   putchar(' ');
    li   $v0, 11
    syscall

    la   $t0, student           # printf("%d", student.postcode);
    add  $t1, $t0, DETAILS_POSTCODE
    lhu  $a0, ($t1)
    li   $v0, 1
    syscall

    li   $a0, '\n'              #   putchar('\n');
    li   $v0, 11
    syscall

    li   $v0, 0                 # return 0
    jr   $ra
    
.data
student:
    .half 2052
    .asciiz "Alice"
    .word 5123456

