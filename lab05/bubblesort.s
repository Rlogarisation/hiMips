# read 10 numbers into an array
# bubblesort them
# then print the 10 numbers

# i in register $t0
# registers $t1, $t2 & $t3 used to hold temporary results

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
    li		$s0, 1		# $s0 = swapped = 1
loopForSwapped:
    bne		$s0, 1, endLoopForSwapped	    # if $s0 != 1 then endLoopForSwapped
    
    li		$s0, 0		                    # $s0 = swapped = 0;
    li		$t0, 1		                    # $t0 = i = 1;
    
loopForBubbleSort:
    bge		$t0, 10, endLoopForBubbleSort	# if $t0 >= 10 then endLoopForBubbleSort
    
    mul     $t1, $t0, 4                     # calculate &numbers[i]
    la      $t2, numbers   
    add     $t3, $t1, $t2                   # $t3 = the address of x
    lw		$t4, ($t3)		                # $t4 = x
    
    addi	$t5, $t1, -4			        # $t5 = $t1 + -4
    add		$t6, $t5, $t2		            # $t6 = the address of y
    lw		$t7, ($t6)		                # $t7 = y

    bge		$t4, $t7, endIfCondition	    # if $t4 >= $t7 then endIfCondition
    sw		$t7, ($t3)		                # numbers[i] = y;
    sw		$t4, ($t6)		                # numbers[i - 1] = x;

    li		$s0, 1		                    # $s0 = swapped = 1;
    
endIfCondition:

    addi	$t0, $t0, 1			            # i++;
    j		loopForBubbleSort				# jump to loopForBubbleSort
endLoopForBubbleSort:

    j		loopForSwapped				    # jump to loopForSwapped

endLoopForSwapped:
    li   $t0, 0         # i = 0
loop1:
    bge  $t0, 10, end1  # while (i < 10) {

    mul  $t1, $t0, 4    #   calculate &numbers[i]
    la   $t2, numbers   #
    add  $t3, $t1, $t2  #
    lw   $a0, ($t3)     #   load numbers[i] into $a0
    li   $v0, 1         #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    addi $t0, $t0, 1    #   i++
    j    loop1          # }
end1:

    jr   $ra            # return

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

