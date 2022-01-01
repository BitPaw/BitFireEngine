DirExport = "__Export__"
DirTemp = "__Temp__"

#-------------------------------------------------------------------------------------------------
$(DirExport)/MakeFileGenerator.run: $(DirTemp)/MakeFileGenerator.o
	g++ $(DirTemp)/MakeFileGenerator.o -o $(DirExport)/MakeFileGenerator.run
	chmod +x $(DirExport)/MakeFileGenerator.run

$(DirTemp)/MakeFileGenerator.o: MakeFileGenerator.cpp
	@echo "[#] Compiling file MakeFileGenerator.cpp"
	mkdir $(DirExport)
	mkdir $(DirTemp)
	g++ -std=c++17 -c MakeFileGenerator.cpp -o $(DirTemp)/MakeFileGenerator.o


#-------------------------------------------------------------------------------------------------
