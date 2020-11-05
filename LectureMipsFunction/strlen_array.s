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
    # No need to mul 4 here, as char is 1 byte.
    add		$t1, $s0, $a0	
    # load because we cannot compare address with 0 in beq.
    lb		$t2, 0($t1)		        

    beq		$t2, 0, endLoopA	    # if $t1 == 0 then endLoopA
    addi	$s0, $s0, 1			    # $s0 = $s0 + 1
    j		loopA				    # jump to loopA
    
endLoopA:
    move 	$v0, $s0		
    jr		$ra					# jump to $ra
    


    .data
string:
    .asciiz "Hello"