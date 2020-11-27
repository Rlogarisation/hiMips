main:
    li		$t0, 1		# $t0 =1 

loop:
    bgt		$t0, 10, end	# if $t0 > 10 then target
    # Print the counter otherwise
    move 	$a0, $t0		# $a0 = $t1
    li		$v0, 1		# $v0 =1 
    syscall
    # Print the next line
    li		$a0, '\n'		# $a1 ='\n' 
    li		$v0, 11		# $v1 =11 
    syscall
    # Perform counter++
    addi	$t0, $t0, 1		# $t0 = $t0 + 1
    # Continue the loop
    j		loop				# jump to loop

end:
    li		$v0, 0		# $v0 =0 
    jr		$ra					# jump to $ra
    
