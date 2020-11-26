main:
    li		$t0, 17	# $t0 = 17
    li		$t1, 25	# $t1 = 25
    add		$t2, $t0, $t1		# $t2 = $01 + 1t2
    
    move 	$a0, $t2		# $a0 = $21
    li		$v0, 1		# $v0 =1 
    syscall

    li		$a0, '\n'		# $a0 = '\n'
    li		$v0, 11		# $v0 =11 
    syscall

    li		$v0, 0		# $v0 =0 
    jr		$ra					# jump to $ra
    
    
    