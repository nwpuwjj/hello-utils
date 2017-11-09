
函数名: strdup
功  能: 将串拷贝到新建的位置处
用  法: char *strdup(char *str)；
 
这个函数在linux的man手册里解释为：
The strdup() function returns a pointer toa new string which is a
duplicate of the string s. Memory for thenew string is obtained with
malloc(3), and can be freed with free(3).
The strndup() function is similar, but onlycopies at most n charac-
ters. If s is longer than n, only ncharacters are copied, and a termi-
nating NUL is added.
 
strdup函数原型：
strdup()主要是拷贝字符串s的一个副本，由函数返回值返回，这个副本有自己的内存空间，和s不相干。strdup函数复制一个字符串，使用完后要记得删除在函数中动态申请的内存，strdup函数的参数不能为NULL，一旦为NULL，就会报段错误，因为该函数包括了strlen函数，而该函数参数不能是NULL。
strdup的工作原理:
char * __strdup (const char *s)
{
size_t len =strlen (s) + 1;
void *new =malloc (len);
if (new == NULL)
return NULL;
return (char *)memcpy (new, s, len);
}

/** Duplicates a string or die if memory cannot be allocated
 * @param s String to duplicate
 * @return A string in a newly allocated chunk of heap.
 */
char *
safe_strdup(const char *s)
{
    char *retval = NULL;
    if (!s) {
        debug(LOG_CRIT, "safe_strdup called with NULL which would have crashed strdup. Bailing out");
        exit(1);
    }
    retval = strdup(s);
    if (!retval) {
        debug(LOG_CRIT, "Failed to duplicate a string: %s.  Bailing out", strerror(errno));
        exit(1);
    }
    return (retval);
}
