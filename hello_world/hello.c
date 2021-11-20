/*****************************************
* \file        driver.c
*
* \details     Simple hello world driver
*
* \author      José Wanderson
*
* ****************************************/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#define KERNEL_PARAM kernel_param_ops

int valueETX, arr_valueETX[4];
char *nameETX;
int cb_valueETX = 0;

module_param(valueETX, int, S_IRUSR | S_IWUSR);                 // Integer value
module_param(nameETX, charp, S_IRUSR | S_IWUSR);                 // String
module_param_array(arr_valueETX, int, NULL, S_IRUSR | S_IWUSR); // Array of integers

/*----------------------Module_param_cb()-----------------------------------*/
int notify_param(const char *val, const struct kernel_param *kp){

    int res = param_set_int(val, kp); // Use helper for write variable
    if(res==0){
	pr_info("Call back function called..\n");
	pr_info("New value of cb_valueETX = %d\n", cb_valueETX);
	return 0;
    }
    return -1;
}

const struct KERNEL_PARAM my_param_ops = {

	.set = &notify_param,    // Use our setter ...
	.get = &param_get_int, // ... and standard getter
};

module_param_cb(cb_valueETX, &my_param_ops, &cb_valueETX, S_IRUGO | S_IWUSR);
/*--------------------------------------------------------------------------*/

/*
** Module init function
*/
static int __init hello_world_init(void){
    int i;
    pr_info("ValueETX = %d \n", valueETX);
    pr_info("cb_valueETX = %d \n", cb_valueETX);
    pr_info("NameETX = %s \n", nameETX);
    for(i = 0; i< (sizeof arr_valueETX / sizeof(int)); i++){
	pr_info("Arr_value[%d] = %d\n", i, arr_valueETX[i]);
    }

    pr_info("Welcome\n");
    pr_info("This is the Simple Module\n");
    pr_info("Kernel Module Inserted Successfully...\n");
    return 0;
}

/*
** Module Exit function
*/
static void __exit hello_world_exit(void){
    pr_info("Kernel Module Removed Successfully...\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("José Wanderson <wandersonjose75@gmail.com>");
MODULE_DESCRIPTION("A simple hello world driver");
MODULE_VERSION("0.0.1");
