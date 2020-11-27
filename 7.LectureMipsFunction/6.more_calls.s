main:
    addi	$sp, $sp, -4			# $sp = $sp + -4
    sw		$ra, 0($sp)		        # 
    
    li		$a0, 10		            # $a0 = 10
    li		$a1, 12		            # $a1 = 12
    
    jal		sum_product				# jump to sum_product and save position to $ra
    
    move 	$a0, $v0		        # $a0 = $v0
    li		$v0, 1		            # $v0 = 1
    syscall
    li		$a0, '\n'		        # $a0 = '\n'
    li		$v0, 11		            # $v0 = 11
    syscall

    lw		$ra, 0($sp)	
    addi	$sp, $sp, 4			    # $sp = $sp + 4
    	 
    jr		$ra					    # jump to $ra

sum_product:
    addi	$sp, $sp, -12			# $sp = $sp + -12
    sw		$ra, 8($sp)		
    sw		$a0, 4($sp)		
    sw		$a1, 0($sp)		 
    
    li		$a0, 6		            # $a0 = 6
    li		$a1, 7		            # $a1 = 7
    jal		product				    # jump to product and save position to $ra
    
    lw		$ra, 8($sp)		 
    lw		$a0, 4($sp)		
    lw		$a1, 0($sp)	

    add		$t0, $a0, $a1		    # $t0 = a + b
    add		$v0, $t0, $v0		    # $v0 = $t0 + p
    


    addi	$sp, $sp, 12			# $sp = $sp + 12
    jr		$ra					    # jump to $ra
    
product:
    mul     $v0, $a0, $a1
    jr		$ra					    # jump to $ra
    
    