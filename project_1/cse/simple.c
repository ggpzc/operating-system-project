/**
 * simple.c
 *
 * A simple kernel module. 
 * 
 * To compile, run makefile by entering "make"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include<linux/hash.h>
#include<linux/gcd.h>
#include<asm/param.h>
#include<linux/jiffies.h>

/* This function is called when the module is loaded. */
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");
       printk(KERN_INFO "\nexercise1\n");
       printk(KERN_INFO "The GOLDEN_RATIO_PRIME is: %lu\n",GOLDEN_RATIO_PRIME);
       printk(KERN_INFO "The greatest common divisor of 3300 and 24 is: %lu\n", gcd(3300,24));
       printk(KERN_INFO "\nexercise2\n");
       printk(KERN_INFO "HZ is: %d\n",HZ);
       printk(KERN_INFO "jiffies is: %lu\n",jiffies);
       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "jiffies is: %lu\n",jiffies);
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );

module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SGG");

