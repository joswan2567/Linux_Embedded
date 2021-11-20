#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

dev_t dev = 0;

/*
** Module init function
*/

static int __init hello_init(void){

    if((alloc_chrdev_region(&dev, 0, 1, "Joswan_Dev")) < 0){
	pr_err("Cannot allocate major number for device \n");
	return -1;
    }

    pr_info("Kernel Module Inserted Sucessfully... \n");
    return 0;

}

/*
** Module exit function
*/

static void __exit hello_exit(void){

     unregister_chrdev_region(dev, 1);
     pr_info("Kernel Moduel Removed Successfuly...\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("José Wanderson <wandersonjose75@gmail.com>");
MODULE_DESCRIPTION("Simple linux driver (Manually Creating a Device File)");
MODULE_VERSION("0.1");

