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
    jmp fin1
checkMax:
    cmp eax, 3 
    jle fin1
    mov eax, 3 ;si la cantidad de vidas supera 3, solo lo pone en 3
fin1:
    ret



global calcularVelocidad
;int calcularVelocidad(int score)
;Entrada: edi = score
;Salida: eax = velocidad nueva
;velocidad = -6 - (score / 50)
;velocidad mínima = -15

calcularVelocidad:
    mov eax, edi        ; eax = score
    mov ecx, 50
    cdq
    idiv ecx            ; eax = score / 100

    neg eax
    sub eax, 6

    cmp eax, -15
    jge fin2

    mov eax, -15        ; limite máximo de velocidad

fin2:
    ret