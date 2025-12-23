<p align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/badges/minishellm.png" alt="Minishell Badge"/>
</p>

<h1 align="center">🐚 Minishell</h1>

<p align="center">
  <strong>As beautiful as a shell</strong><br>
  Un intérprete de comandos UNIX minimalista desarrollado desde cero
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" />
  <img src="https://img.shields.io/badge/Standard-POSIX-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/School-42_Madrid-black?style=for-the-badge&logo=42" />
</p>

---

## 📋 Tabla de Contenidos

- [Sobre el Proyecto](#-sobre-el-proyecto)
- [Características](#-características)
- [Requisitos](#-requisitos)
- [Instalación](#-instalación)
- [Uso](#-uso)
- [Built-ins Implementados](#-built-ins-implementados)
- [Características Técnicas](#-características-técnicas)
- [Ejemplos](#-ejemplos)
- [Estructura del Proyecto](#-estructura-del-proyecto)
- [Recursos](#-recursos)

---

## 🎯 Sobre el Proyecto

**Minishell** es un proyecto del cursus de 42 que consiste en crear un intérprete de comandos simple inspirado en bash. El objetivo es comprender en profundidad cómo funciona un shell UNIX, desde el parsing de comandos hasta la ejecución de procesos, pasando por la gestión de señales y redirecciones.

Este proyecto profundiza en conceptos fundamentales de sistemas operativos como:
- Creación y gestión de procesos (`fork`, `execve`, `wait`)
- Comunicación entre procesos mediante pipes
- Manejo de señales UNIX
- Gestión de descriptores de archivo
- Variables de entorno

---

## ✨ Características

### Funcionalidades Core
- ✅ Prompt interactivo que muestra el estado del shell
- ✅ Historial de comandos navegable
- ✅ Búsqueda y ejecución de comandos usando `PATH`
- ✅ Variables de entorno (`$VAR`, `$?`)
- ✅ Gestión de comillas simples (`'`) y dobles (`"`)
- ✅ Expansión de variables dentro de comillas dobles
- ✅ Exit status del último comando ejecutado (`$?`)

### Redirecciones
- ✅ Redirección de entrada: `<`
- ✅ Redirección de salida: `>`
- ✅ Redirección de salida en modo append: `>>`
- ✅ Here document: `<<`

### Pipes y Comandos Encadenados
- ✅ Pipes (`|`) para encadenar comandos
- ✅ Soporte para múltiples pipes en una sola línea

### Señales
- ✅ `Ctrl-C`: Interrumpe el comando actual y muestra un nuevo prompt
- ✅ `Ctrl-D`: Sale del shell (EOF)
- ✅ `Ctrl-\`: No hace nada (ignorado)

---

## 🛠️ Requisitos

- **Sistema Operativo**: Linux o macOS
- **Compilador**: `gcc` o `clang`
- **Make**: Para automatizar la compilación
- **Librerías**:
  - `readline` (para el historial y edición de línea)

### Instalación de dependencias

**En Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install build-essential libreadline-dev
```

**En macOS:**
```bash
brew install readline
```

---

## 📦 Instalación

```bash
# Clonar el repositorio
git clone https://github.com/madel-04/minishell.git
cd minishell

# Compilar el proyecto
make

# Ejecutar minishell
./minishell
```

### Comandos Make disponibles

```bash
make        # Compila el proyecto
make clean  # Elimina archivos objeto
make fclean # Elimina archivos objeto y el ejecutable
make re     # Recompila el proyecto desde cero
```

---

## 🚀 Uso

Una vez ejecutado el programa, se mostrará el prompt del shell:

```bash
minishell$ 
```

### Comandos básicos

```bash
minishell$ echo "Hello World"
Hello World

minishell$ pwd
/home/user/minishell

minishell$ ls -la | grep minishell | wc -l
42

minishell$ export USER=mayte
minishell$ echo $USER
mayte

minishell$ exit
```

---

## 🔧 Built-ins Implementados

Los siguientes comandos están implementados como built-ins (no llaman a ejecutables externos):

| Comando | Descripción |
|---------|-------------|
| `echo` | Imprime argumentos en la salida estándar (con opción `-n`) |
| `cd` | Cambia el directorio actual |
| `pwd` | Imprime el directorio de trabajo actual |
| `export` | Establece variables de entorno |
| `unset` | Elimina variables de entorno |
| `env` | Muestra todas las variables de entorno |
| `exit` | Sale del shell con un código de salida opcional |

---

## 🏗️ Características Técnicas

### Parsing
- **Tokenización**: Separación de la entrada en tokens (palabras, operadores, redirecciones)
- **Análisis sintáctico**: Construcción de una estructura de comandos ejecutable
- **Expansión**: Procesamiento de variables de entorno y comillas

### Ejecución
- **Gestión de procesos**: Uso de `fork()` para crear procesos hijos
- **Búsqueda de ejecutables**: Búsqueda en `PATH` o rutas absolutas/relativas
- **Pipes**: Comunicación entre procesos mediante `pipe()` y duplicación de descriptores

### Redirecciones
- **Entrada/Salida**: Uso de `dup2()` para redirigir `stdin` y `stdout`
- **Here document**: Lectura de entrada hasta un delimitador

### Señales
- **Signal handling**: Uso de `signal()` o `sigaction()` para manejar `SIGINT` y `SIGQUIT`
- **Comportamiento diferenciado**: Las señales se comportan diferente en modo interactivo vs. ejecución

---

## 💡 Ejemplos

### Redirecciones

```bash
# Redirección de entrada
minishell$ cat < input.txt

# Redirección de salida
minishell$ ls -l > output.txt

# Append a archivo
minishell$ echo "nueva línea" >> output.txt

# Here document
minishell$ cat << EOF
> línea 1
> línea 2
> EOF
línea 1
línea 2
```

### Pipes

```bash
# Pipe simple
minishell$ ls | grep .c

# Múltiples pipes
minishell$ cat file.txt | grep "pattern" | wc -l

# Con redirecciones
minishell$ < input.txt grep "search" | sort | uniq > output.txt
```

### Variables de entorno

```bash
# Exportar variable
minishell$ export NAME="Mayte"
minishell$ echo $NAME
Mayte

# Usar variable en comando
minishell$ export DIR=/home/user
minishell$ cd $DIR

# Exit status
minishell$ ls /nonexistent
ls: cannot access '/nonexistent': No such file or directory
minishell$ echo $?
2
```

### Comillas

```bash
# Comillas simples (no expanden)
minishell$ echo '$USER'
$USER

# Comillas dobles (expanden variables)
minishell$ echo "$USER is working"
mayte is working

# Mezcladas
minishell$ echo "My name is '$USER'"
My name is 'mayte'
```

---

## 📁 Estructura del Proyecto

```
minishell/
├── Makefile
├── includes/
│   └── minishell.h       # Cabeceras y estructuras principales
├── src/
│   ├── main.c            # Punto de entrada del programa
│   ├── parsing/          # Módulos de parsing y tokenización
│   │   ├── lexer.c
│   │   ├── parser.c
│   │   └── expander.c
│   ├── execution/        # Módulos de ejecución
│   │   ├── executor.c
│   │   ├── pipes.c
│   │   └── redirections.c
│   ├── builtins/         # Implementación de built-ins
│   │   ├── echo.c
│   │   ├── cd.c
│   │   ├── pwd.c
│   │   ├── export.c
│   │   ├── unset.c
│   │   ├── env.c
│   │   └── exit.c
│   ├── signals/          # Gestión de señales
│   │   └── signals.c
│   └── utils/            # Funciones auxiliares
│       ├── env_utils.c
│       ├── error.c
│       └── free.c
└── libft/                # Librería personalizada de funciones C
```

---

## 📚 Recursos

### Documentación oficial
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)

### System calls relevantes
- `fork(2)` - Crear proceso hijo
- `execve(2)` - Ejecutar programa
- `wait(2)` / `waitpid(2)` - Esperar a proceso hijo
- `pipe(2)` - Crear pipe
- `dup2(2)` - Duplicar descriptor de archivo
- `open(2)` / `close(2)` - Abrir/cerrar archivos
- `signal(2)` / `sigaction(2)` - Manejar señales

### Librerías
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)

---

## 🎓 Aprendizajes Clave

Este proyecto me permitió desarrollar una comprensión profunda de:

- **Gestión de procesos**: Creación, sincronización y comunicación entre procesos
- **Descriptores de archivo**: Manipulación y redirección de flujos de entrada/salida
- **Parsing de texto**: Diseño e implementación de un lexer y parser funcional
- **Gestión de memoria**: Prevención de memory leaks en un programa complejo
- **Señales UNIX**: Manejo de interrupciones y comportamiento asíncrono
- **Debugging**: Uso de herramientas como `valgrind` y `gdb` para depuración avanzada

---

## 👥 Autores

- **Mayte** - [@madel-04](https://github.com/madel-04)
- **Miguel** - [@MiMendiola](https://github.com/MiMendiola)

---

## 📄 Licencia

Este proyecto es parte del cursus de 42 Madrid y está sujeto a sus normas académicas.

---

<p align="center">
  <sub>Desarrollado con 💻 en 42 Madrid</sub>
</p>
