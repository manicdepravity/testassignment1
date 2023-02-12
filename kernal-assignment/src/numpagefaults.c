#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/utsname.h>
#include <linux/mm.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANDREW HILL");
MODULE_DESCRIPTION("Assignment1: /proc/numpagefaults");
//struct array to store pgfaults
static int version_proc_show(struct seq_file *m, void *v)
{
        unsigned long envp[NR_VM_EVENT_ITEMS];
        u64 mypgfault;
        all_vm_events(envp);
        mypgfault = envp[PGFAULT];
        seq_printf(m, "%llu\n", (unsigned long long) mypgfault);

        return 0;
}
// called on sudo insmod and cat numpagefault
static int __init procv_init(void)
{
        proc_create_single("numpagefaults", 0, NULL, version_proc_show);
        printk(KERN_INFO "Loading in: /proc/numapagefaults");
        return 0;
}
// calleld on sudo rmmod and removes our /proc/
static void __exit procv_exit(void)
{
        remove_proc_entry("numpagefaults", NULL);
        printk(KERN_INFO "Removing Installed: /proc/numagefaults");
}

module_init(procv_init);
module_exit(procv_exit);
