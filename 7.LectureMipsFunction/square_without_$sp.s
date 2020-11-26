
# What is the point/benifit to use $sp in official version?
# What is the benifit to use $sp to store array value than .space?
main:
    li		$s0, 0		        # $s0 = i = 0
    la		$t0, square		 
    
loopA:
    bge		$s0, 10, endLoopA	# if $s0 >= 10 then endLoopA
    
    mul     $t1, $s0, $s0       # $t1 = i * i

    mul     $t2, $s0, 4         # Counter position
    add		$t3, $t0, $t2		# square[i]
    sw		$t1, 0($t3)		    # squares[i] = i * i;
    

    addi	$s0, $s0, 1			# i++
    j		loopA				# jump to loopA
    
endLoopA:
    li		$s0, 0		        # $s0 = i = 0
loopB:
    bge		$s0, 10, endLoopB	# if $s0 >= 10 then endLoopB
    
    mul     $t2, $s0, 4         # Counter position
    add		$t3, $t0, $t2		# square[i]
    lw		$a0, 0($t3)		    # squares[i] = i * i;
    li		$v0, 1		        # $v0 = 1
    syscall
    li		$a0, '\n'		    # $a0 = '\n'
    li		$v0, 11		        # $v0 = 11
    syscall

    addi	$s0, $s0, 1			# $s0 = $s0 + 1
    j		loopB				# jump to loopB
    
endLoopB:
    li		$v0, 0		        # $v0 = 0
    jr		$ra					# jump to $ra


    .data
square:
    .space 40