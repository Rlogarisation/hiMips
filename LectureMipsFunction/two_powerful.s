main:
    addi	$sp, $sp, -4			# $sp = $sp + -4
    sw		$ra, 0($sp)		
    
    li		$a0, 1		            # $a0 = 1
    jal		two				        # jump to two and save position to $ra
    
    lw		$ra, 0($sp)		
    addi    $sp, $sp, 4
    jr		$ra					    # jump to $ra
    

two:
    addi	$sp, $sp, -8			# $sp = $sp + -8
    sw		$ra, 4($sp) 
    sw		$a0, 0($sp)

    bge		$a0, 1000000, endIf	    # if $a0 >= 1000000 then endIf
    mul     $a0, $a0, 2
    jal		two				        # jump to two and save position to $ra
    
endIf: 
    lw		$ra, 4($sp) 
    lw		$a0, 0($sp)
    addi	$sp, $sp, 8
    
    li		$v0, 1		
    syscall
    li		$a0, '\n'		        # $a0 = '\n'
    li		$v0, 11		            # $v0 = 11
    syscall

    jr		$ra					    # jump to $ra
    