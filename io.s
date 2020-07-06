global outb        		; make the label outb visible outside 
; outb - send a byte to an I/O port
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp    ] return address
outb:
	mov al, [esp + 8]    ; move the data to be sent into al 
	mov dx, [esp + 4]    ; move the address of the I/O port into dx 
	out dx, al           ; send the data to the I/O port
	ret                  ; return to the calling function


global inb
; inb - send a byte from the given I/O port
; stack: [esp + 4] the address of the I/O port
;        [esp] return address
inb:
    mov dx, [esp + 4]
    in al, dx
    ret
