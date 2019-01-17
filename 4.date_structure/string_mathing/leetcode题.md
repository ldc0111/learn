####	005 马拉车算法

````c++
//马拉车算法，
//预处理：将每个字符的左边右边都加上一个相同的特殊字符，在第一位再加上一个特殊字符　
//第一步的目的是使得最长回文子串的长度有奇偶不确定的，都变为奇数个。第二处理是便于计算，和边界处理



#define min(a, b) ((a) < (b) ? (a) : (b))
char* longestPalindrome(char* s) {
    int len = strlen(s), j = 2, retlen = 0, retid = 0;
    char *t = (char *)calloc(len * 2 + 3, sizeof(char));
    char *q = (char *)calloc(len + 1, sizeof(char));
    int  *p = (int *)calloc(len * 2 + 2,sizeof(int)), id = 0, mx = 0;
    //1特殊处理，处理完数据存储在ｔ中
    t[0] = '@';
    t[1] = '#';
    for (int i = 0; i < len; i++) {
        t[j++] = s[i];
        t[j++] = '#';
    }
    t[j] = 0;
    //printf("%s", t);
    
    for (int i = 1; t[i]; i++) {
        //判断他是不是在上一个最大回文串内，如果是就取他对称点或他里右边界的最小值，如果不是就取１
        //2 * id - i = id - (i - id)
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while (t[i + p[i]] == t[i - p[i]]) p[i]++;//中心串左边和右边相等就继续扩大范围
        if (mx < i + p[i]) {　//看他是否超过上一个最大回文串的右边界，超过就替换
            id = i;
            mx = i + p[i];
        }
        if (retlen < p[i]) {
            retlen = p[i];//记录最大值长度
            retid = id;//记录最大值的下标
        }
    }
    //         			起始位置　　　　　　　　　　长度
    strncpy(q, s + (retid - retlen) /2 , retlen - 1);
    return q;
}
//马拉车算法
````



####	008

````c++
int myAtoi(char* str) {
    int sum = 0,z = 1, pos = 0;
    //跳过开头空格
    while (str[0] == ' ') str = str + 1;
    //判断正负
    if (str[0] == '-') z = -1, str = str + 1;
    else if (str[0] == '+') z = 1, str = str + 1;
    //判断合法性
    if (str[0] < '0' && str[0] > '9') return 0;
    
    while (str[0] >= '0' && str[0] <= '9') {
        pos = str[0] - '0';
        //超出范围处理，背下来吧
        if (sum * z > INT_MAX / 10 || (sum * z == INT_MAX /10 && pos * z > 7)) return INT_MAX;
        if (sum * z < INT_MIN / 10 || (sum * z == INT_MIN / 10 && pos * z < -8)) return INT_MIN;
        sum = sum * 10 + pos;
        str = str + 1;
    }
    return sum * z;
}
````



####	013

```c
int romanToInt(char* s) {
    int a[26] = {0};
    //建立映射关系
    a['I' - 'A'] = 1;
    a['V' - 'A'] = 5;
    a['X' - 'A'] = 10;
    a['L' - 'A'] = 50;
    a['C' - 'A'] = 100;
    a['D' - 'A'] = 500;
    a['M' - 'A'] = 1000;
    int num = 0,temp = a[s[0] - 'A'];//第一个字符
    char ch = s[0];//第一个字符
    for (int i = 1; s[i]; i++) {
        int ind = s[i] - 'A';
        //如果和上一个字符相同，ｔｅｍｐ累加
        if (a[ind] == a[ch - 'A']) {
            temp += a[ch -'A'];
        }else if (a[ind] < a[ch - 'A']){//如果面值小于上一个字符，则ｎｕｍ值更新，加上ｔｅｍｐ的值，ｔｅｍｐ值跟新
            num += temp;
            temp = a[ind];
        }else {//如果面值大于上一个值，则ｎｕｍ值更新，加上ｔｅｍｐ的值，ｔｅｍｐ值跟新
            num -= temp;
            temp = a[ind];
        }
        //记录上一个字符
        ch = s[i];
    }
    //因为最后一个没有跟新所以返回值位ｎｕｍ　+ temp
    return num + temp;
}
```



