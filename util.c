#include <sys/stat.h>
#include <unistd.h> // access

#include "yu.h"
#include "util.h"

/*
 * C是个很小的语言，很多常用的函数都需要自己定义
 */

/* 用 newstr 替换 str 中的 oldstr ，str 长度一定要够长！
 * 即能容下 newstr 比 oldstr 多出的字节长度 
 */
extern void yu_str_replace (char *str, 
                            char *oldstr,
                            char *newstr)
{
  char *pstr=NULL;
  pstr = strstr(str, oldstr);
  if (pstr != NULL)
    {
      char swapstr[LINE_LENGTH_MAX]={'\0'};
      int str_length = strlen(oldstr);
      *pstr = '\0';
      strcpy (swapstr, pstr + str_length);
      strcat (str, newstr);
      strcat (str, swapstr);
    }
}


// 解压缩 bz2, gz 压缩包，暂用 system 调用
extern int yu_decompress_file (char *file)
{
  char cmd[LINE_LENGTH_MAX]={'\0'};
  /*
  char *cmd;
  printf ("strlen(file)=%d\n", strlen(file));
  cmd = (char *)malloc(strlen(file)+12);
  */
  if (0 != strstr (file, ".bz2"))
    strcpy (cmd, "/bin/bunzip2 ");
  if (0 != strstr (file, ".gz"))
    strcpy (cmd, "/bin/gunzip ");

  strcat (cmd, file);
  if (0 != strstr(cmd, "bin") && 0 != system (cmd))
    return 1;
  /*
  printf ("release malloc ...\n");
  free(cmd);
  */
  return 0;
}


extern char yu_decimal_to_hex_char (int dec)
{
  switch (dec)
    {
    case 10 :
      dec = 'a';
      return dec;
    case 11 :
      dec = 'b';
      return dec;
    case 12 :
      dec = 'c';
      return dec;
    case 13 :
      dec = 'd';
      return dec;
    case 14 :
      dec = 'e';
      return dec;
    case 15 :
      dec = 'f';
      return dec;
    default :
      dec = yu_itoa (dec);
      return dec;
    }
}


extern char yu_itoa (unsigned char i)
{
  switch (i)
    {
    case 0:
      return '0';
    case 1:
      return '1';
    case 2:
      return '2';
    case 3:
      return '3';
    case 4:
      return '4';
    case 5:
      return '5';
    case 6:
      return '6';
    case 7:
      return '7';
    case 8:
      return '8';
    case 9:
      return '9';
    }
  
  // Should never run here! Just disable gcc walling.
  return 'X';
}


// 确保指定的目录存在，不存在就创建。
extern int yu_make_sure_dir_exist (char *dir) {
  
  char *tmpdir;
  int i, len;
  tmpdir = malloc (strlen (dir) + 1);

  strcpy (tmpdir, dir);
  if (tmpdir[strlen (tmpdir) - 1] != '/')
    strcat (tmpdir, "/");

  len = strlen (tmpdir);
  for (i=1; i<len; i++) {
    if (tmpdir[i] == '/') {
      tmpdir[i] = '\0';
      if (access (tmpdir, R_OK) != 0) {
        if (mkdir (tmpdir, 0755) == -1) {
          perror (_("Couldn't create the directory"));
          return 1;
        }
      }
      tmpdir[i] = '/';
    }
  }

  free (tmpdir);
  return 0;
}


// 确保字符串以 '/' 结尾
extern char * yu_make_sure_last_slash_exist (char *str)
{
  int len = strlen(str);
  if (str[len - 1] == '\0')
    return str;
  char *tmpstr = malloc (len + 1);
  strcpy (tmpstr, str);
  strcat (tmpstr, "/");
  return tmpstr;
}

// 分配一段内存，连接两个字符串，返回新字符串
extern char * yu_concatenation_str (char *astr, char *bstr)
{
  char *tmpstr;
  tmpstr = (char *)malloc(strlen(astr)+strlen(bstr));
  strcpy (tmpstr, astr);
  strcat (tmpstr, bstr);
  return tmpstr;
}

extern int
yu_concatenation_str_together (char *str,
                               char *astr,
                               char *bstr)
{
  //  if (strlen(astr) + strlen(bstr) > strlen(str))
  //    return 1;
  strcpy (str, astr);
  strcat (str, bstr);
  return 0;
}
