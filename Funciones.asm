section .text

global actualizarPuntuacion
;int actualizarPuntuacion(int scoreActual, int valorExtra)
;devuelve scoreActual + valorExtra
actualizarPuntuacion:
    mov eax, edi
    add eax, esi
    ret

global actualizarVidas
;int actualizarVidas(int vidasActuales, int vidasParaModificar)
;edi = vidasActuales 
;esi = vidas (+1 o -1)

actualizarVidas:
    mov eax, edi
    add eax, esi
    cmp eax, 0
    jge checkMax
    mov eax, 0 ;si es menor ya se murio
    jmp fin
checkMax:
    cmp eax, 3 
    jle fin
    mov eax, 3 ;si la cantidad de vidas supera 3, solo lo pone en 3
fin:
    ret