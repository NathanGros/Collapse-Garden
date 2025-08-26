make :
	gcc main.c types.c backend.c movement.c drawing.c -o main.exe -lraylib -lm
	./main.exe
