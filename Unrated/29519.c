#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int pos = 0;  
    
    while (pos < n - 1) {
        pos=pos+pos+1;
        if(pos>=n||a[pos]==0){
            printf("No\n");
            return 0;
        }
    }
    
    printf("Yes\n");
    
    return 0;
}
