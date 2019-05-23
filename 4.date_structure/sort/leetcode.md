####　1.

#####　解法１，排序，前后指针

`````c
//解法1，排序，然后遍历一遍，设定两个指针一个头指针，一个尾指针，相加，如果相加大于与尾指针--，小于头指针加加
void quick_sort(int *nums, int l, int r){
    if(r <= l) return ;
    int x = l,y = r,z = nums[l];
    while(x < y){
        while(x < y && nums[y] >= z) y--;
        if(x < y) nums[x++] = nums[y];
        while(x < y && nums[x] <= z) x++;
        if(x < y) nums[y--] = nums[x];
    }
    nums[x] = z;
    quick_sort(nums,l,x - 1);
    quick_sort(nums, x + 1,r);
    return ;
}


int* twoSum(int* nums, int numsSize, int target) {
    int *temp_nums = (int *)malloc(sizeof(int) * numsSize);
    memcpy(temp_nums,nums,sizeof(int) * numsSize);
    quick_sort(nums,0,numsSize - 1);
    int *temp = (int *)calloc(sizeof(int),2);
    temp[0] =  -1;
    temp[1] = -1;
    int p = 0,q = numsSize - 1;
    
    while(p < q){
        if((nums[p] + nums[q]) > target){
            q--;
        } else if(nums[p] + nums[q] < target) {
            p++;
        } else {
            break;
        }
    }
    for(int i = 0;i < numsSize; i++){
        if(temp_nums[i] == nums[p] && temp[0] == -1){
            temp[0] = i;
        }
        if(temp_nums[i] == nums[q]){
            temp[1] = i;
        }
    }
    //temp[0] = p;
    //temp[1] = q;
    return temp;
}
`````

##### 解法２ 哈希表解法

`````c
//解法2哈希表一遍哈希表，每遍历元素遍历的同时查询traget-nums[i]是否存在与哈希表中，如果存在返回，如果不存在插入哈希表

typedef struct Data{
    int val,ind;
}Data;
typedef struct HastTable{
    Data *data;
    int *flag;
    int size;
}HashTable;
int hashFunc(int val){
    return val & 0x7fffffff;
}

HashTable *init(int n){
    HashTable * h = (HashTable *)malloc(sizeof(HashTable));
    h->size = n << 1;
    h->data = (Data *)calloc(sizeof(Data),h->size);
    h->flag = (int *)calloc(sizeof(int),h->size);
    return h;
}



int insert(HashTable *h, int val,int ind){
    int hash = hashFunc(val);
    int pos = hash %  h->size;
    int times = 1;
    while(h->flag[pos]){
        pos +=(times *times);
        times++;
        pos %= h->size;
    }
    h->data[pos].val = val;
    h->data[pos].ind = ind;
    h->flag[pos] = 1;
    return 0;
}

Data *search(HashTable *h, int val){
    int hash = hashFunc(val);
    int pos = hash % h->size;
    int times = 1;
    while(h->flag[pos] && h->data[pos].val != val){
        pos +=(times *times);
        times++;
        pos %= h->size;
    }
    if(h->flag[pos] == 0) return NULL;
    return h->data + pos;
}

void clear(HashTable *h){
    if(h == NULL) return ;
    free(h->data);
    free(h->flag);
    free(h);
    return ;
}



int* twoSum(int* nums, int numsSize, int target) {
    HashTable * h = init(numsSize);
    int *ret = (int *)malloc(sizeof(int) * 2);
    for(int i = 0; i < numsSize ; i++){
        Data *result = search(h,target - nums[i]);
        if(result){
            ret[0] = result->ind;
            ret[1] = i;
            break;
        }
        insert(h,nums[i],i);
    }
    clear(h);
    return ret;
}
`````

##### 3.暴力解法

`````c
//解法3暴力解法，两层for循环遍历数组，如果有两个元素相加等于target返回，并将结果存入一个数组内

int* twoSum(int* nums, int numsSize, int target) {
    int a = 0,b = 0;
    int flag = 1;
    for(int i = 0; i < numsSize && flag; i++){
        for(int j = i +1; j < numsSize && flag; j++){
            if(target == nums[i] + nums[j]){
                flag = 0;
                a = i;
                b = j;
            }
        }
    }
    int *c = (int *)malloc(sizeof(int) * 2);
    c[0] = a;
    c[1] = b;
    return c;
}
`````

