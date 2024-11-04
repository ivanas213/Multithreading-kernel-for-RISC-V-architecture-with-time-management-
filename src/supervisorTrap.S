.extern _ZN5Riscv20handleSupervisorTrapEv  # External reference to the handleSupervisorTrap function

.align 4  # Align the code to a 4-byte boundary
.global _ZN5Riscv14supervisorTrapEv  # Make the function globally accessible
.type _ZN5Riscv14supervisorTrapEv, @function  # Define the type of symbol as a function

_ZN5Riscv14supervisorTrapEv:
    # Adjust the stack pointer to create space for saving registers (256 bytes)
    addi sp, sp, -256

    # Save all registers (x0 to x31) onto the stack
    .irp index, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd x\index, \index * 8(sp)  # Store each register at its respective position in the stack
    .endr  # End of repeat block for saving registers

    # Call the supervisor trap handler (RISC-V specific)
    call _ZN5Riscv20handleSupervisorTrapEv  # Call the function to handle supervisor traps

    # Save the return value (a0 register) into the stack at the 10th register position
    sd a0, 10*8(sp);

    # Restore all registers (x0 to x31) from the stack
    .irp index, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld x\index, \index * 8(sp)  # Load each register from the stack back into the CPU
    .endr  # End of repeat block for loading registers

    # Adjust the stack pointer back to its original position (deallocate space for registers)
    addi sp, sp, 256

    # Return from the supervisor trap (this is a RISC-V specific instruction)
    sret  # Return to the program execution from the trap
