# add 17 and 25 using variables stored in memory and print result
main:
    la		$t0, x		# 
    lw		$t1, 0($t0)		# 
    # Each int is 4 bytes,
    # equivalent to x[1]
    lw		$t2, 4($t0)		
    # x[2] = x[0] + x[1];
    add		$t3, $t1, $t2		# $t3 = $t1 + $t2
    sw		$t3, 8($t0)		# 
    # printf("%d", x[2]);
    lw		$a0, 8($t0)		# 
    li		$v0, 1		# $v0 = 1
    syscall
    # printf("\n");
    li		$a0, '\n'		# $a0 = '\n'
    li		$v0, 11		# $v0 = 11
    syscall
    # return 0;
    li		$v0, 0		# $v0 = 0
    jr		$ra					# jump to $ra
    
.data
# int x[] = {17,25,0}
x:  .word 17, 25, 0