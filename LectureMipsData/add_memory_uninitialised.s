main:
    # Memory is assessed,
    # No need to correspond $t0 to variable.

    # Assign $t0 = x = 17.
    li		$t0, 17		# $t0 = 17
    la		$t1, x		# 
    sw		$t0, 0($t1)		# 
    
    # Assign $t0 = y = 25.
    li		$t0, 25		# $t0 = 25
    la		$t1, y		# 
    sw		$t0, 0($t1)		# 
    
    # Assign the address of x into $t1
    # similarly, $t2 = y, $t3 = z
    la		$t0, x		# 
    lw		$t1, 0($t0)		# $t1 = x
    la		$t0, y		# 
    lw		$t2, 0($t0)		# $t2 = y
    add		$t3, $t1, $t2		# $t3 = $t1 + $t2
    # Store z into memory address
    la		$t0, z		# 
    sw		$t3, 0($t0)		#

    # printf("%d", z);
    la		$t0, z		# 
    lw		$t3, 0($t0)		# 
    move 	$a0, $t3		# $a0 = $t3
    li		$v0, 1		# $v0 = 1
    syscall

    # printf("\n");
    li		$a0, '\n'		# $a0 = '\n'
    li		$v0, 11		# $v0 = 11
    syscall
    
    # return 0
    li		$v0, 0		# $v0 = 0
    jr		$ra					# jump to $ra
    
    
    


.data
x:  .space 4
y:  .space 4
z:  .space 4