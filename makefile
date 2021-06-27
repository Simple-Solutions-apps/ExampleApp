CC = x86_64-w64-mingw32-gcc.exe
CFlags = -Wall -O2

DirSrc = .\src
DirObj= .\obj
DirRes = .\res
DirBin = .\bin
DirLib = .\lib

APP = $(DirBin)\ExampleApp.exe

srcMain = $(DirSrc)\main.c
srcMsgBoxes = $(DirSrc)\MsgBoxes.c
srcCallbacks = $(DirSrc)\callbacks.c
srcFunctions = $(DirSrc)\functions.c
srcResources = $(DirRes)\main.rc

objMain = $(DirObj)\main.o
objMsgBoxes = $(DirObj)\MsgBoxes.o
objControls = $(DirObj)\controls.o
objCallbacks = $(DirObj)\callbacks.o
objResources = $(DirObj)\resources.o

dllCommCtrls = $(DirLib)\comctl32.dll

objs = $(objMain) $(objMsgBoxes) $(objControls) $(objCallbacks) $(objResources)

$(objMain): $(srcMain)
	$(CC) $(CFlags) -c $(srcMain) -o $(objMain)
$(objCallbacks): $(srcCallbacks)
	$(CC) $(CFlags) -c $(srcCallbacks) -o $(objCallbacks)
$(objControls): $(srcControls)
	$(CC) $(CFlags) -c $(srcControls) -o $(objControls)
$(objMsgBoxes): $(srcMsgBoxes)
	$(CC) $(CFlags) -c $(srcMsgBoxes) -o $(objMsgBoxes)
$(objResources): $(srcResources)
	windres.exe $(srcResources) -o $(objResources)

build: $(objs)
	$(CC) -o $(APP) $(objs) $(dllCommCtrls) -s -mwindows
	$(APP)
clean:
	del *.o *.exe
run:
	$(APP)
rebuild:
	make clean
	make build