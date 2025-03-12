/*
 * A tool read and set section value
 * Writed by zet (feqin1023 AT gmail dot com)
 *
 * 2018/02/01 - Updated by Abel Romero Pérez aka D1W0U <abel@abelromero.co>
 * I've fixed the check_vermagic() and set_vermagic() functions.
 * unload_module() dumps the memory into the module (saves the modification of vermagic).
 * So we are able to see the module info section fine, and to modify the vermagic.
 * Also cleaned the source code.
 *
 * I've tested it to work on Ubuntu Linux Kernel, 4.13.0-32-generic => 4.13.0-31-generic
 *
 * Work done for the ARP-RootKit.
*/

#include <ctype.h>
#include <assert.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define  __KERNEL_VERSION(x,y,z) (((x)<<16)+((y)<<8)+((z)))
#define ___DEBUG printf
#define FREE(x) do{ if((x)) free((x));}while(0)
/// ELF object
#define EI_CLASS 4
#define ELF_32 1
#define ELF_64 2
// none = 0, Elf32 = 1, Elf64 = 2


/// This data structure defined in linux kernel, include/kernel/module.h
#define MODULE_NAME_LEN	 (64 - sizeof(unsigned long))
typedef struct modversion_info {
	unsigned long crc;
	char name[MODULE_NAME_LEN];
} version_t;

#define VMAGIC_LEN 8 // Length of "vermagic" variable.
typedef struct module_bin_info{
    int class_flag;

    /// All of these elf structure pointer point to mapped virtual address.
    Elf32_Ehdr *eh_32;
    Elf64_Ehdr *eh_64;
    // TODO useless
    Elf32_Phdr *phdr_32;
    Elf64_Phdr *phdr_64;
    Elf32_Shdr *sha_32;
    Elf64_Shdr *sha_64;
    /// Module name
    char *name;
    /// Virtual address of mapped module
    char *map;
    /// Virtual address of sction header string table
    char *vaddr_shst;
    // file descriptor of the module
    int file;
    // file state buffer
    struct stat sb;
}module_bin;
// program name
char *bin = NULL;

int unload_module (module_bin* mb);
int get_os_sym_key_crc(const char* kernel_key_path,const char* key,char* crc);

void usage (FILE *stream) {
  fprintf(stream,
  "Read and set vermagic and crc of module\n"
  "Usage: %s <options> <module>\n"
  "Options are:\n"
  "\t-d, dump .modinfo section.\n"
  "\t-v new-value, set vermagic.\n"
  "\t-D, dump CRCs.\n"
  "\t-c {\"+'{'name, no-zero-value'}'\"}, set CRC.\n",
  bin
  );

  exit(stream == stdout ? EXIT_SUCCESS : EXIT_FAILURE);
}

