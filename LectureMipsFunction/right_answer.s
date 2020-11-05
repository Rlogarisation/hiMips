main:
    # Save current main return value into stack pointer.
    addi	$sp, $sp, -4			# Move sp down to create room
    sw		$ra, 0($sp)		

    jal		answer				    # jump to answer and save position to $ra
     
    move 	$a0, $v0		        # $a0 = $v0
    li		$v0, 1		            # printf("%d\n", a);
    syscall
    li		$a0, '\n'		        # $a0 = '\n'
    li		$v0, 11		            # $v0 = 11
    syscall

    lw		$ra, 0($sp)		        # 
    addi	$sp, $sp, 4			    # $sp = $sp + 4
    
    jr		$ra					    # jump to $ra
    

answer:
    li		$v0, 42		            # return 42;
    jr		$ra					    # jump to $ra
    