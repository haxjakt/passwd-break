# Lucrarea 5: Generator de parole
## Tema
Implementati in C sun Unix/Linux generatorul de parole

## Compile
<code>gcc break.c -lcrypt -o break</code>

## Run
openssl passwd -6 <b>your_password</b> | ./break
