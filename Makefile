make :
	gcc main.c structures.c models.c backend.c movement.c drawing.c -o main.exe -lraylib -lm
	./main.exe
