main:
    # x[3] = 17;
    li		$t0, 3		# $t0 = 3
    # 4 bytes in int
    mul     $t0, $t0, 4

    la		$t1, x		# The address of array x
    # Move to x[3]
    add		$t2, $t1, $t0		# $t2 = address of x[3]
    
    li		$t3, 17		# $t3 = 17
    sw		$t3, ($t2)		# 
    
    # ...

.data:
# int x[10];
x:  .space 40