;draw image in MBR
;
;Skid by sleepmod
;thanks sleepmod
bits 16
org 0x7C00

segclear:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00
    mov bp, sp
    sti
    
start:
    mov ax, 0x13
    int 0x10
    
readdisk:
    mov ah, 0x42
    mov si, bootdap
    int 0x13
    jmp $
bootdap:
    db 0x10
    db 0
    dw (filled - image)  / 512 + 1
    dw 0x0000, 0xA000
    dq 1
booterrored: ;i think its computer boot errored partern...
    mov ah, 0x0e
    mov al, "X"
    int 0x10
    jmp stop ;stop it
stop:
    hlt ;system halted!

times 510 - ($-$$) db 0
dw 0xAA55 ;signature

image: incbin "C:\micro\MBR.vad";image only .vad, get to VGApainter (if you build this file(.bin) please paste image to directory. (dont paste = error))
filled: times 510 - ($-$$) % 512 db 0