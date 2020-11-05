main:
    # $t0 = b
    li		$t0, 0x03040506	# $t0 = 0x03040506
    # $t1 = u
    la		$t1, a		# 
    sw		$t0, 0($t1)		# 

    lb      $a0, 0($t1) # b = *(uint8_t *)&u;
    li		$v0, 1		# $v0 = 1
    syscall
    
    li		$a0, '\n'		# $a0 = '\n'
    li		$v0, 11		# $v0 = 11
    syscall

    li		$v0, 0		# $v0 = 0
    jr		$ra					# jump to $ra
    

.data:
# 6 5 4 3
a:  .space 4