/*
 * Compilacao:
 *   gcc -o hello -nostdlib hello.c
 */

void end(void);
void write(char * text, int len);

void _start(void)
{
 char *msg = "Hello World!\n";
 int a;

 for(a=0; a<10;a++)
  write(msg,13);

 teste(100);

 end();
}

void write(char * text, int len)
{
 asm("movl $4,%%eax\n\t"
         "movl $1,%%ebx\n\t"
	 "movl %0,%%edx\n\t"
         "movl %1,%%ecx\n\t"
         "int $0x80"
         :
         : "r" (len), "r" (text)
         : "%eax", "%ebx", "%edx", "%ecx");
}

void end(void)
{
__asm__("movl $1,%eax\n\t"
        "movl $0,%ebx\n\t"
        "int $0x80");
}

int teste(int a) 
{
 if ( a == 0 ) return 0;

 write("Teste\n",6);
 return teste(a-1);   
}
