include ../Examples.mk
include ../../lpc11xx.mk

$(echo  !!!)

PHONY += all clean

all: liblpc11xx.a uart_echo_noirq.bin uart_echo_irq.bin

uart_noirq.elf: liblpc11xx.a
uart_irq.elf: liblpc11xx.a

liblpc11xx.a: 
	$(MAKE) -C $(LPC11XXLIB_DIR)/src $@ O="$(PWD)"

clean:
	rm -f *.{o,a,elf,hex,srec,bin,prg,map}
