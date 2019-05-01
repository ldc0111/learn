#include <stdio.h>
#include <math.h>

struct point {
    int x;
    int y;
};
struct rectangle {
    struct point p1;
    struct point p2;
};

int main() {
    struct point p3;
    scanf("%d %d", &p3.x, &p3.y);
    struct rectangle re;
    scanf("%d %d %d %d", &re.p1.x, &re.p1.y, &re.p2.x, &re.p2.y);
    if((p3.x > re.p1.x &&p3.x < re.p2.x && p3.y > re.p1.y && p3.y < re.p2.y) ||
        (p3.x < re.p1.x &&p3.x > re.p2.x && p3.y < re.p1.y && p3.y > re.p2.y)){
        printf("YES\n");
    }else{
        printf("NO\n");
    }
    return 0;
}