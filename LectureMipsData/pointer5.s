main:
    # $t0 = p
    la		$t0, numbers		# $t0 represents the array 
    # $t1 = q
    # Why can't      lw $t1, 16($t0)
    add		$t1, $t0, 16		# $t1 = $t1 + 16
    # OR 
    # la    $t1, numbers + 16
loop:
    bgt		$t0, $t1, end	    # if $t0 > $t1 then end
    
    lw		$a0, 0($t0)		    # 
    li		$v0, 1		        # $v0 = 1
    syscall

    li		$a0, '\n'		    # $a0 = '\n'
    li		$v0, 11		        # $v0 = 11
    syscall

    add		$t0, $t0, 4		    # p++
    j		loop				# jump to loop
    
end:
    li		$v0, 0		        # $v0 = 0
    jr		$ra					# jump to $ra
    

.data
numbers:    
    .word   3, 9, 27, 81, 243