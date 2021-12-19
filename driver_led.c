	#include <linux/module.h>  
	#include <linux/kernel.h>  
	#include <linux/fs.h>  
	#include <asm/uaccess.h> /* copy_to_user,copy_from_user */  
	#include <linux/miscdevice.h>    
	#include <linux/pci.h>    
	#include <mach/map.h>    
	#include <mach/regs-gpio.h>    
	#include <mach/gpio-bank-m.h>    
	#include <plat/gpio-cfg.h>  
	 
	MODULE_LICENSE("GPL" );
	#define LED_MAJOR 240 
        #define LED0 0x1U
        #define LED1 0x2U
        #define LED2 0x4U
        #define LED3 0x8U
	  
	int led_open (struct inode *inode,struct file *filp)  
	  
	{  
	    unsigned tmp;     
	         tmp = readl(S3C64XX_GPMCON);     
	    //tmp = (tmp & ~(0x7U<<1))|(0x1U);  
	    tmp = (tmp & ~(0xffff) | (0x1111)); //set the GPIO output mode
   
	         writel(tmp, S3C64XX_GPMCON);   
	    printk("#########open######\n");  
	    return 0;  
	}  
	  
	ssize_t led_read (struct file *filp, char __user *buf, size_t count,loff_t *f_pos)  
	{  
	    printk("#########read######\n");  
	    return count;  
	}  
	void Led_on(unsigned LEDx)
        {
            unsigned  tmp;	  
            tmp = readl(S3C64XX_GPMDAT);
            tmp &=~ (LEDx);
            writel(tmp,S3C64XX_GPMDAT);
	}
        void Led_off(unsigned LEDx)
        {
            unsigned  tmp;	  
            tmp = readl(S3C64XX_GPMDAT);
            tmp |= (LEDx);
            writel(tmp,S3C64XX_GPMDAT);
        }
	ssize_t led_write (struct file *filp, const char __user *buf, size_t count,loff_t *f_pos)  
	{  
	    char wbuf[10];  
	    printk("#########write######\n");  
	    copy_from_user(wbuf,buf,count);  
	    switch(wbuf[0])
	    {
		    case 0:
			    Led_on(LED0);
			    break;

		    case 1:
			    Led_on(LED1);
                            break;
		    case 2:
			    Led_on(LED2);
                            break;
		    case 3:
			    Led_on(LED3);
                            break;
		    case 4:
			    Led_off(LED0);
                            break;
		    case 5:
			    Led_off(LED1);
                            break;
		    case 6:
			    Led_off(LED2);
                            break;
		    case 7:
			    Led_off(LED3);
                            break;


	    }   
	    printk(KERN_INFO "$$$$$$$$$$led_write$$$$$$$$$\n");
	    return count;  
	}  
	  
	int led_release (struct inode *inode, struct file *filp)  
	{  
	    printk("#########release######\n");  
	    return 0;  
	}  
	  
	struct file_operations led_fops ={  
	    .owner = THIS_MODULE,  
	    .open = led_open,  
	    .read = led_read,  
	    .write = led_write,  
	    .release = led_release,  
	};  
	  
	int __init led_init (void)  
	{   int rc;  
	    printk ("Test led dev\n");  
	    rc = register_chrdev(LED_MAJOR,"led",&led_fops);  
	    if (rc <0)  
	    {  
	        printk ("register %s char dev error\n","led");  
	        return -1;  
	    }  
	    printk ("ok!\n");  
	    return 0;  
	}  
	  
	void __exit led_exit (void)  
	{  
	    unregister_chrdev(LED_MAJOR,"led");  
	    printk ("module exit\n");  
	    return ;  
	}  
	  
	module_init(led_init);  
	module_exit(led_exit); 
