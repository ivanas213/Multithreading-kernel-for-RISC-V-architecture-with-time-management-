.global _ZN5Riscv13pushRegistersEv
.type _ZN5Riscv13pushRegistersEv, @function
_ZN5Riscv13pushRegistersEv:
    addi sp, sp, -256             # Allocate 256 bytes on the stack to store registers x3 to x31.
    
    # Loop over registers x3 to x31 and store each on the stack.
    .irp index, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
        sd x\index, \index * 8(sp)  # Save register x\index at offset (\index * 8) bytes on the stack.
    .endr
    
    ret                            # Function return, with all registers saved on the stack.

.global _ZN5Riscv12popRegistersEv
.type _ZN5Riscv12popRegistersEv, @function
_ZN5Riscv12popRegistersEv:

    # Loop over registers x3 to x31 and load each from the stack to restore them.
    .irp index, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
        ld x\index, \index * 8(sp)  # Load register x\index from offset (\index * 8) bytes on the stack.
    .endr
    
    addi sp, sp, 256               # Restore stack pointer by deallocating the 256 bytes used.
    ret                            # Function return, with all registers restored.
