import random

#RANDOM NUCLEOTIDE GENERATOR

seq_len = int(input("Sequence Length: "))

with open("seq_gen.fasta", "w") as file:
    for i in range(seq_len):
        nucleotide = random.randint(1, 4)

        if nucleotide == 1:
            file.write('A')
        elif nucleotide == 2:
            file.write('G')
        elif nucleotide == 3:
            file.write('C')
        else:
            file.write('T')


