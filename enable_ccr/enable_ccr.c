#include <linux/module.h>
#include <linux/kernel.h>

void enable_ccr(void *info)
{
   asm volatile("MSR PMUSERENR_EL0, %0" ::"r"(1));
   asm volatile("MSR PMCR_EL0, %0" ::"r"(1));
   asm volatile("MSR PMCNTENSET_EL0, %0" ::"r"(0x80000000));
}

int init_module(void)
{
   on_each_cpu(enable_ccr, NULL, 0);
   printk(KERN_INFO "Userspace access to CCR enabled\n");
   return 0;
}
