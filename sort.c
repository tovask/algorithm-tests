#include <stdio.h>
#include <stdlib.h>
#define S 500000
/*int main()
{
    int i,j,k,a,b,c,s,*t;
    FILE*f;
    t=calloc(S,sizeof(int));
    for(i=0;i<S;){
        a=rand();
        rand();
        b=rand();
        c=(b<<15)+a;
        for(j=0;j<i;j++)if(c==t[j])break;
        if(j==i)t[++i]=c;
    }
    f=fopen("unsorted.dat","wb");
    fwrite(t,sizeof(int),S,f);
    fclose(f);
 	for (i=S-1;i>0;i=k)
	   for (j=0,k=-1;j<i;j++)
	      if (t[j]>t[j+1]){
	         c=t[j+1];
	         t[j+1]=t[j];
	         t[k=j]=c;
	         }
    f=fopen("sorted.dat","wb");
    fwrite(t,sizeof(int),S,f);
    fclose(f);
    j=S/2;
    k=S-1;
    for(i=0;i<j;i++){
        c=t[i];
        t[i]=t[k-i];
        t[k-i]=c;

    }
    f=fopen("reverse.dat","wb");
    fwrite(t,sizeof(int),S,f);
    fclose(f);
    return 0;
}
*/
/*int main()
{
    int i,j,*t;
    FILE*f;
    t=calloc(S,sizeof(int));
    f=fopen("sorted.dat","rb");
    fread(t,sizeof(int),S,f);
    fclose(f);
    j=s-1;
    for(i=0;i<j;i++)if(t[i]>=t[i+1])break;
    if(i==j)printf("Fel rendben!\n");else printf("HIBA\n");
    f=fopen("reverse.dat","rb");
    fread(t,sizeof(int),S,f);
    fclose(f);
    j=S-1;
    for(i=0;i<j;i++)if(t[i]<=t[i+1])break;
    if(i==j)printf("Le rendben!\n");else printf("HIBA\n");
    printf("Hello world!\n");
    return 0;
}
*/

int cmp(int*i,int*j,int m){
    static int c=0;
    switch(m){
        case 0: c++;return *i-*j;
        case 1: c=0;
    }
    return c;
}

double cmp_(int*i,double j,int m){
    static int c=0;
    switch(m){
        case 0: c++;return *i-j;
        case 1: c=0;
    }
    return c;
}

int xcg(int*i,int*j,int m){
    static int c=0; int k;
    switch(m){
        case 0: c++;k=*i;*i=*j;*j=k;return 0;
        case 1: c=0;
    }
    return c;
}

void bouble(int*a,int n){
    int i,j;
 	for (i=n-1;i;i--)for (j=0;j<i;j++)
        if (cmp(a+j,a+j+1,0)>0)xcg(a+j,a+j+1,0);
}

void smart(int*a,int n){
    int i,j,k;
 	for (i=n-1;i>0;i=k)for (j=0,k=-1;j<i;j++)
        if (cmp(a+j,a+j+1,0)>0){k=j;xcg(a+j,a+j+1,0);}
}

void shell(int*a,int n){
    int i,j,k,l,m;
    for (m=1;2*m<n;m<<=1);
    for (m-=1;m;m>>=1)
        for (l=0;l<m;l++)
            for (i=n-1-(n-1-l)%m;i>l;i=k)
                for (j=l,k=-m;j<i;j+=m)
                    if (cmp(a+j,a+j+m,0)>0){
                        k=j;xcg(a+j,a+j+m,0);
                    }
}

void sink(int*a,int n,int x){
    int j,k,m;
	for(j=x,k=1;k;)
		if(2*j>n)k=0;
		else {
			if(2*j==n){
                if (cmp(a+j,a+n,0)<0)xcg(a+j,a+n,0);
				k=0;
			}
			else {
				m=cmp(a+2*j,a+2*j+1,0)>0?2*j:2*j+1;
                if (cmp(a+j,a+m,0)<0){
                    xcg(a+j,a+m,0);
					j=m;
				}
				else k=0;
			}
		}
}

void heap(int*a,int n){
    int i,*b;
    b=a-1;
    for(i=n/2;i;i--)sink(b,n,i);
	for(i=n;i>1;){
	    xcg(b+1,b+i,0);
	    sink(b,--i,1);
	}
}

void quick(int*a,int*b){
    if(a!=b){
        int*c=a,*d=b;
        double k=((double)*a+*b)/2;
        do{
            while(cmp_(c,k,0)<0)c++;
            while(cmp_(d,k,0)>0)d--;
            if(c<d)xcg(c++,d--,0);
        } while(c<d);
        quick(a,d);
        quick(c,b);
    }
}

int main()
{
    int p,q,qq,qqq,i,j,*t,*w;
    //FILE*f;
    //char* g[3];
    //g[0]="unsorted.dat";
    //g[1]="sorted.dat";
    //g[2]="reverse.dat";
    t=calloc(S,sizeof(int));
    w=calloc(S,sizeof(int));
    for(p=0;p<3;p++){
        //printf("\n%s\n",g[p]);
        //f=fopen(g[p],"rb");
        //fread(t,sizeof(int),S,f);
        //fclose(f);
        for(q=0;q<S;q++)t[q] = rand() % 3;
        for(q=50;q<50001;q*=10)
        for((qqq=p?1:10),qq=0;qq<qqq;qq++){
            for(i=0;i<q;i++)w[i]=t[i+qq*q];
            cmp(0,0,1);
            xcg(0,0,1);
            bouble(w,q);
            i=cmp(0,0,2);
            j=xcg(0,0,2);
            printf("Bouble Sort  %8d(%1d)   cmp: %10d   xchg: %10d\n",q,qq,i,j);
            for(i=0;i<q;i++)w[i]=t[i+qq*q];
            cmp(0,0,1);
            xcg(0,0,1);
            smart(w,q);
            i=cmp(0,0,2);
            j=xcg(0,0,2);
            printf("Smart Bouble %8d(%1d)   cmp: %10d   xchg: %10d\n",q,qq,i,j);
            for(i=0;i<q;i++)w[i]=t[i+qq*q];
            cmp(0,0,1);
            xcg(0,0,1);
            shell(w,q);
            i=cmp(0,0,2);
            j=xcg(0,0,2);
            printf("Shell Sort   %8d(%1d)   cmp: %10d   xchg: %10d\n",q,qq,i,j);
            for(i=0;i<q;i++)w[i]=t[i+qq*q];
            cmp(0,0,1);
            xcg(0,0,1);
            heap(w,q);
            i=cmp(0,0,2);
            j=xcg(0,0,2);
            printf("Heap Sort    %8d(%1d)   cmp: %10d   xchg: %10d\n",q,qq,i,j);
            for(i=0;i<q;i++)w[i]=t[i+qq*q];
            cmp_(0,0,1);
            xcg(0,0,1);
            quick(w,w+q-1);
            i=cmp_(0,0,2);
            j=xcg(0,0,2);
            printf("Quick Sort   %8d(%1d)   cmp: %10d   xchg: %10d\n",q,qq,i,j);
        }
        break;
    }
    printf("\nEnd of test\n");
    return 0;
}

