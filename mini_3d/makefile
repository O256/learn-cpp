all: mini3d.exe

mini3d.exe: mini3d.c
	gcc -o mini3d.exe mini3d.c -lgdi32

clean:
# windows
	del mini3d.exe

run: mini3d.exe
	./mini3d.exe	
