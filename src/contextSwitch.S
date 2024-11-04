.global _ZN3TCB13contextSwitchEPNS_7ContextES1_
.type _ZN3TCB13contextSwitchEPNS_7ContextES1_, @function
_ZN3TCB13contextSwitchEPNS_7ContextES1_:
    sd ra, 0 * 8(a0)       # Save the return address (ra) from the current context into the memory pointed by a0.
    sd sp, 1 * 8(a0)       # Save the stack pointer (sp) from the current context into the memory pointed by a0.

    ld ra, 0 * 8(a1)       # Load the return address (ra) from the new context (pointed by a1).
    ld sp, 1 * 8(a1)       # Load the stack pointer (sp) from the new context (pointed by a1).

    ret                    # Return to the address stored in ra (from the new context).
