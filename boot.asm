[org 0x7c00]

mov [diskNumber], dl

mov ah, 2            ; Obavezno
mov al, 1            ; Broj sektorta koji hocemo da citamo
mov ch, 0            ; Iz kog cilindra citamo
mov cl, 2            ; Sektor iz kog krecemo citanje (i on se cita)
mov dh, 0            ; Koji hed koristimo za citanje
mov dl, [diskNumber] ; Broj diska sa kog citamo (u slucaju da je na racunar nakaceno vise diskova)
; mov es, 0         ; Koristi se za dostizanja vecih adresa koje ne mogu da se predstave sa 16 bita
mov bx, 0x7e00       ; Adresa od koje stavljameo podatke sa diska

int 0x13

mov ah, 0x0e         ; Potrebno za pisanje karaktera na ekran

mov al, [0x7e00]     ; Stavaljamo vrednost koju hocemo da prikazemo u registar
int 0x10             ; Prikazi karakter iz registra al na ekran

diskNumber: db 0

times 510 - ($ - $$) db 0
db 0x55, 0xaa

db "vuckoo0"