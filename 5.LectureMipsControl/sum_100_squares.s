main:
    # int sum = 0;
    li		$t0, 0		# $t0 = 0
    # int counter = 0;
    li		$t1, 0		# $t1 = 0
    
loop:
    bgt		$t1, 100, end	# if $t1 > 100 then end
    # int square = counter * counter;
    mul     $t2, $t1, $t1
    add		$t0, $t0, $t2		# $t0 = $t0 + $t2
    addi	$t1, $t1, 1			# $t1 = $t1 1 0
    j		loop				# jump to loop
    

end:
    # printf("%d", sum);
    move 	$a0, $t0		# $a0 = $t0
    li		$v0, 1		# $v0 = 1
    syscall

    # printf("\n");
    li		$a0, '\n'		# $a0 = '\n'
    li		$v0, 11		# $v0 = 11
    syscall

    li		$v0, 0		# $v0 =0 
    jr		$ra					# jump to $ra
    
    