#### 3.

##### 解法１，滑动窗口法,头尾指针控制窗口大小

````c
//解法1，用可伸缩的滑动窗口，标记数组的作用是统计这个字符是否在窗口内，两个指针表示滑动窗口的前和后，，每次进入一个元素，如果窗口内没有，
//temp++，标记值设为1，窗口内有，前指针指向的元素标记值清0，前指针后移，直到前指针指向的元素与后指针指向的
//元素相同，max等于最大的temp值。
int lengthOfLongestSubstring(char* s) {
    int a[256] = {0};
    int max = 0, temp = 0, ti = 0;;
    for(int i = 0; s[i]; i++){
        if(a[s[i]] == 0){
            temp++;
            a[s[i]] = 1;
        }else {
            while(s[ti] != s[i]){
                a[s[ti]] = 0;
                ti++;
                temp--;
            }
            ti++;
        }
        if(temp > max) {
            max = temp;
        }
    }
    return max;
}
````

##### 解法２，滑动窗口法，一个变量控制窗口大小

````c
//解法2，标记数组标记每个元素i之前后出现的位置，len表示滑动窗口的长度，滑动窗口内部表示不重复的元素的数量，
//遍历元素更新，len值，窗口变大，当出现重复元素时，窗口缩小到踢出重复元素及重复元素之前的元素大小，更新标记数组
//当窗口长度大于len，更新len，注意开始有一个虚拟位
int lengthOfLongestSubstring(char* s) {
    int pos[256] = {0}, len, ans = 0;
    memset(pos, -1, sizeof(pos));
    for(int i = 0; s[i]; i++){
        len++;
        if(i - pos[s[i]] < len) len = i - pos[s[i]];
        pos[s[i]] = i;
        if(len > ans) ans = len;
    }
    return ans;
}
````

##### 解法３，滑动窗口+二分

`````c
//解法3，二分模型11111000000，设定一个滑动窗口的大小，
//每出现一个字符，相应字符标记位加1，如果标记位等于1，则表示新进入了一个字符，当i大于len时，窗口向后移动，响应字符标记减1，
//注意，串口内统计的是不重复字符的数量，当数量等于窗口长度时，表示存在一个长度为len的字符串，返回真，
int chack(char *s,int len){
    int num[256] = {0}, cnt = 0;
    for (int i = 0; s[i]; i++){
        num[s[i]]  += 1;
        cnt += (num[s[i]] == 1);
        if (i >= len){
            num[s[i - len]]--;
            cnt -= (num[s[i - len]] == 0);
        }
        if(cnt == len) return 1;
    }
    return 0;
}

int lengthOfLongestSubstring(char* s) {
    int head = 0,tail = strlen(s), mid;
    while(head < tail){
        mid = (head + tail + 1) >> 1;
        if(chack(s,mid) == 1) head = mid;
        else tail = mid - 1;
    }
    return head;
}
`````

#####　总结

`````c
//总结：这三种解法都用到了滑动窗口的思想，
//第一个是可伸缩的滑动窗口，有两个前后指针控制窗口长度，标记数组仅仅表示，字符是否出现过，窗口内部就是不重复字符的长度，
//第二个是也是一个可伸缩的滑动窗口，滑动窗口的长度由一个变量len控制，标记数组标记每个元素i之前后出现的位置，遍历时，没有重复元素，不断增加标记数长度，出现重复数组时，就将重复元素及以前的元素踢出窗口
//第三个是设定一个窗口大小,看是否存在一个无重复字符的字符串，满足等于窗口大小，在外面嵌套一层二分，模型11110000，寻找到最大的len
`````

####　4.

#####　解法，二分模型。

**注意越界判断，奇偶数据量判断**

