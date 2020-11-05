# read a number n and print the integers 1..n one per line

main:                 # int main(void)
    la   $a0, stringPrintf  # printf("Enter a number: ");
    li   $v0, 4
    syscall

    li   $v0, 5       # scanf("%d", number);
    syscall

    # Assign number into variable $t0
    move 	$t0, $v0		# $t0 = $v0

    # Initia counter as variable $t1 = 0
    li		$t1, 1		# $t1 = 0
    

loop:
    bgt		$t1, $t0, end	# if $t1 > $t0 then end
    
    move 	$a0, $t1		# $a0 = $t1
    li		$v0, 1		# $v0 = 1
    syscall


    li   $a0, '\n'    # printf("%c", '\n');
    li   $v0, 11
    syscall

    # counter++
    addi	$t1, $t1, 1			# $t1 = $t1 1 0
    

    j		loop				# jump to loop
    

end:
    jr   $ra          # return

    .data
stringPrintf:
    .asciiz "Enter a number: "
