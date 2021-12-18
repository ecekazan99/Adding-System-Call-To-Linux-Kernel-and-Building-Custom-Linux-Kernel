#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <asm/siginfo.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ECE KAZAN");

void cstringcpy(char *, char * );
void concatenate_string(char *, char *, char *);

#define PARAM_LEN 400


void cstringcpy(char *src, char * dest)
{
    while (*src) {
        *(dest++) = *(src++);
    }
    *dest = '\0';
}
void concatenate_string(char *original, char *add, char *result)
{
    while(*original)
    {
       *result = *original;
       original++;
       result++;
    }
    while(*add)
    {
       *result = *add;
       add++;
       result++;
    }
    *result = '\0';
}

SYSCALL_DEFINE2(my_syscall_0,char __user *, usr_param_src ,char __user *, usr_write_back_dst){

	int return_val = 0;
	char param_0[PARAM_LEN] = {'\0'};
	char param_1[PARAM_LEN] = {'\0'};

	if(copy_from_user(param_0, usr_param_src, PARAM_LEN) == 0){
        	printk(KERN_INFO "\"%s\" has been copied from usr_param_src!", param_0);
    	}

	cstringcpy(param_0, param_1);

	return_val = copy_to_user(usr_write_back_dst, param_1, PARAM_LEN);
	if(return_val == 0){
		printk(KERN_INFO "%s\nhas been copied to usr_write_back_dst!", param_1);
	}

	return return_val;
}

SYSCALL_DEFINE2(my_syscall_1,char __user *, usr_param_src_1 ,char __user *, usr_write_back_dst_1){
	char param_1[PARAM_LEN] = {'\0'};
	char param_0[PARAM_LEN] = {'\0'};
	int return_val = 0;
	 char res[100];
	 char res2[100];
	char y1[]="/proc/";
	char y2[]="/status";
	int buf_size=16;
	int j;
    	int z;
    	char buf2[buf_size];
    	struct file *f=NULL;

	char buf[PARAM_LEN];
 	char bufson[PARAM_LEN];
	mm_segment_t fs;
	int i;int i2;int count;int ab;
	i2=0;
	

	if(copy_from_user(param_0, usr_param_src_1, PARAM_LEN) == 0){
        	printk(KERN_INFO "\"%s\" has been copied from usr_param_src!", param_0);
    	}


    	for(i=0;i<PARAM_LEN;i++)
		bufson[i] = 0;
    	
	for(j=1;j<4;j++){	
    
		snprintf(buf2, buf_size, "%d", j);
		concatenate_string(y1, buf2, res);
		concatenate_string(res, y2, res2);

		for(i=0;i<PARAM_LEN;i++)
			buf[i] = 0;

		    f = filp_open(res2, O_RDONLY, 0);

		    if(!IS_ERR(f)){
                
			fs = get_fs();
			set_fs(get_ds());
			f->f_op->read(f, buf, 128, &f->f_pos);
			set_fs(fs);

			z=0;

			while(z<128){
				count=0;
				if(z+3<128 && buf[z]=='N' && buf[z+1]=='a' && buf[z+2]=='m' && buf[z+3]=='e'){
					while(buf[z]!='\n'){
						bufson[i2]=buf[z];
						z=z+1;
						i2=i2+1;
					}
					bufson[i2]='\n';
					i2=i2+1;
				}
				else if(z+3<128 && buf[z]=='P'&& buf[z+1]=='P' &&buf[z+2]=='i' &&buf[z+3]=='d'){
					while(buf[z]!='\n'){
						bufson[i2]=buf[z];
						z=z+1;
						i2=i2+1;
					}
					bufson[i2]='\n';i2=i2+1;
				}
				else if(z+4<128 && z-1>0 && buf[z-1]!='r' && buf[z-1]!='P'&& buf[z]=='P' && buf[z+1]=='i'&& buf[z+2]=='d'){
					while(buf[z]!='\n'){
						bufson[i2]=buf[z];
						z=z+1;
						i2=i2+1;
					}
					bufson[i2]='\n';
					i2=i2+1;
				}
				else if(z+3<128 && buf[z]=='U'&&buf[z+1]=='i'&&buf[z+2]=='d'){
					while(buf[z]!='\t' || count!=2){
						bufson[i2]=buf[z];
						z=z+1;
						i2=i2+1;
						if(buf[z]=='\t'){
							count=count+1;
						}
					}
					bufson[i2]='\n';
					i2=i2+1;
				}
				else if(z+5<128 && buf[z]=='S'&&buf[z+1]=='t'&& buf[z+2]=='a'&& buf[z+3]=='t'&& buf[z+4]=='e'){
					while(buf[z]!='\n'){
						bufson[i2]=buf[z];
						z=z+1;
						i2=i2+1;
					}
					bufson[i2]='\n';
					i2=i2+1;
				}	
				z=z+1;	
			}
		    	for(ab=0;ab<20;ab++){
		     	   bufson[i2]='=';
				i2++;
		   	 }
		    	bufson[i2]='\n';
			i2=i2+1;
			filp_close(f,NULL);
		}
		   
	}
  	cstringcpy(bufson,param_1);

	return_val = copy_to_user(usr_write_back_dst_1, param_1, PARAM_LEN);
	if(return_val == 0){
		printk("%s\n",bufson);
		printk(KERN_INFO "all processes some information!!!\n");
	}
	printk("%s\n",param_1);

	return return_val;
}

