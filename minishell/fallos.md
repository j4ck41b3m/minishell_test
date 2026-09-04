Cosas a arreglar:

- comando no encontrado
- leaks al ejecutar `.` y `..`
- pipe con un builtin `exit | exit`
- error al borrar una carpeta de un nivel anterior

valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.supp --track-fds=yes ./minishell