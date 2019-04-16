#include <linux/module.h>
#include <linux/init.h>
#include <linux/utsname.h>

static int __init my_init(void)
{
	/*
	 * 	char sysname[__NEW_UTS_LEN + 1];
	char nodename[__NEW_UTS_LEN + 1];
	char release[__NEW_UTS_LEN + 1];
	char version[__NEW_UTS_LEN + 1];
	char machine[__NEW_UTS_LEN + 1];
	char domainname[__NEW_UTS_LEN + 1];
	 */
	struct new_utsname* system = init_utsname();
	pr_info("Lab6.3: Hello");
	pr_info("sysname: %s nodename:%s \n"
			, system->sysname
			, system->nodename
	);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Bye");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Paulo");
MODULE_LICENSE("GPL v2");