/// Initialize the global elf variables
void set_elf_data (module_bin* mb)
{
  Elf32_Shdr *shst_32;
  Elf64_Shdr *shst_64;

  if (mb->class_flag == ELF_64) {

#define SET_ELF_DATA_ARCH(A)                                            \
    mb->eh_##A = (Elf##A##_Ehdr *)mb->map;                                      \
    /* program header mostly is empty in shared module*/                \
    if (mb->eh_##A->e_phoff)                                                \
      mb->phdr_##A = (Elf##A##_Phdr *)((char *)mb->eh_##A + mb->eh_##A->e_phoff);   \
    mb->sha_##A = (Elf##A##_Shdr *)((char *)mb->eh_##A + mb->eh_##A->e_shoff);      \
    shst_##A = &mb->sha_##A[mb->eh_##A->e_shstrndx];                            \
    /* this is a common variable for elf32 and elf64*/                  \
    mb->vaddr_shst = mb->map + shst_##A->sh_offset;                             \

    SET_ELF_DATA_ARCH(64)
  } else {
    SET_ELF_DATA_ARCH(32)
  }

  return;
}

int load_module (module_bin* mb) {
  // file descriptor of the module
  int file;

  assert(mb->name);
  file = open(mb->name, O_RDWR);
  
  if (file == -1) {
    perror("open---");
    return EXIT_FAILURE;
  }
  mb->file = file;
  if (fstat(file, &mb->sb) == -1) {
    perror("fstat");
    return EXIT_FAILURE;
  }

  // TODO: maybe need a more carefull protection value.
  // for now READ and write.
  mb->map = (char *)mmap(NULL, mb->sb.st_size, PROT_READ|PROT_WRITE,
                             MAP_SHARED, file, 0);
  if(mb->map == MAP_FAILED) {
    perror("mmap");
    return EXIT_FAILURE;
  }

  // check elf object version, EI_CLASS == 4
  mb->class_flag = (int) *(mb->map + EI_CLASS);
  if (mb->class_flag != ELF_32 && mb->class_flag != ELF_64) {
    fprintf(stderr, "error: Module :%s format error\n", mb->name);
    return EXIT_FAILURE;
  }

  // if i386 operate elf64
#ifdef __i386__
  if (mb->class_flag == ELF_64)
    fprintf(stderr, "error: You are operating ELF64 object in 32 bits machine.\
       \nMostly you will receive Segmentation Fault.                          \
       \nIf you really need do this.                                          \
       \nContact me: feqin1023 AT gmail dot com                               \
       \n");
#endif

  set_elf_data(mb);

  return EXIT_SUCCESS;
}

/// if find return the section index
//  not return 0
unsigned int find_section (module_bin* mb,char *name) {
  unsigned int i = 0, sec_num = 0;

  if (mb->class_flag == ELF_64) {
//
#define FIND_SECTION_ARCH(A)                                        \
    sec_num = (unsigned int)mb->eh_##A->e_shnum;                        \
    assert(sec_num && "elf section number is 0");                   \
                                                                    \
    for (; i < sec_num; i++)                                        \
      if (! strcmp(mb->vaddr_shst + mb->sha_##A[i].sh_name, name)) {        \
        printf("Section name:\t\t\t\t%s\n", name);                  \
        return i;                                                   \
      }                                                             \
                                                                    \
    /* if has not find sectuion*/                                   \
    if (i == (unsigned int)mb->eh_##A->e_shnum)                         \
      fprintf(stderr, "Not any section named: %s\n", name);         \
 
    // elf64
    FIND_SECTION_ARCH(64)
  } else {
    // elf32
    FIND_SECTION_ARCH(32)
  }

  return 0;
}

void formalize(char *p, char **name, unsigned long *value) {
  char *comma, *last, ch;

  // {+'{'(name)?, no-zero-value'}'}?
  if (*p != '{')
    usage(stderr);
  // skip '{' and space/tab
  while (isspace(*++p))
    ;
  // only one comma
  if (!(comma = strchr(p, ',')) || !(last = strrchr(p, ',')) || comma != last)
    usage(stderr);
  //
  if (isalpha(ch = *p) || ch == '_' || ch == ',') {
    if (ch != ',') {
      *name = p;
      p = comma;
      // skip space and tab before comma
      while (isspace(*--p))
        ;
      // set name null-terminate
      ++p;
      *p = 0;
    }
    *value = strtoul(++comma, NULL, 0);
  }else
    usage(stderr);

  if (*value == 0)
    usage(stderr);
}

int set_crc (module_bin* mb,char *crc) {
  version_t *vv;
  unsigned int vn, i = 0;
  size_t vs;
  char *cn;
  unsigned long cv;
  int flag = 0;

  if (! (i = find_section(mb,"__versions")))
    return EXIT_FAILURE;
  if (mb->class_flag == ELF_64) {

#define SET_CRC_ARCH(A)                                                       \
      vv = (version_t *)((char *)mb->eh_##A + mb->sha_##A[i].sh_offset);              \
      vs = (size_t)mb->sha_##A[i].sh_size;                                        \

    // elf64
    SET_CRC_ARCH(64)
  } else {
    // elf32
    SET_CRC_ARCH(32)
  }
  // number of modversion entry
  vn = vs / sizeof(version_t);
  
  formalize(crc, &cn, &cv);
  if (strlen(cn) + 1 > MODULE_NAME_LEN) {
    fprintf(stderr, "Size of new crc name can not beyond %ld\n",
            MODULE_NAME_LEN);
    return EXIT_FAILURE;
  }
  // 
  for (i = 0; i < vn; i++) {
    if (! strcmp(vv[i].name, cn)) {
      flag = 1;
      printf("{-}Old value => %s:\t\t 0X%lX\n", vv[i].name, vv[i].crc);
      //memcpy(vv[i].name, cn, strlen(cn));
      //vv[i].name[strlen(cn)] = 0;
      vv[i].crc = cv;
      printf("{+}New value => %s:\t\t 0X%lX\n", vv[i].name, vv[i].crc);
      break;
    }
  }

  if (flag == 0)
    fprintf(stderr, "Can not find any crc-name : %s", cn);

  return EXIT_SUCCESS;
}

void dump_modinfo (module_bin* mb) {
  unsigned int i = 0;
  // section size
  size_t size = 0;
  // original section size
  char *p = NULL;

  if (! (i = find_section(mb,".modinfo")))
    return;

  if (mb->class_flag == ELF_64) {
    p = mb->map + mb->sha_64[i].sh_offset;
    size = (size_t)mb->sha_64[i].sh_size;
  } else {
    p = mb->map + mb->sha_32[i].sh_offset;
    size = (size_t)mb->sha_32[i].sh_size;
  }

  // there is no difference between elf32 and elf64 at this point
  for (i = 0; size > i;) {
    printf("[%03d] %s\n", i, &p[i]);
	i += strlen(&p[i]);
	while (!p[i]) i++; // skip 0's
  }
 
  return;
}

int set_vermagic(module_bin* mb,char *ver) {
  char *p;
  unsigned int i;
  unsigned long new_len = strlen(ver);
  size_t size;

  // no seection named .modinfo
  if (! (i = find_section(mb,".modinfo")))
    return EXIT_FAILURE;

  if (mb->class_flag == ELF_64) {
    p = mb->map + mb->sha_64[i].sh_offset;
    size = (size_t)mb->sha_64[i].sh_size;
  } else {
    p = mb->map + mb->sha_32[i].sh_offset;
    size = (size_t)mb->sha_32[i].sh_size;
  }

  for (i = 0; size > i;) {
    if (! strncmp(&p[i], "vermagic", VMAGIC_LEN) && p[i + VMAGIC_LEN] == '=') {
      printf("{-}Old value => %s\n", &p[i]);
      if (new_len > strlen(&p[i + VMAGIC_LEN + 1])) {
        fprintf(stderr, "Length of the new specified vermagic overflow\n");
		return EXIT_FAILURE;
      }
      memcpy(&p[i + VMAGIC_LEN + 1], ver, new_len);
      memset(&p[i + VMAGIC_LEN + 1 + new_len], 0, strlen(&p[i]) - VMAGIC_LEN - 1 - new_len);

      printf("{+}New value => %s\n", &p[i]);
    }
    i += strlen(&p[i]);
    while (!p[i]) i++; // skip 0's
  }

  return EXIT_SUCCESS;
}
/*****************************************/
int set_check_version_key_crc (const char* kernel_key_path,module_bin* mb) {
  version_t *vv;
  unsigned int vn, i = 0;
  size_t vs;
//  char *cn;
  char crc[16] = {0};
  unsigned long cv;
//  int flag = 0;

  if (! (i = find_section(mb,"__versions")))
    return EXIT_FAILURE;
  if (mb->class_flag == ELF_64) {

#define SET_CRC_ARCH(A)                                                       \
      vv = (version_t *)((char *)mb->eh_##A + mb->sha_##A[i].sh_offset);              \
      vs = (size_t)mb->sha_##A[i].sh_size;                                        \

    // elf64
    SET_CRC_ARCH(64)
  } else {
    // elf32
    SET_CRC_ARCH(32)
  }
  // number of modversion entry
  vn = vs / sizeof(version_t);
#if 0
  //formalize(crc, &cn, &cv);
  if (strlen(cn) + 1 > MODULE_NAME_LEN) {
    fprintf(stderr, "Size of new crc name can not beyond %ld\n",
            MODULE_NAME_LEN);
    return EXIT_FAILURE;
  }
#endif
  //
  for (i = 0; i < vn; i++) {


      ___DEBUG("{-}Old value => %s:\t\t 0X%lX\n", vv[i].name, vv[i].crc);
      memset(crc,0,sizeof(crc));
      if(0 ==get_os_sym_key_crc(kernel_key_path,vv[i].name,crc))
      {
          cv = strtoul(crc,NULL,16);
          if(cv != 0)
          {
      vv[i].crc = cv;
            ___DEBUG("{+}New value => %s:\t\t 0X%lX crc <%s>\n", vv[i].name, vv[i].crc,crc);
          }
          else
          {
            fprintf(stderr,"Cant not fine any crc-name %s\n",vv[i].name);
    }
  }
      else
      {
        fprintf(stderr,"Cant not fine any crc-name %s\n",vv[i].name);
      }
  }

  return EXIT_SUCCESS;
}

int __get_kernel_version(char* ver_str,int* kernel_num)
{
    FILE* fp = NULL;
    char buffer[1024] = {0};
    char* p;
    //char* q;
    char* verStr = NULL;
    char* key = "Linux version ";
  //  int ret;
//    int version_num = 0;
    int a,b,c;
    char d[1024] = {0};
    fp = fopen("/proc/version","r");
    if(fp == NULL)
    {
        perror("open /proc/version");
        exit(1);
    }
    if(NULL == fgets(buffer,1024,fp))
    {
        perror("read /proc/version");
        fclose(fp);
        exit(1);
    }
    /*Linux version xxx-vorter-X () */
    p = strstr(buffer,key);
    if(!p)
    {
        //
       fprintf(stderr, "error: not find <%s> from <%s>\n",key,buffer);
       fclose(fp);
       return -1;
    }
    p+=strlen(key);
    verStr = p;
    p = strchr(verStr,' ');
    if(p)
        *p = 0;
    else
    {
        fprintf(stderr, "error: not find Version's space!\n");
        fclose(fp);
        return -1;
    }
    sscanf(verStr,"%d.%d.%d%s",&a,&b,&c,d);
    ___DEBUG("a %d b %d c %d d %s \n",a,b,c,d);
    fclose(fp);
    strcpy(ver_str,verStr);
    *kernel_num = ((a<<16) + (b<<8) +c);
    return 0;
}
int __get_vermagic_from_modinfo (module_bin* mb,char** ret)
{
  unsigned int i = 0;
  // section size
  size_t size = 0;
  // original section size
  char *p = NULL;

  if (! (i = find_section(mb,".modinfo")))
    return -1;

  if (mb->class_flag == ELF_64) {
    p = mb->map + mb->sha_64[i].sh_offset;
    size = (size_t)mb->sha_64[i].sh_size;
  } else {
    p = mb->map + mb->sha_32[i].sh_offset;
    size = (size_t)mb->sha_32[i].sh_size;
  }

  // there is no difference between elf32 and elf64 at this point
  for (i = 0; size > i;) {
    //printf("[%03d] %s\n", i, &p[i]);
     if (! strncmp(&p[i], "vermagic", VMAGIC_LEN) && p[i + VMAGIC_LEN] == '=')
     {
        *ret = (char*)malloc(strlen(&p[i])+1);
        if(*ret == NULL)
            return -1;
        else
        {
            strcpy(*ret,&p[i]);
            return 0;
        }
     }
	i += strlen(&p[i]);
	while (!p[i]) i++; // skip 0's
  }

  return -1;
}

int read_vermagic_str_from_ko(char* ko_name,char** vermagic)
{
    module_bin mb;
    int ret;
    memset(&mb,0,sizeof(mb));
    mb.name = ko_name;
    if (load_module(&mb)) {
        return -1;
    }
    ret = __get_vermagic_from_modinfo(&mb,vermagic);
    unload_module(&mb);
    return ret;

}

int __get_one_ko_path_from_dep(const char* kernel_key_path, char ** ko_path)
{
    /* get current os vermagic */
    FILE* fp = NULL;
    char buffer[1024] = {0};
    char modules_dep_path[256] = {0};
    char tmp_ko_path[1024] = {0};
    char* p;
    sprintf(modules_dep_path,"/lib/modules/%s/modules.dep",kernel_key_path);
    fp = fopen(modules_dep_path,"r");
    if(fp == NULL)
    {
       fprintf(stderr,"open %s %s\n",modules_dep_path,strerror(errno));
       return -1;
    }
    if(NULL == fgets(buffer,1024,fp))
    {
       fprintf(stderr,"read %s %s\n",modules_dep_path,strerror(errno));
       fclose(fp);
       return -1;
    }
    p = strchr(buffer,':');
    if(p)
    {
        *p = 0;
    }
    else
    {
        fclose(fp);
        return -1;
    }
    if(buffer[0] != '/')
    {
        sprintf(tmp_ko_path,"/lib/modules/%s/%s",kernel_key_path,buffer);
    }
    else
    {
        sprintf(tmp_ko_path,"%s",buffer);
    }
    if(*(p-2) == 'x' && *(p-1) == 'z' )
    {
        char cmd[256] = {0};
        sprintf(cmd,"unxz %s -c >>/tmp/1qaz.ko",tmp_ko_path);
        system(cmd);
        sprintf(tmp_ko_path,"%s","/tmp/1qaz.ko\0");

    }
    *ko_path = malloc(sizeof(tmp_ko_path)+1);
    if(*ko_path == NULL)
    {
        fclose(fp);
        return -1;
    }
    strcpy(*ko_path,tmp_ko_path);
    fclose(fp);
    return 0;

//    return -1;
}
int get_os_vermagic(const char* kernel_key_path, char** os_vermagic)
{
    char* ko_path = NULL;
    int ret = 0;
    char* vermagic_str = NULL;
    char* p;
    char* key = "vermagic=";
    if(__get_one_ko_path_from_dep(kernel_key_path,&ko_path) != 0)
    {
        return -1;
    }
    if(ko_path != NULL)
    {
        ___DEBUG(" %s:%d ko_path <%s>\n",__func__,__LINE__,ko_path);
        ret = read_vermagic_str_from_ko(ko_path,&vermagic_str);
        if(ret == 0)
        {
            ___DEBUG(" %s:%d os_vermagic <%s>\n",__func__,__LINE__,vermagic_str);
            p = strstr(vermagic_str,key);
            if(!p)
            {
                ret = 1;
                goto end;
            }
            else
            {
                p += strlen(key);
                *os_vermagic = malloc(strlen(p)+1);
                if(*os_vermagic == NULL)
                {
                    ret =1;
                    goto end;
                }
                strcpy(*os_vermagic,p);
                ret = 0;
            }
        }
    }
end:
    FREE(ko_path);
    FREE(vermagic_str);
    return ret;

}
/* /lib/modules/$(uname -r)/build/Module.symvers
/boot/sysver-$(uname -r).gz
*/
int get_os_sym_key_crc_from_symvers(const char* key,char* crc,const char* file_path)
{
    FILE* fp = NULL;
    char buffer[1024] = {0};
    int ret = -1;
    char new_key[128] = {0};
    char* p;
    sprintf(new_key,"\t%s\t",key);
    fp = fopen(file_path,"r");
    if(fp == NULL)
    {
       fprintf(stderr,"open %s %s\n",file_path,strerror(errno));
       return -1;
    }

    while(NULL != fgets(buffer,1024,fp))
    {
        p = strstr(buffer,new_key);
        if(p == NULL)
        {
            continue;
        }
        *p = 0;
        strncpy(crc,buffer,10);
        ret = 0;
        goto end;
    }
end:
    fclose(fp);
    return ret;
}

int get_os_sym_key_crc(const char* kernel_key_path,const char* key,char* crc)
{
    char file_path[256] = {0};
    sprintf(file_path, "/boot/sysver-%s.gz",kernel_key_path);
    if(0 == access(file_path,0))
    {
        return get_os_sym_key_crc_from_symvers(key,crc,file_path);
    }

    memset(file_path,0,sizeof(file_path));
    sprintf(file_path, "/lib/modules/%s/build/Module.symvers",kernel_key_path);
    if(0 == access(file_path,0))
    {
        return get_os_sym_key_crc_from_symvers(key,crc,file_path);
    }
    return -1;
}
int __set_vermagic(char* name,char* os_vermagic)
{

    module_bin mb;
    int ret;
    memset(&mb,0,sizeof(mb));
    mb.name = name;
    if (load_module(&mb)) {
        return -1;
    }
    ret = set_vermagic(&mb, os_vermagic);

    unload_module(&mb);
    return ret;
}
int __update_crc_to_ko_file(const char* kernel_key_path,char* name)
    {

    module_bin mb;
    int ret;
    memset(&mb,0,sizeof(mb));
    mb.name = name;
    if (load_module(&mb)) {
        return -1;
    }
    ret = set_check_version_key_crc(kernel_key_path, &mb);
    unload_module(&mb);
    return ret;


}
int set_vermagic_and_crc(char* name)
{
    char* __os_vermagic = NULL;
//    char* __check_versions_key_crc = NULL;
    int kernel_version_num = 0;
    char kernel_key_path[128]= {0};
    int ret;
//    unsigned long ul_crc = 0;
//    char * key;
/*
    char* x = "module_layout";//2.6.30 and high

    char* x1 = "struct_module"; //2.6.29 and low
*/
//    char crc[256] ={0};
    /*get this os's vermagic and __versions*/
    if(0 !=__get_kernel_version(kernel_key_path,&kernel_version_num))
    {
        return -1;
    }
    ___DEBUG("kernel_all_path <%s> \n",kernel_key_path);
    ret = get_os_vermagic(kernel_key_path,&__os_vermagic);
    if(ret == 0)
    {
        ___DEBUG("__os_vermagic <%s> \n",__os_vermagic);
    }
    __set_vermagic(name,__os_vermagic);

    /* set to the ko. */
    ret =  __update_crc_to_ko_file(kernel_key_path,name);
    if(ret)
    {
        fprintf(stderr,"fail: set vermaagic and crc \n");
    }
    return 0;
}
/*****************************************/

int unload_module (module_bin* mb) {
  if (msync(mb->map, mb->sb.st_size, MS_SYNC) == -1) {
    perror("Could not sync the file to disk");
    return EXIT_FAILURE;
  }
  if (munmap(mb->map, mb->sb.st_size) == -1) {
    perror("munmap");
    return EXIT_FAILURE;
  }
  close(mb->file);
  return EXIT_SUCCESS;
}

void dump_crc (module_bin* mb) {
  // version info vector
  version_t *vv;
  unsigned int vn, i = 0;
  size_t vs;

  if (mb->class_flag == ELF_64) {
#define CHECK_CRC_ARCH(A)                                                   \
    if (! (i = find_section(mb,"__versions")))                                 \
      return;                                                               \
    vv = (version_t *)((char *)mb->eh_##A + mb->sha_##A[i].sh_offset);              \
    vs = (size_t)mb->sha_##A[i].sh_size;                                        \

    // elf64
    CHECK_CRC_ARCH(64)
  } else {
    // elf32
    CHECK_CRC_ARCH(32)
  }
  //
  vn = vs / sizeof(version_t);

  for (i = 0; i < vn; i++)
    printf("[%03d] %s\t\t\t: 0X%08lX \n", i + 1, vv[i].name, vv[i].crc);

  return;
}

int main (int argc, char **argv) {
  module_bin mb;

  bin = argv[0];
  mb.name = argv[argc - 1];

  if (!mb.name || argc < 3) {
    usage(stderr);
  }

  if (load_module(&mb)) {
	fprintf(stderr, "error: Load module : %s failed.\n", mb.name);
	return EXIT_FAILURE;
  }

  if (!strncmp(argv[1], "-d", 2) && argc == 3) {
    dump_modinfo(&mb);
  } else if (!strncmp(argv[1], "-v", 2) && argc == 4) {
    set_vermagic(&mb,argv[2]);
  } else if (!strncmp(argv[1], "-D", 2) && argc == 3) {
	dump_crc(&mb);
  } else if (!strncmp(argv[1], "-c", 2) && argc == 4) {
	set_crc(&mb,argv[2]);
  } else if (!strncmp(argv[1], "-x", 2) && argc == 3) {

	set_vermagic_and_crc(argv[2]);
  }  else {
	usage(stderr);
  }

  return unload_module(&mb);
}

