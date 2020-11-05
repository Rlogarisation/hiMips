# Read a number n and print the first n tetrahedral numbers
# https://en.wikipedia.org/wiki/Tetrahedral_number

main:                  # int main(void) {

    la   $a0, prompt   # printf("Enter how many: ");
    li   $v0, 4
    syscall

    li   $v0, 5         # scanf("%d", number);
    syscall

    # Assign input number as $t0
    move 	$t0, $v0		# $t0 = $v0

    # Initial $t1 = n = 1;
    li		$t1, 1		# $t1 = 1

loopA:
    # while (n <= input) 
    # Exit loopA condition:
    # n > input
    bgt		$t1, $t0, end	# if $t1 > $t0 then end
    # Initial $t2 = total = 0;
    li		$t2, 0		# $t2 = 0
    # Initial $t3 = j = 1;
    li		$t3, 1		# $t3 = 1
    

    j		loopB				# jump to loopB
    
loopA2:
    # printf("%d\n", total);
    move 	$a0, $t2		# $a0 = $t2
    li		$v0, 1		# $v0 = 1
    syscall
    
    li		$a0, '\n'		# $a0 = '\n'
    li		$v0, 11		# $v0 = 11
    syscall
    

    # n = n + 1;
    add		$t1, $t1, 1		# $t1 = $t1 + 1
    
    j		loopA				# jump to loopA
loopB:
    # while (j <= n) 
    bgt		$t3, $t1, loopA2	# if $t3 > $t1 then loopA
    # Initial $t4 = i = 1;
    li		$t4, 1		# $t4 = 1
    
    j		loopC				# jump to loopC
loopB2:
    # j = j + 1;
    add		$t3, $t3, 1		# $t3 = $t3 + 1
    

    j		loopB				# jump to loopB

loopC:
    # while (i <= j)
    # End if (i > j)
    bgt		$t4, $t3, loopB2	# if $t4 > $t3 then loopB

    # total = total + i;
    add		$t2, $t2, $t4		# $t2 = $t2 + $t4
    
    # i = i + 1;
    add		$t4, $t4, 1		# $t4 = $t4 + 1
    

    j		loopC				# jump to loopC
    
end:
    jr   $ra           # return

    .data
prompt:
    .asciiz "Enter how many: "
