# Quote-Character-Device-Driver
A Linux kernel module that will return one quote of twenty to the user upon being read

![Sample quotes from the character device driver](https://iili.io/HxCcH4s.png)

## HOW TO RUN:
	0) Open 3 terminal tabs
	1) In first terminal shell type "sudo tail -f /var/log/kern.log"
	2) our major number is dynamically generated and will be outputed here
	3) In a new terminal move the repository's files to /usr/src/quotes
	4) type in the shell "make" to run the Makefile
	5) then type in the shell "sudo insmod inspiration.ko"
	6) In the first terminal we will see "Inspiration quote module has been loaded:
	   and the major number will be the last string on the line
	7) in a third terminal(tab or window) go to /dev ("cd /dev" in shell)
	8) in the third terminal shell type "sudo mknod inspiration c 247 0"
	9) now in the third terminal type "cat /dev/inspiration" to receieve your quote
	EXTRA: You can remove the module from the kernel by typing "sudo rm -f inspiration"
	in the /dev/ directory ( third terminal)
	and typing "sudo rmmod inspiration" in /usr/src/quotes (second terminal)
	You should see in the kernel logs (first terminal) "Inspirational quote module has been unloaded"

### Quote sources:
	https://www.goodreads.com/author/quotes/3137322.Fyodor_Dostoevsky
	https://bookhaven.stanford.edu/2020/05/dostoevskys-dream-of-a-worldwide-plague/
	https://www.goodreads.com/author/quotes/282885.Jordan_B_Peterson
	https://www.goodreads.com/author/quotes/20738929.Terry_Davis_Creator_of_Temple_OS
	https://nichequotes.com/douglas-murray-quotes
	https://www.goodreads.com/work/quotes/3204877-brave-new-world
	Brave New World Revisited - Aldous Huxley
	Make the Most of You - Patrick Lindsay 
	The Holy Bible
	The last 3 books are from my bedroom
