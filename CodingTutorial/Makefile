##################################
# simple Makefile for ACO course #
##################################

# pick your favourite compiler
COMPILER	=	gcc

# flags you want to use when compiling
FLAGS		=	-O2 -fopenmp #-g

# system-wide libraries you like to link to
LIBRARIES	=	-lm 

# your code might be split into several C-files; here you specify which...
OBJECTS		=	utility.o my.o

# and it might be the best to actually put all those auxiliary files into a single library
MY_LIBRARY	=	libACO.a

##########################################################################################
# general syntax for the 'rules':                                                        #
#                                                                                        #
# rulename: all_the files_the_rule depends_on $(OBJECTS)                                 #
#   "TAB"  $(COMPILER) $(FLAGS) -o outputname name_of_C_file.c   $(OBJECTS) $(LIBRARIES) #
#          ^^^^^^^^^^^^^^^^^^^^                                  ^^^^^^^^^^^^^^^^^^^^^^^ #
#           compilation stuff                                         linking stuff      #
#                                                                                        #
#                                                                                        #
# objectfile.o: all_the files_the_objectfile depends_on                                  #
#   "TAB"  $(COMPILER) $(FLAGS) -c name_of_C_file.c   $(LIBRARIES)                       #
#                                                                                        #
##########################################################################################

# the rules for how to make all the relevant files
test00:	HelloWorld.c
	$(COMPILER) $(FLAGS) -o HelloWorld HelloWorld.c  $(LIBRARIES)

test01:	stdint.c
	$(COMPILER) $(FLAGS) -o stdint stdint.c  $(LIBRARIES)

test02:	foverflow.c
	$(COMPILER) $(FLAGS) -o foverflow foverflow.c  $(LIBRARIES)

test03:	Pointer.c
	$(COMPILER) $(FLAGS) -o Pointer Pointer.c  $(LIBRARIES)

test04:	Array1D.c $(OBJECTS)                 # we are not using our own library libACO.a but instead the collection of object files
	$(COMPILER) $(FLAGS) -o Array1D Array1D.c $(OBJECTS) $(LIBRARIES) 

test05:	Array3D.c $(MY_LIBRARY)              # we are first constructing our own library and then using it during linking
	$(COMPILER) $(FLAGS) -o Array3D Array3D.c $(MY_LIBRARY) $(LIBRARIES)

test06:	ParallelRecursion1D.c $(MY_LIBRARY)  # we are again constructing our own library, but then also using it like a system-wide library
	$(COMPILER) $(FLAGS) -o ParallelRecursion1D ParallelRecursion1D.c  $(LIBRARIES) -lACO -L./

test07:	Structure.c $(OBJECTS)
	$(COMPILER) $(FLAGS) -o Structure Structure.c $(OBJECTS) $(LIBRARIES)

test08: StructureArray.c $(OBJECTS)
	$(COMPILER) $(FLAGS) -o StructureArray StructureArray.c  $(OBJECTS) $(LIBRARIES)

test09: StructurePointer.c $(OBJECTS)
	$(COMPILER) $(FLAGS) -o StructurePointer StructurePointer.c $(OBJECTS) $(LIBRARIES)

test10: FunctionPointer.c $(OBJECTS)
	$(COMPILER) $(FLAGS) -o FunctionPointer FunctionPointer.c  $(OBJECTS) $(LIBRARIES)

test11:	indexx.c $(OBJECTS)
	$(COMPILER) $(FLAGS) -o indexx indexx.c $(OBJECTS) $(LIBRARIES)

test12: qsort.c $(OBJECTS)
	$(COMPILER) $(FLAGS) -o qsort qsort.c $(OBJECTS) $(LIBRARIES)

test13:	IO.c $(OBJECTS)
	$(COMPILER) $(FLAGS) -o IO IO.c $(OBJECTS) $(LIBRARIES)

test14:	read_mtree.c $(OBJECTS)
	$(COMPILER) $(FLAGS) -o read_mtree read_mtree.c $(OBJECTS) $(LIBRARIES)

test15:	valgrindtest.c $(OBJECTS)
	$(COMPILER) $(FLAGS) -o valgrindtest valgrindtest.c $(OBJECTS) $(LIBRARIES)

galaxyGC: galaxyGC.c $(OBJECTS)
	$(COMPILER) $(CFLAGS) -o galaxyGC galaxyGC.c $(OBJECTS) $(LIBRARIES)

# our very own library
utility.o:	utility.c utility.h
	$(COMPILER) $(FLAGS) -c utility.c $(LIBRARIES)

my.o:		my.c
	$(COMPILER) $(FLAGS) -c my.c $(LIBRARIES)

libACO.a: $(OBJECTS)
	ar -r libACO.a $(OBJECTS)

# remove everything that is not needed and allow for a fresh compilation of everything
clean:
	rm -rf *.o libACO.a *.dSYM rm -f HelloWorld stdint foverflow Pointer Array1D Array3D ParallelRecursion1D ParallelRecursion1Dimproved Structure StructureArray FunctionPointer StructurePointer indexx qsort IO valgrindtest read_mtree galaxyGC pi gravity1D-parallel
