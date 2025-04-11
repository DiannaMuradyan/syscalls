#define read 0                   //defined syscall numbers
#define write 1
#define open 2
#define close 3
#define mmap 9
#define exit 60
#define rdwr 2
#define one_MB  1048576
#define NULL (void*)0


int openSyscall(char* name,int flag,int mode) {      //syscall to open a file
	int ret;
	asm (
		"syscall"
		: "=a"(ret)
		: "a"(open), "D"(name), "S"(flag), "d"(mode)
		: "rcx", "r11", "memory"
	);
	return ret;
}


int readSyscall(int fd,char* buffer,int size) {        //reading from the file
	int ret;
	asm (
		"syscall"
		:"=a"(ret)
		:"a"(read), "D"(fd), "S"(buffer), "d"(size)
		:"rcx", "r11", "memory"
	);
	return ret;
}


int  writeSyscall(int fd,const void* buffer,int size) {         //writing in the buffer from the file
	int ret;
	asm (
		"syscall"
		: "=a"(ret)
		: "a"(write), "D"(fd), "S"(buffer), "d"(size)
		: "rcx", "r11", "memory"
	);
	return ret;
}


int closeSyscall(int fd) {          //syscall to close the file
	asm (
		"syscall"
		: 
		: "a"(close), "D"(fd)
		: "rcx", "r11", "memory"
	);
}

int exitSyscall() {                //syscall to exit the program
	asm (
		"syscall"
		:
		: "a"(exit)
		: "rcx", "r11", "memory"
   );
}

char* itoa(int num, char* str) {   //from int to string
	int count = 0;
	int tmp = num;
	while (num) {
		++count;
		num /= 10;
	}
	for (int i = 0; i < count; ++i) {
		str[count - i-1] = tmp%10 + 48;
		tmp /= 10;
	}
	str[count] = '\0';
	return str;
}


int strlength(char* str) {   //return the length of the string
	int count = 0;
	char* tmp = str;
	while (*tmp != '\0') {
		++count;
		++tmp;
	}
	return count;
}



void* brkSyscall(void* addr) {  //syscall to set the heap end
	 void* ret;
    asm (
        "syscall"              
        :"=a"(ret)      
        :"a"(12), "D" (addr)  
		  :"rcx", "r11", "memory"           
    );
	return ret;
}


void* sbrk(int size) {              //to set the heap end by giving desired size
	if (!size) {
		return brkSyscall(NULL);
	}
	void* old = brkSyscall(NULL);
	void* new = old + size;
	return brkSyscall(new);	
}


int _start()                       
{ 
	void* old = sbrk(0);     //getting the current heap end

	sbrk(one_MB);            //changing heap end by adding 1Mb
	
	int fd = openSyscall("file.txt",rdwr,0664);    //opening the file

	char* buff = (char*)old;                      //casting the reserved memory to char

	int n = readSyscall(fd,buff,1000);              //reading from file to the buffer and getting the count of readen symbols

	char num[20] = {};                            //reserving memory to store n as string
	itoa(n,num);                                  //getting n's representaion as a string

//	writeSyscall(1,buff,n); 
   
	writeSyscall(1,num,strlength(num));                //writing the num to stdout 
	writeSyscall(1," : bytes have been read\n",25);    

	closeSyscall(fd);          //closing the file
	exitSyscall();             //exit the program
}


