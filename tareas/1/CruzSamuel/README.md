# Tarea 1: Minishell básica

**Estudiante:** Cruz Macedo Samuel Santiago
**Materia:** Sistemas Operativos

## Cómo correrlo
Solo necesitas tener Python 3 instalado. Ejecutas en la terminal:
`python3 minishell.py`

## Diseño del programa
El programa es un bucle que siempre está esperando que escribas algo. Lo más importante que hice fue:
1. **Parseo:** Usé un `.split()` simple para separar el comando de los argumentos. No maneja comillas raras, pero para comandos normales funciona perfecto.
2. **Procesos:** Uso `os.fork()` para crear una copia del proceso. El hijo es el que hace el `execvp` y el padre se queda esperando con `waitpid`.
3. **Señales:** - Puse un manejador para `SIGCHLD` para que los procesos hijo no se queden como "zombies" en el sistema. 
   - Hice que el padre ignore el `SIGINT` (Ctrl+C) para que no se me cierre la shell cada que quiero matar un comando. El hijo sí lo recibe porque le reseteo la señal antes del exec.

## Dificultades
Al principio no sabía por qué se me cerraba la shell al picar Ctrl+C, pero luego vi que las señales se heredan al hijo, así que tuve que investigar cómo hacer que el padre las ignore y el hijo no. 

También me dio lata lo de `os.waitpid` en el manejador de `SIGCHLD`, porque si no usaba `WNOHANG`, a veces la shell se sentía "lenta" o se quedaba esperando algo que ya había terminado.