````c
#define min(a,b) ((a) < (b) ? (a) : (b))
//ｋ表示需要寻找到的，第ｋ位大小的值，如果其中有一个越界，就直接统计下一个的下标并返回
//注意ｂ１，ｂ２初始值都为０，要寻找第小的值，如果在一个数组中则应该表示为，ｂ１　＋ k - 1，比如要寻找第三小的，则下标应该为 2
void findk(int *num1, int *num2, int *b1, int *b2, int e1, int e2, int k){
    while(k > 1) {
        if (*b1 == e1) { *b2 = *b2 + k - 1; return;}//b1越界
        else if (*b2 == e2) {*b1 = *b1 + k - 1; return;}//b2越界
        int a1, a2;
        a1 = min(k >> 1, e1 - *b1);//找到数组剩下的元素和k取一半的元素的最小值，目的放置取值时越界
        a2 = min(k - (k >> 1), e2 - *b2);//同上
        //a1，a2表示第几小的值，转化为坐标时应该是b1 +ａ１－１，比如取第１小的值，应该是１＋ｂ１－１，如果不减的话，标记的就是从ｂ１开始的第二小的值，就越过了
        if(num1[a1 + *b1 - 1] > num2[a2 + *b2 - 1]){//大于
            *b2 += a2;//舍去num2标记以及标记的之间的值，
            k -= a2;//ｋ减去ｎｕｍｓ１舍去的数量
        } else {//小于
            *b1 += a1;//同上
            k -= a1;
        }
    }
}
//得到b1，b2标记之中的最小值，如果有一个越界，直接返回另一个，最小值的那个标记指针后移一位
//这个函数是个亮点
int get_min_num(int *num1, int *num2, int *b1, int *b2, int e1, int e2){
    int ret;
    if (*b1 == e1) {ret = num2[*b2]; *b2 += 1;}
    else if (*b2 == e2){ret = num1[*b1]; *b1 += 1;}
    else{
        ret = min(num1[*b1], num2[*b2]);
        if(ret == num1[*b1]) *b1 += 1;
        else *b2 += 1;
    }
    return ret;
}




//1111110000000
//二分模型111110000，找到最后一个一，是当k等于1时，b1，b2指向的位置，
//问题：(nums1Size + nums2Size + 1)为什么要+1，
//因为当他们的和为奇数时，我们需要找一个值，那个值为(nums1Size + nums2Size) >> 1 + 1,
//当他们的和为偶数时，我们要找的值为(nums1Size + nums2Size) >> 1,(nums1Size + nums2Size) >> 1 + 1
//所以我们总要寻找(nums1Size + nums2Size)>> 1 + 1,的值，所以我们第一直觉是两种方案都寻找(nums1Size + nums2Size) >> 1的值，
//这样让和位奇数是，还需要往后移动一位最小值，再寻找答案，
//当和为偶数时，就需要统计两个值，这中方案，需要加一个奇数和偶数的特判，
//而船长这总做法就牛逼了，加１之后，对于奇数我们找的就是(nums1Size + nums2Size)　>> 1 + 1位置的值，
//对于偶数我们找的就是(nums1Size + nums2Size)>> 1 的值，而且奇数只用统计一次，偶数需要统计两次，就可以写成下面ｆｏｒ循环的模样了，ｏｒｚ
//而上一种写法都需要统计两次，奇数第一次不要，不够优美，，，，，
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int b1 = 0, b2 = 0, sum = 0;
    findk(nums1, nums2, &b1, &b2, nums1Size, nums2Size, (nums1Size + nums2Size + 1) >> 1);
    printf("%d %d", b1, b2);
    int i, j;
    for(i = (nums1Size + nums2Size) % 2,j = 0; i < 2; i++,j++){
        sum += get_min_num(nums1, nums2, &b1, &b2, nums1Size, nums2Size);
    }
    return sum * 1.0 / j;
}

````

#### 21

````c
//目标将２离岸边合并到１链表中
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    if(l1 == NULL && l2 == NULL) return 0;//排除特殊情况
    if(l1 == NULL && l2 != NULL) return l2;
    if(l1 != NULL && l2 == NULL) return l1;
    struct ListNode ll1,ll2;//建立虚拟头结点
    ll1.next= l1,ll2.next = l2;
    struct ListNode *p1 = &ll1,*p2 = &ll2,*cur;//
    while(p1 != NULL && p2 != NULL && p1->next != NULL && p2->next != NULL){//防止指向为空
        while(p1->next != NULL &&(p2->next == NULL || p1->next->val <= p2->next->val)) p1 = p1->next;//当１链表指针指向元素小于２指针指向元素
        while(p2->next != NULL && (p1->next == NULL || p1->next->val > p2->next->val)){//当２链表指针指向元素小于１节点，插入，并从２链表中删除
            cur = p2->next;
            p2->next = cur->next;
            cur->next = p1->next;
            p1->next = cur;
            p1 = p1->next;
        }
    }
    return ll1.next;
}
````

