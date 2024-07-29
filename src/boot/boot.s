    .section    .vectors
    .align      16
    .org        0
    .global     __vectors
__vectors:
    .literal_position
    
    .org        0x50
__vec_user_excp:
    j       __vec_user_excp_handler
    
    # Some offset for now to allow other vectors to fit in
    .org        0x100
    .section    .vectors
__vec_user_excp_handler:
    addi    a1, a1, -24
    s32i    a0, a1, 4
    rsr     a0, ps
    s32i    a0, a1, 8
    rsr     a0, epc1
    s32i    a0, a1, 12
    call0   _vec_user_excp
    l32i    a0, a1, 8
    wsr     a0, ps
    l32i    a0, a1, 12
    wsr     a0, epc1
    l32i    a0, a1, 4
    addi    a1, a1, 24
    rsync
    rfe

    .section .boot.startup
    .global __boot_startup
    .literal_position
__boot_startup:
    movi    a0, __vectors # relocate vector table
    wsr     a0, vecbase
    call0   _boot
