make :
	gcc main.c types.c drawing.c -o main.exe -lraylib -lm
	./main.exe
