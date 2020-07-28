terasort: CommandLineArguments.o Mapper.o parallel_terasort.o Partition.o Partitioner.o QuickSort.o Reducer.o TeraSort.o TeraSortItem.o
	g++ -pthread CommandLineArguments.o Mapper.o parallel_terasort.o Partition.o Partitioner.o QuickSort.o Reducer.o TeraSort.o TeraSortItem.o -o terasort
CommandLineArguments.o: CommandLineArguments.cpp
	g++ -c CommandLineArguments.cpp -o CommandLineArguments.o
Mapper.o: Mapper.cpp
	g++ -c Mapper.cpp -o Mapper.o
parallel_terasort.o: parallel_terasort.cpp
	g++ -c parallel_terasort.cpp -o parallel_terasort.o
Partitioner.o: Partitioner.cpp
	g++ -c Partitioner.cpp -o Partitioner.o
Partition.o: Partition.cpp
	g++ -c Partition.cpp -o Partition.o
QuickSort.o: QuickSort.cpp
	g++ -c QuickSort.cpp -o QuickSort.o
Reducer.o: Reducer.cpp
	g++ -c Reducer.cpp -o Reducer.o
TeraSort.o: TeraSort.cpp
	g++ -c TeraSort.cpp -o TeraSort.o
TeraSortItem.o: TeraSortItem.cpp
	g++ -c TeraSortItem.cpp -o TeraSortItem.o