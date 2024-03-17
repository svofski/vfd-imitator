#!/usr/bin/env python3


# recipe for gimp: 
#   scale down to width 357 (21*17)
#   bright/contrast, contrast down to -13

pgmfile = open('eggog-traced.pgm', 'r').read().split('\n') #replace('\n', ',')
pgmdata = ','.join(pgmfile[4:-1])

text = f'#include <stdint.h>\nconst uint8_t eggog_traced_pgm[] = {{{pgmdata}}};'

print(text)


