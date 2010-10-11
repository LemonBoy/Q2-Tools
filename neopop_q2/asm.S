.arm
.text

.global drawScreen
.global BGR2RGB

@ Transform the BGR value into a RGB one
@ r0 = color
@ ret = converted color

BGR2RGB:
    stmdb sp!, {r1-r3}
    and r1, r0, #0x1F       @ Extract the R
    lsr r0, r0, #5
    and r2, r0, #0x1F       @ Extract the G
    lsr r0, r0, #5
    and r3, r0, #0x1F       @ Extract the B
    orr r0, r3, r1, lsl #11 @ Mix the B and the R
    orr r0, r0, r2, lsl #6  @ Mix with the G
    ldmia sp!, {r1-r3}
    bx lr

@ Draw the screen in thee fastest way possible
@ r0 = framebuffer
@ r1 = neopop buffer

drawScreen:
    stmdb sp!, {r0-r12, lr}
    ldr lr, =152        @ Rows
_drawRowStart:
    mov r2, #8          @ Pass to do for completing a row
_drawRowLoop:
    ldmia r1!, {r3-r12} @ Read
    stmia r0!, {r3-r12} @ Write
    subs r2, r2, #1     @ Last one ?
    bne _drawRowLoop
_drawNextRow:
    add r0, r0, #160    @ Complete the row
    subs lr, lr, #1
    bne _drawRowStart   @ Draw the next row
    ldmia sp!, {r0-r12, lr}
    bx lr
