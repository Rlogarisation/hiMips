# Read a number and print positive multiples of 7 or 11 < n

main:                  # int main(void) {

    la   $a0, stringPrintf   # printf("Enter a number: ");
    li   $v0, 4
    syscall

    li   $v0, 5         # scanf("%d", number);
    syscall

    # Assign $t0 as the input number
    move 	$t0, $v0	# $t0 = v0
    # Initial a counter = 0
    li		$t1, 1		# $t1 = 0
    
    
loop:
    # Exit loop 
    bge		$t1, $t0, end	# if $t1 >= t0 then end
    
    # $t2 = counter % 7
    rem     $t2, $t1, 7
    # If $t2 == 0
    beq		$t2, 0, print # if $t2 =0 then print

    # $t3 = counter % 11
    rem     $t3, $t1, 11
    beq		$t3, 0, print	# if $t3 == 0 then print
    
    # counter++;
    add		$t1, $t1, 1		
    
    j		loop				# jump to loop
    
print:
    move	$a0, $t1		# $a0 = $t1
    li		$v0, 1		# $v0 = 1
    syscall

    li		$a0, '\n'		# $a0 = '\n'
    li		$v0, 11		# $v0 = 11
    syscall

    add		$t1, $t1, 1		

    j		loop				# jump to loop
    

end:
    jr   $ra           # return

    .data
stringPrintf:
    .asciiz "Enter a number: "