#### 35

过于简单，不贴了

#### 38

##### 解法１，递归法

````c
char* countAndSay(int n) {
    if(n == 1) return strdup("1");
    char *s = countAndSay(n - 1);
    int len = 1;
    for(int i = 1;  s[i]; i++) len += (s[i] != s[i - 1]);
    len = len << 1 + 1;
    char *ret = (char *)calloc(sizeof(char),len);
    
    int num = s[0] - '0',cnt = 1,j = 0;
    for(int i = 1; s[i - 1]; i++){
        if(s[i] == s[i - 1]){
            cnt += 1;
        }else {
            j += sprintf(ret + j, "%d%d",cnt,num);
            cnt = 1;
            num = s[i] - '0';
        }
    }
    free(s);
    return ret;
}
````

##### 解法２，循环数组法

````c
char* countAndSay(int n) {
    char **str = (char **)malloc(sizeof(char *) * 2);
    str[0] = (char *)calloc(sizeof(char),5000);
    str[1] = (char *)calloc(sizeof(char),5000);
    int k = 0;
    str[0][0] = '1';//第一个数组
    while(k < n -1){//之后要进行的论数
        int temp = 1,　x = 0;//ｔｅｍｐ是上个元素的个数
        for(int i  = 1;str[k % 2][i - 1]; i++){//
            if(str[k % 2][i] == str[k % 2][i - 1]){//这个和前一个相等ｔｅｍｐ＋＋
                temp++;
            } else{//如果不相等，就统计上一个，并且标记到下一个数组中
                str[(k + 1) % 2][x++] = temp + '0';//
                str[(k + 1) % 2][x++] = str[k % 2][i - 1];
                temp = 1;
            }
        }
        k++;
    }
    printf("k = %d %d\n",k,strlen(str[k % 2]));
    return str[k % 2];
}
````

#### 88,

过于简单，不贴了

#### 217

````c
//模板哈希，没啥解释的
typedef struct data{
    int val;
}Data;

typedef struct HashTable{
    Data *data;
    int  *flag;
    int  size;
}HashTable;

HashTable * init(int len){
    HashTable * h = (HashTable *)malloc(sizeof(HashTable));
    h->size = len << 1;
    h->data = (Data *)calloc(sizeof(Data),h->size);
    h->flag = (int *)calloc(sizeof(int), h->size);
    return h;
}
int hashFunc(int val){
    return val & 0x7fffffff;//哈希值除去负数
}


int search(HashTable *h, int val){
    int hash = hashFunc(val);
    int pos = hash % h->size;
    int times = 1;
    while(h->flag[pos] && h->data[pos].val != val){
        pos += (times * times);
        times++;
        pos %= h->size;
    }
    if(h->flag[pos] == 0) return 0;
    return 1;
    
}
void insert(HashTable *h, int val){
    int hash = hashFunc(val);
    int pos = hash % h->size;
    int times = 1;
    while(h->flag[pos]){
        pos += (times * times);
        times++;
        pos %= h->size;
    }
    h->data[pos].val = val;
    h->flag[pos] = 1;
    return ;
}
void clear(HashTable *h){
    if(h == NULL) return ;
    free(h->data);
    free(h->flag);
    free(h);
    return ;
}

bool containsDuplicate(int* nums, int numsSize) {    
    HashTable *h = init(numsSize);
    for(int i = 0; i < numsSize; i++){
        if(search(h,nums[i])){//找到
            return true;
        }
        insert(h,nums[i]);
    }
    clear(h);
    
    return false;
}

````

#### 219

````c
//哈希元素存放两个值，一个元素值，一个元素下标，并且存储过程中会覆盖相同元素用来更新下标
typedef struct data{
    int val,ind;
}Data;

typedef struct HashTable{
    Data *data;
    int *flag;
    int size;
}HashTable;
HashTable * init(int len){
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = len << 1;
    h->data = (Data *)calloc(sizeof(Data),h->size);
    h->flag = (int *)calloc(sizeof(int), h->size);
    return h;
}

