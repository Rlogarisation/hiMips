main:
    la		$a0, string		 
    addi	$sp, $sp, -4			# $sp = $sp + -4
    sw		$ra, 0($sp)		        # 
    
    jal		my_strlen				# jump to my_strlen and save position to $ra
    
    move 	$a0, $v0		        # $a0 = $v0
    li		$v0, 1		            # $v0 = 1
    syscall
    li		$a0, '\n'		        # $a0 = '\n'
    li		$v0, 11		            # $v0 = 11
    syscall

    lw		$ra, 0($sp)		
    addi	$sp, $sp, 4			    # $sp = $sp + 4

    li		$v0, 0		            # $v0 = 0
    jr		$ra					    # jump to $ra

my_strlen:
    li		$s0, 0		            # $s0 = length = 0
    
loopA:	
    lb		$t0, 0($a0)	        

    beq		$t0, 0, endLoopA	    # if $t0 = *s == 0 then endLoopA
    addi	$s0, $s0, 1			    # length++;
    addi	$a0, $a0, 1			    # *s++;
    

    j		loopA				    # jump to loopA
    
endLoopA:
    move 	$v0, $s0		
    jr		$ra					# jump to $ra
    


    .data
string:
    .asciiz "Hello"