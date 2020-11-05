main:
    li      $v0, 5             #   scanf("%d", &x);
    syscall                 
    move    $t0, $v0    # $t0 = x;           

    li		$s0, 0		# $s0 = i = 0;
    
loopA:
    bge		$s0, $t0, endLoopA	# if $s0 >= $t0 then endLoopA
    li		$s1, 0		# $s1 = j = 0;
    
loopB:
    bge		$s1, $t0, endLoopB	# if j >= x then endLoopB
    
    li		$a0, '*'		# $a0 = '*'
    li		$v0, 11		# $v0 = 11
    syscall


    addi	$s1, $s1, 1			# j++
    j		loopB				# jump to loopB
    

endLoopB:

    addi	$s0, $s0, 1			# i++
    
    li		$a0, '\n'		# $a0 = '\n'
    li		$v0, 11		# $v0 = 11
    syscall

    j		loopA				# jump to loopA
    

endLoopA:

    li      $v0, 0         # return 0
    jr      $ra
