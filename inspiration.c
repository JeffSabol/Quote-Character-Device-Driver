#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h> // the character device
#include <linux/fs.h> // for character driver support
#include <linux/uaccess.h>

#define DEVICE_NAME  "inspiration"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jsabolumbc");
MODULE_DESCRIPTION("An inspritation quote character device module");

static char msg[80];
static char *msg_Ptr;
static int Device_Open = 0;

static const char *quotes[] = {
	"\"To love someone means to see them as God intended them.\" - Fyodor Dostoevsky\n",
	"\"He dreams of a worldwide plague that affects people's relationship with each other. No specific medical symptoms are mentioned. It is human interaction that breaks down, and the entire society gradually collapses.\" - Fyodor Dostoevsky\n",
	"\"When you have something to say, silence is a lie.\" - Dr. Jordan B. Peterson\n",
	"\"I don't think you have any insight whatsoever into your capacity for good until you have some well-developed insight into your capacity for evil.\" - Dr. Jordan B. Peterson\n",
	"\"If the world hates you, know that it has hated Me before it hated you.\" - John 15:18\n",
	"\"Do not think that I have come to bring peace to earth. I have not come to bring peace, but a sword.\" - Matthew 10:34\n",
	"\"An idiot admires complexity, a genius admires simplicity, a physicist tries to make it simple, for an idiot anything the more complicated it is the more he will admire it, if you make something so cluster*!#@ed he can't understand it he's gonna think you're a god cause you made it so complicated that nobody can understand it. That's how they write journals in Academics, they try to make it so complicated people think you're a genius. \" - Terry Davis, Creator of Temple OS\n",
	"\"To immerse oneself in popular culture for any length of time is to wallow in an almost unbearable shallowness.\" - Douglas Murray\n",
	"\"Words can be like X-rays if you use them properly - they'll go through anything. You read and you're pierced.\" - Aldous Huxley\n",
	"\"The daily soma ration was an insurance against personal maladjustment, social unrest and the spread of subversive ideas.\" - Aldous Huxley\n",
	"\"Permanent crisis is what we have to expect in a world in which over-population is producing a state of things, in which dictatorship under Communist auspices becomes almost inevitable.\" - Aldous Huxley\n",
	"\"I would rather trust a woman's instinct than a man's reason.\" - Stanley Baldwin\n",
	"\"The more corrupt the republic, the more numerous the laws.\" - Tacitus\n",
	"\"I saw the angel in the marble and carved until I set him free.\" - Michelangelo\n",
	"\"Every man's memory is his private literature.\" - Aldous Huxley\n",
	"\"Good judgment comes from experience, and a lot of that comes from bad judgment.\" - Will Rogers\n",
	"\"Let freedom never perish in your hands.\" - Joseph Addison\n",
	"\"When written in Chinese, the world \"crisis\" is composed of two characters-one represents danger and one represents opportunity. \" - John Fitzgerald Kennedy\n",
	"\"Don't kill the messenger.\" - Sophocles\n",
	"\"Words are, of course, the most powerful drug used by mankind.\" - Rudyard Kipling\n",
};


static int inspiration_open(struct inode *pinode, struct file *pfile){
	static int counter = 0;

	if(Device_Open) return -EBUSY;

	Device_Open++;
	sprintf(msg,quotes[counter],counter);
	counter++;
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);
	if(counter==19) counter=0;

	printk(KERN_ALERT "Inspirational device opened\n");
	return 0;
}


static ssize_t inspiration_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset){
	int bytes_read = 0;

	//if end of message, return 0(end of file)
	if (*msg_Ptr == 0)
		return 0;

	// put data into buffer
	while (length && *msg_Ptr) {

		/*
		 * The buffer is in the user data segment, not the kernel
		 * segment so "*" assignment won't work.  We have to use
		 * put_user which copies data from the kernel data segment to
		 * the user data segment.
		 */
		put_user(*(msg_Ptr++), buffer++);

		length--;
		bytes_read++;
	}

	// Most read functions return the number of bytes put into the buffer
	return bytes_read;
}

static ssize_t inspiration_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset){
	printk(KERN_ALERT "Inspirational quotes is read only!\n");
	return -EINVAL;
}

static int inspiration_release(struct inode *pinode, struct file *pfile){
	Device_Open--;
	module_put(THIS_MODULE);
	printk(KERN_ALERT "Inspirational device closed.\n");
	return 0;
}

static int major;

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = inspiration_open,
	.read = inspiration_read,
	.write = inspiration_write,
	.release = inspiration_release,
};




static int __init ModuleInit(void) {
	major = register_chrdev(0,DEVICE_NAME,&fops); // fops = file operations

	if(major<0) {
		printk(KERN_ALERT "Inspirational quote module failed!\n");
		return major;
	}


	printk(KERN_ALERT "Inspirational quote module has been loaded: %d\n",major);
	return 0;
}

static void __exit ModuleExit(void) {
	unregister_chrdev(major,DEVICE_NAME); //unregistering the file driver

	printk(KERN_ALERT "Inspirational quote module has been unloaded\n");

}

module_init(ModuleInit);
module_exit(ModuleExit);