SYSCALL_DEFINE2(my_syscall_2, char __user *, usr_param_src_2,char __user *, usr_write_back_dst_2){
 	char res[100];
 	char res2[100];
	char y1[]="/proc/";
	char y2[]="/cmdline";
	int buf_size=16;  
 	int return_val = 0;
  	 char param_1[PARAM_LEN]={'\0'};

        struct file *f=NULL;
        char buf[PARAM_LEN];
	char buf2[buf_size];
        mm_segment_t fs;
        int i;int j;

	char param_0[PARAM_LEN] = {'\0'};

	if(copy_from_user(param_0, usr_param_src_2, PARAM_LEN) == 0){
        	printk(KERN_INFO "\"%s\" has been copied from usr_param_src!", param_0);
    	}
	 j=1;

	snprintf(buf2, PARAM_LEN, "%d", j);
	concatenate_string(y1, buf2, res);
	concatenate_string(res, y2, res2);
   	printk(KERN_INFO "%s\n",res2);

	    for(i=0;i<PARAM_LEN;i++)
		buf[i] = 0;

	    f = filp_open(res2, O_RDONLY, 0);
	    if(IS_ERR(f))
		printk("filp_open error!!.\n");
	    else{
		fs = get_fs();

		set_fs(get_ds());

		f->f_op->read(f, buf, 128, &f->f_pos);
		set_fs(fs);

		cstringcpy(buf,param_1);
		return_val = copy_to_user(usr_write_back_dst_2, param_1, PARAM_LEN);
		if(return_val == 0){
			printk("process and its cmdline\n");
			printk(KERN_INFO "%s\n",param_1);
		}
	   	filp_close(f,NULL);
	}
	printk(KERN_INFO "%d ->%s\n",j,param_1);
	return return_val;
}
SYSCALL_DEFINE2(my_syscall_3,char __user *, usr_param_src_3 ,char __user *, usr_write_back_dst_3){

	int return_val = 0;
	char param_0[PARAM_LEN] = {'\0'};
	char param_1[PARAM_LEN] = {'\0'};

	if(copy_from_user(param_0, usr_param_src_3, PARAM_LEN) == 0){
        	printk(KERN_INFO "\"%s\" has been copied from usr_param_src!", param_0);
    	}

	cstringcpy(param_0, param_1);

	return_val = copy_to_user(usr_write_back_dst_3, param_1, PARAM_LEN);
	if(return_val == 0){
		printk(KERN_INFO "%s\nhas been copied to usr_write_back_dst!", param_1);
	}

	return return_val;
}