#include <linux/module.h>
#include <linux/init.h>
#include <linux/percpu.h>

DEFINE_PER_CPU(int, cpuvar);

static int __init my_init(void)
{
	pr_info("[%s] :: my_init \n", KBUILD_MODNAME);
	pr_info("[%s] :: cpu: %d, this_cpu_read :%d \n", KBUILD_MODNAME, get_cpu(), this_cpu_read(cpuvar));
	this_cpu_write(cpuvar, 10);
	pr_info("[%s] :: cpu: %d, this_cpu_read :%d \n", KBUILD_MODNAME, get_cpu(), this_cpu_read(cpuvar));
	return 0;
}

static void __exit my_exit(void){
	pr_info("[%s] :: my_exit \n", KBUILD_MODNAME);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Paulo Almeida");
MODULE_LICENSE("GPL v2");
