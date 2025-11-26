tableur: main.c liste.c
	gcc -o test main.c liste.c




	gcc -Wall -Wextra -std=c11 -g -Icellules -Iliste -Istack cellules\graphe_test.c cellules\graphe.c cellules\cellules.c liste\liste.c stack\stack.c -o graphe_test.exe