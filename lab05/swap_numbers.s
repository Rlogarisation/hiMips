# read 10 numbers into an array
# swap any pairs of of number which are out of order
# then print the 10 numbers

# i in register $t0,
# registers $t1 - $t3 used to hold temporary results

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
    li		$t0, 1		# reset i = 1;
loopSorting:
    bge		$t0, 10, endloopSorting	# if $t0 >= 10 then loopSorting

    mul     $t1, $t0, 4             # $t1 = [i]
    la      $t2, numbers        
    add     $t3, $t1, $t2           # $t3 = the address of x
    lw		$t4, ($t3)		        # $t4 = x
    addi    $t6, $t1, -4            # $t6 = [i - 1]
    add     $t7, $t6, $t2           # $t7 = the address of y
    lw		$t5, ($t7)		        # $t5 = y
    
    bge		$t4, $t5, endIfSorting	# if $t4 >= $t5 then endIfSorting
    sw		$t5, ($t3)		        # numbers[i] = y;
    sw		$t4, ($t7)		        # numbers[i - 1] = x;
    
endIfSorting:

    add		$t0, $t0, 1		        # counter++;
    j		loopSorting				# jump to loopSorting
    
endloopSorting:
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
    li   $v0, 0
    jr   $ra            # return 0

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

