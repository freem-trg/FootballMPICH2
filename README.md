Учебная задача по параллельному программированию.

На чемпионате мира по футболу используется электронный мяч.  На поле   22
игрока, по 11 в каждой команде. Каждый игрок бьет по мячу со случайной силой (в ньютонах)
5 раз. Мяч получает удары и определяет, с какой силой его ударили, и игрок какой команды
это сделал. Мяч рассчитывает суммарную силу ударов игроков первой и второй команд. В
конце матча, получив 110 ударов, мяч сообщает, игроки какой команды сильнее били по нему

Compiling:
mpicxx football.cpp

Executing:
mpirun -n 23 ./a.out