####	014

```c++
char* longestCommonPrefix(char** strs, int strsSize) {
    //判断合法性
    if (strs == NULL || strsSize == 0) return "";
    char ch;
    int j = 1, i = 0;
    char *str = (char *)malloc(sizeof(char) * strlen(strs[0]));
    //以第一个单词位基准，判断后面的单词每个字母与第一个单词的字符是不是相同的，如果不相同跳出，如果相同继续判断第一个单词的下一个字符
    for (; strs[0][i]; i++) {
        ch = strs[0][i];
        j = 1;
        while (j < strsSize && ch == strs[j][i]) j++;
        if (j < strsSize) break;
        str[i] = ch;
    }
    str[i] = 0;
    return str;
}
```



####	028 模板题

```c
int KMP(char *text, char *pattern) {
    int len1 = strlen(text), len2 = strlen(pattern);
    int *next = (int *)malloc(sizeof(int) * len2);
    next[0] = -1;
    int j = -1;
    for (int i = 1; pattern[i]; i++) {
        while (j >= 0 && pattern[j + 1] != pattern[i]) j = next[j];
        if (pattern[j + 1] == pattern[i]) j += 1;
        next[i] = j;
    }
    j = -1;
    for (int i = 0; text[i]; i++) {
        while (j >= 0 && pattern[j + 1] != text[i]) j = next[j];
        if (pattern[j + 1] == text[i]) j += 1;
        if (pattern[j + 1] == 0) return i - len2 + 1;
    }
    return -1;
}

int Sunday(char *text, char *pattern) {
    int len1 = strlen(text), len2 = strlen(pattern);
    int ind[127] = {0};
    for (int i = 0; i < 127; i++) ind[i] = len2 + 1;
    for (int i = 0; pattern[i]; i++) ind[i] = len2 - i;
    for (int i = 0; i <= len1 - len2;) {
        int j = 0;
        for (; j < len2; j++) {
            if (pattern[j] != text[i + j]) break;
        }
        if (j == len2) return i;
        i += ind[i + len2];
    }
    return -1;
}


int strStr(char* haystack, char* needle) {
    if (strlen(needle) == 0) return 0;
    return KMP(haystack, needle);
}
```

####	036

##### 两次遍历

```c
bool isValidSudoku(char** board, int boardRowSize, int boardColSize) {
    int flag = 1;
    int a[10] = {0}, b[10] = {0};//映射数组
    //横竖查重
    for (int i = 0; i < boardRowSize && flag; i++) {
        memset(a,0,sizeof(a)); memset(b, 0,sizeof(b));
        for (int j = 0; j < boardRowSize && flag; j++) {
            if (board[i][j] != '.'){
                if(a[board[i][j] - '0'] != 0) flag = 0;
                a[board[i][j] - '0'] = 1;
            }
            if (board[j][i] != '.') {
                if (b[board[j][i] - '0'] != 0) flag = 0;
                b[board[j][i] - '0'] = 1;
            }
        }
    }
    //3*3格查重
    for (int i = 1; i < 9 && flag; i += 3) {
        for (int j = 1; j < 9 && flag; j += 3) {
            memset(a,0, sizeof(a));
            for (int k = -1; k <= 1; k++) {
                for (int w = -1; w <= 1; w++) {
                    if (board[i + k][j + w] == '.') continue;
                    if (a[board[i + k][j + w] - '0'] != 0) flag = 0;
                    a[board[i + k][j + w] - '0'] = 1;
                }
            }
        }
    }
    return flag;
}
```

#### 单次遍历－有美感的代码

````c
bool isValidSudoku(char** board, int boardRowSize, int boardColSize) {
    int x = 0;
    int a[9][9] = {0},b[9][9] = {0}, c[9][9] = {0};
    for (int i = 0; i < boardRowSize; i++) {
        for (int j = 0; j < boardRowSize; j++) {
            if(board[i][j] == '.') continue;
            x = board[i][j] - '1';
            if(a[i][x] || b[x][j] || c[3 * (i / 3) + j / 3][x]) return 0;
            a[i][x] = 1;
            b[x][j] = 1;
            c[3 * (i / 3) + j / 3][x] = 1;
        }
    }
    return 1;
}
````



