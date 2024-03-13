PROGRAM = shake128
SRCP    = main.c
OBJP    = main.o
SRCF    = utils.c shake128.c permutations.c sponge.c
OBJF    = utils.o shake128.o permutations.o sponge.o

CODE    = cd code
CC      = gcc
CFLAGS  = -Werror -Wall -Wextra -Wpedantic -pedantic-errors\
          -Wformat=2 -Wno-unused-parameter -Wshadow -Waggregate-return\
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs -O2 \
          -Wbad-function-cast -Wcast-align -Wcast-qual -Wfloat-equal \
          -Wdeclaration-after-statement -Wfloat-equal -Wpointer-arith \
          -Wmissing-declarations -Wmissing-prototypes -Wsequence-point \
          -Wstrict-prototypes -Wswitch -Wundef -Wunreachable-code\
          -Wunused-but-set-parameter -Wjump-misses-init -Wlogical-op

CFLAGS += $(shell gcc -v --help 2>/dev/null \
          | egrep  "std=c[^I]+ISO [^1]" \
          | egrep -o "\-[^ ]+" | tail -n 1)

.SILENT:
.PHONY:     default
default:    program	

.PHONY:			program
program: interfaces
	@$(CODE) && $(CC) $(CFLAGS) $(SRCP) -c 
	@$(CODE) && $(CC) $(CFLAGS) $(OBJP) $(OBJF) -o ../$(PROGRAM) -lgmp
	@echo "Built the "$(PROGRAM)" executable." 

.PHONY:     interfaces
interfaces: clean
	@$(CODE) && $(CC) $(CFLAGS) $(SRCF) -c
	@echo "Built all interfaces of the $(PROGRAM) program."

.PHONY:     clean
clean:  
	@$(RM) $(PROGRAM) code/*.o
	@echo "Done cleaning up."


