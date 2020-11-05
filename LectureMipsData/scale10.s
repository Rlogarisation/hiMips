main:
    li		$s0, 0		            # $s0 = counter = 0
    
loopScan:
    bge		$s0, 10, endLoopScan	# if $s0 >= 10 then endLoopScan
    
    la		$a0, enterNumberMsg		# printf("Enter a number: ");
    li		$v0, 4		            # $v0 = 4
    syscall

    li		$v0, 5		            # scanf("%d", &numbers[i]);
    syscall

    mul     $t0, $s0, 4             # $t0 = index
    la		$t1, numbers		    # $t1 = array
    add		$t2, $t1, $t0		    # $t2 = array[index]
    sw		$v0, ($t2)		        # store input into array[index] 
        

    addi	$s0, $s0, 1			    # counter++
    j		loopScan				# jump to loopScan
    
endLoopScan:
    li		$s0, 0		            # reset counter to 0
    j		loopMul				    # jump to loopMul

loopMul:
    bge		$s0, 10, endLoopMul	    # if $s0 >= 10 then endLoopMul
    
    mul     $t0, $s0, 4             # $t0 = index
    la		$t1, numbers		    # $t1 = array
    add		$t2, $t1, $t0		    # $t2 = array[index]
    
    lw		$t3, ($t2)		        # $t3 = array[index]
    mul     $t3, $t3, 42            # numbers[i] *= 42;
    sw		$t3, ($t2)		        # put new value back into array
    lw		$a0, ($t2)		        # printf("%d\n", numbers[i]);
    li		$v0, 1		            # $v0 = 1
    syscall
    li		$a0, '\n'		        # $a0 = '\n'
    li		$v0, 11		            # $v0 = 11
    syscall

    addi	$s0, $s0, 1			    # counter++
    j		loopMul				    # jump to loopMul
    
endLoopMul:
    li		$s0, 0		            # reset counter to 0
    jr		$ra					    # jump to $ra
    
.data
numbers:
    .space 40                       # int numbers[10];

enterNumberMsg:
    .asciiz "Enter a number: "