int hashFunc(int val){
    return val & 0x7fffffff;
}
int search(HashTable *h, int val){
    int hash = hashFunc(val);
    int pos = hash % h->size;
    int times = 1;
    while(h->flag[pos] && h->data[pos].val != val){
        pos +=(times * times);
        times++;
        pos %= h->size;
    }
    if(h->flag[pos] == 0) return -1;
    return h->data[pos].ind;
}
int insert(HashTable *h,int val,int ind){
    int hash = hashFunc(val);
    int pos = hash % h->size;
    int times = 1;
    while(h->flag[pos] && h->data[pos].val != val){
        pos +=(times * times);
        times++;
        pos %= h->size;
    }
    h->data[pos].val = val;
    h->data[pos].ind = ind;
    h->flag[pos] = 1;
    return 0;
}
int clear(HashTable *h){
    if(h == NULL) return ;
    free(h->data);
    free(h->flag);
    free(h);
    return ;
}



bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    HashTable *h = init(numsSize);
    for(int i = 0; i < numsSize; i++){
        int temp = search(h, nums[i]);//存在返回下标，不催在返回-1
        if(temp != -1 && i - temp <= k){
            return true;
        }
        insert(h,nums[i],i);//插入过程会覆盖相同元素
    }
    //printf("%d",h->flag[1]);
    return false;
}
````

####　278

过于简单，不贴了

#### 349

````c
typedef struct Data{
    int val;
}Data;

//模板哈希，存储多一个是否被查询过的量，查询过再次查询就返回失败
typedef struct HashTable{
    Data *data;
    int *flag;
    int *sea;
    int size;
}HashTable;

HashTable * init(int len){
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size  = len << 1;
    h->data = (Data *)calloc(sizeof(Data), h->size);
    h->flag = (int *)calloc(sizeof(int), h->size);
    h->sea = (int *)calloc(sizeof(int),h->size);
    return h;
}

int hashFunc(int val){
    return val & 0x7fffffff;
}



int search(HashTable *h,int val){
    int hash = hashFunc(val);
    int pos = hash % h->size;
    int times = 1;
    while(h->flag[pos] && h->data[pos].val != val){
        pos += (times * times);
        times++;
        pos %= h->size;
    }
    if(h->flag[pos] == 0) return 0;
    if(h->sea[pos] == 1) return 0;
    if(h->data[pos].val == val){
        h->sea[pos] = 1;
        return 1;
    }
    return 0;
}

int insert(HashTable *h,int val){
    int hash = hashFunc(val);
    int pos = hash % h->size;
    int times = 1;
    while(h->flag[pos] && h->data[pos].val != val){
        pos += (times * times);
        times++;
        pos %= h->size;
    }
    h->data[pos].val = val;
    h->flag[pos] = 1;
    return 0;
}


void clear(HashTable *h){
    if(h == NULL) return ;
    free(h->data);
    free(h->flag);
    free(h->sea);
    free(h);
    return ;
}



int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    if(!nums1Size || !nums2Size) return NULL;
    HashTable * h = init(nums1Size);
    int mi = nums1Size < nums2Size ? nums1Size : nums2Size;
    int *nums = (int *)malloc(sizeof(int) * mi);
    (*returnSize) = 0;
    for (int i = 0; i < nums1Size; i++){
        insert(h,nums1[i]);//重复元素覆盖
    }
    for(int i = 0; i < nums2Size; i++){
        if(search(h,nums2[i])){//查过一遍就标记，再查就返回失败
            nums[(*returnSize)++] = nums2[i];
        }
    }
    
    return nums;
}

````

#### 350

````c
//模板哈希，存储量多一个元素个数，相同的元素会被累加的对应的元素数量上，每次查询减１，减到０，后面再次查询返回失败
typedef struct Data{
    int val;
}Data;
typedef struct HashTable{
    Data * data;
    int *flag;
    int *times;
    int size;
}HashTable;

HashTable * init(int len){
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = len << 1;
    h->data = (Data *)calloc(sizeof(Data),h->size);
    h->flag = (int *)calloc(sizeof(Data), h->size);
    h->times = (int *)calloc(sizeof(int),h->size);
    return h;
}
int hashFunc(int val){
    return val &0x7fffffff;
}


