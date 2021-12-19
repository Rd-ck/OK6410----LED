ifneq ($(KERNELRELEASE),)

obj-m := driver_led.o
else
KDIR := /root/forlinx/linux-3.0.1
all:
        
        make -C $(KDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-linux-
clean:
        rm -f *.ko *.o *.mod.o *.mod.c *.symver
endif
~      