####	058

#####	最长的 最慢的

````c
int lengthOfLastWord(char* s) {
    int i = 0, a = 0, len = strlen(s);
    while (s[len - 1] == ' ') len -= 1;
    for (;i < len; i++) {
        if(s[i] != ' ') continue;
        a = i + 1;
    }
    return i - a;
}
````

##### 中间的　没用ｓｔｒｌｅｎ函数的

````c
int lengthOfLastWord(char* s) {
    int res = 0;
    for (int i = 0; s[i]; i++) {
        if(i > 0 && s[i - 1] == ' ' && s[i] != ' ') res = 1;
        else if (s[i] != ' ') res++;
    }
    return res;
}
````

##### 最短的最快的 吹爆的

````c
int lengthOfLastWord(char* s) {
    int res = 0,len = strlen(s);
    while (len > 0 && s[len - 1] == ' ') len -= 1;
    while (len > 0 && s[len - 1] != ' ') res++,len--;
    return res;
}
````



####	125

````c
bool isPalindrome(char* s) {
    int len = strlen(s),flag = 1;
    int i = 0, j = len - 1, temp = 0;
    while (i < j && flag) {
        while(i < j &&!(s[i] >= '0' && s[i] <= '9' || s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z')) i++;
        while(i < j && !(s[j] >= '0' && s[j] <= '9' || s[j] >= 'a' && s[j] <= 'z' || s[j] >= 'A' && s[j] <= 'Z')) j--;
        if(i >= j) break;
        temp = s[i] ^ s[j];
        i++, j--;
        if (temp == 0 ||temp == 32) continue;
        flag = 0;
        
    }
    return flag;
}
````



####	165

````c
int getint(char *s, int *ind){
    int num = 0;
    while(s[*ind] != '.' && s[*ind] != 0) {
        num = num * 10 + (s[*ind] - '0');
        (*ind)++;
    }
    return num;
}

int compareVersion(char* version1, char* version2) {
    int a = 0, b = 0, len1 = strlen(version1), len2 = strlen(version2), k1 = 0, k2 = 0;
    int flag = 0;
    while (a < len1 || b < len2) {
        if(a < len1)   k1 = getint(version1, &a);
        else k1 = 0;
        if(b < len2)   k2 = getint(version2, &b);
        else k2 = 0;
        a++,b++;
        if(k1 == k2) continue;
        flag = (k1 > k2 ? 1 : -1);
        break;
    }
    return flag;
}
````



####	205

````c
bool isIsomorphic(char* s, char* t) {
    int a[256] = {0},b[256] = {0};
    int flag = 1;
    for (int i = 0; s[i] && flag; i++) {
        if(a[s[i]] == 0 && b[t[i]] == 0) a[s[i]] = t[i],b[t[i]] = s[i];
        else if (a[s[i]] != t[i]) flag = 0;
    }
    return flag;
}
````



####	242

````c
bool isAnagram(char* s, char* t) {
    int len1 = strlen(s), len2 = strlen(t);
    if (len1 != len2) return 0;
    int a[256] = {0},b[256] = {0};
    for (int i = 0; i < len1; i++) {
        a[s[i]]++;
        b[t[i]]++;
    }
    for(int i = 0; i < 256; i++) {
        if(a[i] != b[i]) return 0;
    }
    return 1;
}
````



####	290 双向哈希

```c
typedef struct hashTable{
    char ** value;
    char **s;
    int *temp;
    int size;
}hashtable;

void init(hashtable *h,int n) {
    h->size = 4 * n;
    h->value = (char **)calloc(h->size,sizeof(char **));
    h->s = (char **)calloc(h->size, sizeof(char **));
    h->temp = (int *)calloc(h->size, sizeof(int));
    return ;
}
int hashfunc(hashtable *h, char *str) {
    int code = 0;
    for (int i = 0; str[i]; i++) {
        code = (code * 26 + (str[i] - 'a')) % h->size;
    }
    return code;
}
//单向映射
int insert(hashtable *h, char *str, char *s){
    int hash = hashfunc(h, str);
    int index = hash;
    while (h->temp[index]) {
        index = (index + 1) % h->size;
    }
    
    h->temp[index] = 1;
    h->s[index] = strdup(str);//源，　
    h->value[index] = strdup(s);//目的
    return 1;
}
int search(hashtable *h, char *str, char *s) {
    int hash = hashfunc(h, str);
    int index = hash;
    while (h->temp[index]) {
        if(strcmp(h->s[index],str) != 0) {
            index = (index  + 1) % h->size;
            continue;
        }
        if (strcmp(h->value[index], s) == 0) return 1;//插过且两个相等
        else return -1;//没插过，两个不相等
    }
    //没插过
    return 0;
}

char *getstr(char *s, int *ind) {
    int n = *ind;
    while (s[n] != 0 && s[n] != ' ') n++;
    char *p = (char *)calloc((n - *ind + 1), sizeof(char));
    strncpy(p, &s[*ind], n - *ind);
    (*ind) = n + 1;
    return p;
}

bool wordPattern(char* pattern, char* str) {
    int ind1 = 0,ind2 = 0, temp1 = 0, temp2 = 0;
    hashtable h1,  h2;
    char p[2];
    char *q = NULL;
    init(&h1,strlen(pattern));
    init(&h2,strlen(pattern));
    while (pattern[ind1] != 0 && str[ind2] != 0) {
        p[0] = pattern[ind1++], p[1] = 0;
        q = getstr(str, &ind2);
        temp1 = search(&h1, p, q);
        temp2 = search(&h2, q, p);
        //printf("%d %d\n", temp1, temp2);
        if (temp1 < 0 || temp2 < 0) return 0;
        else if (temp1 == 0 && temp2 == 0) {
            insert(&h1, p, q);
            insert(&h2, q, p);
        }
    }
    if(ind1 < strlen(pattern) || ind2 < strlen(str)) return 0; 
    return 1;
}
```

####	344

````c
#define swap(a,b){\
    __typeof(a) temp = a;\
    a = b;\
    b = temp;\
}

char* reverseString(char* s) {
    int h = 0,tail = strlen(s) - 1;
    while (h < tail) {
        swap(s[h], s[tail]);
        h++, tail--;
    }
    return s;
}
````

####	345

````c
#define swap(a,b){\
    __typeof(a) temp = a;\
    a = b;\
    b = temp;\
}
char* reverseVowels(char* s) {
    int h = 0, tail = strlen(s) - 1;
    while (h < tail) {
        while (h < tail && !(s[h] == 'a' || s[h] == 'e' || s[h] == 'i' || s[h] =='o' || s[h] == 'u'
                            ||s[h] == 'A' || s[h] == 'E' || s[h] == 'I' || s[h] =='O' ||s[h] == 'U')) h++;
        while (h < tail && !(s[tail] == 'a' || s[tail] == 'e' || s[tail] == 'i' || s[tail] == 'o' || s[tail] == 'u'
                            ||s[tail] == 'A' || s[tail] == 'E' || s[tail] == 'I' || s[tail] == 'O' || s[tail] == 'U')) tail--;
        swap(s[h], s[tail]);
        h++, tail--;
    }
    return s;
}
````



####	383

````c
bool canConstruct(char* ransomNote, char* magazine) {
    int a[256] = {0}, b[256] = {0};
    for (int i = 0; magazine[i]; i++) {
        a[magazine[i] + 128]++;
    }
    for (int i = 0; ransomNote[i]; i++) {
        b[ransomNote[i] + 128]++;
    }
    for (int i = 0; i < 256; i++) {
        if(b[i] > a[i]) return 0;
    }
    return 1;
}
````

####	387

```c
int firstUniqChar(char* s) {
    int min = 100000000;
    int a[256] = {0},b[256] = {0};//ａ统计出现的位置，ｂ统计出现的个数
    for (int i = 0; s[i]; i++) {
        a[s[i] + 128] = i;
        b[s[i] + 128]++;
    }
    for (int i = 0; i < 256; i++) {
        if(b[i] >= 2 || b[i] == 0) continue;
        min = min < a[i] ? min : a[i];
    }
    if(min == 100000000) return -1;
    return min;
}
```

