#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


#include<stdint.h>

void default_handler();
void divide_by_zero_fault (uint32_t eip, uint32_t cs, uint32_t flags) ;
void single_step_trap (uint32_t cs, uint32_t eip, uint32_t flags) ;
void nmi_trap (uint32_t cs, uint32_t eip, uint32_t flags);
void breakpoint_trap (uint32_t cs, uint32_t eip, uint32_t flags) ;
void overflow_trap (uint32_t cs, uint32_t eip, uint32_t flags) ;
void bounds_check_fault (uint32_t cs, uint32_t  eip, uint32_t flags) ;
void invalid_opcode_fault (uint32_t cs, uint32_t  eip, uint32_t flags) ;
void no_device_fault (uint32_t cs, uint32_t eip, uint32_t flags) ;
void double_fault_abort (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  ;
void invalid_tss_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err) ;
void no_segment_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  ;
void stack_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  ;
void general_protection_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  ;
void page_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err) ;
void fpu_fault  (uint32_t cs, uint32_t  eip, uint32_t flags)  ;
void alignment_check_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err) ;
void machine_check_abort (uint32_t cs, uint32_t  eip, uint32_t flags)  ;
void simd_fpu_fault (uint32_t cs, uint32_t  eip, uint32_t flags)  ;
#endif
