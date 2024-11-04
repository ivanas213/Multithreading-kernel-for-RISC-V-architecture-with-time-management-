.global copy_and_swap
copy_and_swap:
    lr.w t0, (a0)          # Load the original value from the memory location pointed by a0.
    bne t0, a1, fail       # If the original value (t0) does not match the expected (a1), jump to fail.
    sc.w t0, a2, (a0)      # Attempt to store the desired value (a2) into memory. Store result in t0.
    bnez t0, copy_and_swap # If store-conditional failed (t0 is not zero), retry.
    li a0, 0               # Set a0 to 0, indicating success.
    jr ra                  # Return to the address stored in the return address register (ra).
fail:
    li a0, 1               # Set a0 to 1, indicating failure.
    jr ra                  # Return to the address stored in the return address register (ra).
