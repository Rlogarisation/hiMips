# Read 10 numbers into an array
# print 0 if they are in non-decreasing order
# print 1 otherwise

# i in register $t0

main:

    li   $t0, 0         # i = 0
loop0:
    bge  $t0, 10, end0  # while (i < 10) {

    li   $v0, 5         #   scanf("%d", &numbers[i]);
    syscall             #

    mul  $t1, $t0, 4    #   calculate &numbers[i]
    la   $t2, numbers   #
    add  $t3, $t1, $t2  #
    sw   $v0, ($t3)     #   store entered number in array

    addi $t0, $t0, 1    #   i++;
    j    loop0          # }
end0:
    li	 $s0, 0		    # $s0 = swapped = 0;
    li	 $t0, 1		    # reset i = 1;

loopSwapped:
    bge		$t0, 10, endLoopSwapped	# if $t0 >= 10 then target
    
    mul     $t1, $t0, 4    #   calculate &numbers[i]
    la      $t2, numbers   #
    add     $t3, $t1, $t2  #    $t3 = x's address;
    
    add		$t4, $t1, -4		# $t4 = $t1 + -4
    add		$t5, $t4, $t2		# $t5 = y's address;
    
    lw		$t6, ($t3)		#   $t6 = x
    lw		$t7, ($t5)		#   $t5 = y
    


    bge		$t6, $t7, skipSwap	# if x >= y then skipSwap
    li		$s0, 1		   # $s0 = 1
    

skipSwap:

    addi	$t0, $t0, 1			# i++;
    j		loopSwapped				# jump to loopSwapped
    
endLoopSwapped:


    move   $a0, $s0        # printf("%d", 42)
    li   $v0, 1         #
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr   $ra

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

