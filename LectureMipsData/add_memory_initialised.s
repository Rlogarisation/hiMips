main:
    # No need to load word,
    # as we initiallised the value already.
    la		$t0, x		# 
    lw		$t1, 0($t0)		# 
    la		$t0, y		# 
    lw		$t2, 0($t0)		# 
    add		$t3, $t1, $t2		# $t3 = $t1 + $t2
    la		$t0, z		# 
    sw		$t3, 0($t0)		# 

    # Print
    la		$t0, z		# 
    lw		$a0, 0($t0)		# 
    li		$v0, 1		# $v0 = 1
    syscall

    li		$a0, '\n'		# $a0 = '\n'
    li		$v0, 11		# $v0 = 11
    syscall
    
    # Return 0
    li		$v0, 0		# $v0 = 0
    jr		$ra					# jump to $ra
    




data:
x:  .word 17
y:  .word 25
z:  .space 4