int search(HashTable *h,int val){
    int hash = hashFunc(val);
    int pos = hash% h->size;
    int times = 1;
    while(h->flag[pos] && h->data[pos].val != val){
        pos +=(times * times);
        times++;
        pos %= h->size;
    }  
    if(h->flag[pos] == 0) return 0;
    if(h->times[pos] > 0){
        h->times[pos]--;
        return 1;
    }
    return 0;
}
void insert(HashTable *h,int val){
    int hash = hashFunc(val);
    int pos = hash% h->size;
    int times = 1;
    while(h->flag[pos] && h->data[pos].val != val){
        pos +=(times * times);
        times++;
        pos %= h->size;
    }
    h->data[pos].val = val;
    h->flag[pos] = 1;
    h->times[pos]++;
    return ;
}

void clear(HashTable *h){
    if(h == NULL) return ;
    free(h->data);
    free(h->flag);
    free(h);
    return ;
}

int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    if(!nums1Size|| !nums2Size)  return 0;
    HashTable *h = init(nums1Size);
    int mi = nums1Size < nums2Size ? nums1Size : nums2Size;
    int *nums = (int *)malloc(sizeof(int) * mi);
    (*returnSize) = 0;
    for(int i = 0; i < nums1Size; i++){
        insert(h,nums1[i]);
    }
    for(int i = 0; i < nums2Size; i++){
        if(search(h,nums2[i])){
            nums[(*returnSize)++] = nums2[i];
        }
    }
    clear(h);
    return nums;
}
````

#### 374

##### 解法１，000111模型

`````c
///０００１１１模型
class Solution {
public:
    int guessNumber(int n) {
        long long  head = 0,tail = n,mid;
        while(head < tail){
            mid = (head + tail) >> 1;
            //if(guess(mid) == 0) return mid;
            if(guess(mid)  == 1) head = mid + 1;
            else tail = mid;
        }
        return head;
    }
};
`````

##### 解法２, 111000模型

````c
//１１１１０００模型
class Solution {
public:
    int guessNumber(int n) {
        long long  head = 0,tail = n,mid;
        while(head < tail){
            mid = (head + tail + 1) >> 1;
            if(guess(mid)  == -1) tail = mid - 1;
            else head = mid;
        }
        return head;
    }
};
````

#### 378

#####　解法　１１１１０００　模型

````c
//返回这个元素是第几小个元素，而我们之前统计的都是多少个比他小，所以返回值要加１，
int find(int **matrix, int matrixRowSize, int matrixColSize,int val,int *temp){//返回这个元素是第几个元素，并看他是否存在
    int ans = 0,k = matrixRowSize - 1;
    for(int i = 0; i < matrixColSize; i++){//列
        while( k >= 0 && matrix[k][i] > val) k--;//找到第一个小于等于它的元素的位置
        if (k < 0 ) return ans + 1;//ｋ越界，证明以后都没有匀速比他小，直接返回
        if(matrix[k][i] == val) *temp = 1,k--;//成立，表示元素存在,因为我们要统计这个元素排第几所以跳过相同的元素
        ans = ans + k + 1;//统计这一列中比特小的元素数量ｋ表示的是下标，所以要加１
    }
    return ans + 1;
}

//１１１１１１１１１１００００００００模型。
int kthSmallest(int **matrix, int matrixRowSize, int matrixColSize, int k) {
    int head = matrix[0][0],tail = matrix[matrixRowSize - 1][matrixColSize - 1],mid;
    int temp = 0;
    //printf("%d ",find(matrix, matrixRowSize,  matrixColSize, 17, &temp));
    //printf("%d\n",temp);
    while(head < tail){
        int temp = 0;
        mid = (head + tail + 1) >> 1;
        int tk = find(matrix, matrixRowSize,  matrixColSize, mid, &temp);
        if(tk == k && temp == 1) return mid;//是mid 并且存在
        if(tk == k && temp == 0) head = mid + 1;//是第k，但是不存在说明这个数小了；
        else if(tk < k){//排名不对的情况
            head = mid;
        }else{
            tail = mid - 1;
        }
    }
    return head;
}
````



####　总结

第三题三种解法可以理解理解滑动窗口的用法，

374可以学习到两种模型的转换，当一道题是３中状态时，我们可以替换成两种中的任意一个模型，之关注两种模型

２１７，２１９，３４９，３５０可以学习到哈希表的灵活性与方便性

４，重点是边界判断，与奇偶判断

３７８是二分模板，没啥好说的