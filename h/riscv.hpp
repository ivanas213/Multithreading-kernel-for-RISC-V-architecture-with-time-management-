//
// Created by ivana
//

#ifndef OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_RISCV_HPP
#define OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_RISCV_HPP

#include "../lib/hw.h"

class Riscv
{
public:

    // Save registers x3 through x31 on the stack.
    static void pushRegisters();

    // Restore registers x3 through x31 from the stack.
    static void popRegisters();

    // Clear bits sstatus.spp and sstatus.spie (non-inline function).
    static void popSppSpie();

    // Read value from scause register.
    static uint64 r_scause();

    // Write value to scause register.
    static void w_scause(uint64 scause);

    // Read value from sepc register.
    static uint64 r_sepc();

    // Write value to sepc register.
    static void w_sepc(uint64 sepc);

    // Read value from stvec register.
    static uint64 r_stvec();

    // Write value to stvec register.
    static void w_stvec(uint64 stvec);

    // Read value from stval register.
    static uint64 r_stval();

    // Write value to stval register.
    static void w_stval(uint64 stval);

    // Enum for masking bits in sip register.
    enum BitMaskSip
    {
        SIP_SSIP = (1 << 1),
        SIP_STIP = (1 << 5),
        SIP_SEIP = (1 << 9),
    };

    // Set mask for sip register.
    static void ms_sip(uint64 mask);

    // Clear mask for sip register.
    static void mc_sip(uint64 mask);

    // Read value from sip register.
    static uint64 r_sip();

    // Write value to sip register.
    static void w_sip(uint64 sip);

    // Enum for masking bits in sstatus register.
    enum BitMaskSstatus
    {
        SSTATUS_SIE = (1 << 1),
        SSTATUS_SPIE = (1 << 5),
        SSTATUS_SPP = (1 << 8),
    };

    // Set mask for sstatus register.
    static void ms_sstatus(uint64 mask);

    // Clear mask for sstatus register.
    static void mc_sstatus(uint64 mask);

    // Read value from sstatus register.
    static uint64 r_sstatus();

    // Write value to sstatus register.
    static void w_sstatus(uint64 sstatus);

    // Handle supervisor trap.
    static void supervisorTrap();

private:

    // Private supervisor trap handler.
    static void handleSupervisorTrap();
};

// Inline functions to directly access specific RISC-V registers.

inline uint64 Riscv::r_scause()
{
    uint64 volatile scause;
    __asm__ volatile ("csrr %[scause], scause" : [scause] "=r"(scause));
    return scause;
}

inline void Riscv::w_scause(uint64 scause)
{
    __asm__ volatile ("csrw scause, %[scause]" : : [scause] "r"(scause));
}

inline uint64 Riscv::r_sepc()
{
    uint64 volatile sepc;
    __asm__ volatile ("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
    return sepc;
}

inline void Riscv::w_sepc(uint64 sepc)
{
    __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));
}

inline uint64 Riscv::r_stvec()
{
    uint64 volatile stvec;
    __asm__ volatile ("csrr %[stvec], stvec" : [stvec] "=r"(stvec));
    return stvec;
}

inline void Riscv::w_stvec(uint64 stvec)
{
    __asm__ volatile ("csrw stvec, %[stvec]" : : [stvec] "r"(stvec));
}

inline uint64 Riscv::r_stval()
{
    uint64 volatile stval;
    __asm__ volatile ("csrr %[stval], stval" : [stval] "=r"(stval));
    return stval;
}

inline void Riscv::w_stval(uint64 stval)
{
    __asm__ volatile ("csrw stval, %[stval]" : : [stval] "r"(stval));
}

inline void Riscv::ms_sip(uint64 mask)
{
    __asm__ volatile ("csrs sip, %[mask]" : : [mask] "r"(mask));
}

inline void Riscv::mc_sip(uint64 mask)
{
    __asm__ volatile ("csrc sip, %[mask]" : : [mask] "r"(mask));
}

inline uint64 Riscv::r_sip()
{
    uint64 volatile sip;
    __asm__ volatile ("csrr %[sip], sip" : [sip] "=r"(sip));
    return sip;
}

inline void Riscv::w_sip(uint64 sip)
{
    __asm__ volatile ("csrw sip, %[sip]" : : [sip] "r"(sip));
}

inline void Riscv::ms_sstatus(uint64 mask)
{
    __asm__ volatile ("csrs sstatus, %[mask]" : : [mask] "r"(mask));
}

inline void Riscv::mc_sstatus(uint64 mask)
{
    __asm__ volatile ("csrc sstatus, %[mask]" : : [mask] "r"(mask));
}

inline uint64 Riscv::r_sstatus()
{
    uint64 volatile sstatus;
    __asm__ volatile ("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));
    return sstatus;
}

inline void Riscv::w_sstatus(uint64 sstatus)
{
    __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
}

#endif
