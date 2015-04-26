mpicc -o process process_card.c
mpicc -o reading reading_cards.c
mpicc -o write_cards write_file.c
mpirun -np 1 ./reading : -np 1 ./process : -np 1 ./write_cards
rm reading process write_cards
