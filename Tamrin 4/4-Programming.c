#line 1000
// Add Your Code under this
//403100043
#include <stdio.h>
#define FOR while
#define begin { tests--;
#define end }                   
#define start int main()
#define where_am_i printf("You are at %d\n",__LINE__)
#define execute(x,y,z, a, b) x##y##z(a, b)
#define execute2(a ,b ,c) ((b) a (c))

    





// DO NOT CHANGE below
int sum(int a, int b){ return a + b; }
int mns(int a, int b){ return a - b; }
int mul(int a, int b){ return a * b; }
start {
    int tests;
    scanf("%d\n", &tests);
    where_am_i;
    where_am_i;

    where_am_i;
    FOR(tests) begin
        int a, b;
        scanf("%d%d", &a, &b);
        printf("first result is %d\n", execute(m,u,l, a, b));
        printf("second result is %d\n", execute(m,n,s, a, b));
        printf("third result is %d\n", execute(s,u,m, a, b));
        printf("fourth result is %d\n", execute2(*, execute2(+, a, b), execute2(-, a, b)));
    end
    where_am_i;
    return 0;
end