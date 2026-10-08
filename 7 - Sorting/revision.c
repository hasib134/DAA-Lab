#include<stdio.h>
#include<stdlib.h>

void shellSort(int arr[],int n){
    //starting with the large gap 
    for(int gap = n/2; gap>0 ;gap/=2){
        //perform insertion sort in the gap 
        for(int i = gap;i<n;i++){
            int key = arr[i];
            int j=i;
            while(j>=gap && arr[j-gap]>key){
                arr[j] = arr[j-gap];
                j = j-gap;
            }
            arr[j] = key;

        }
    }
}

struct bucket{
    float * data;
    int size;
    int capcity;
};

void initializeBucket(struct bucket *b){
    b->size = 0;
    b->capcity = 4;
    b->data = (float*)malloc(b->capcity * sizeof(float));
}
void push_bucket(struct bucket* b,float val){
    if(b->size == b->capcity){
        b->capcity*=2;
        float * temp = (float*)realloc(b->data,b->capcity*sizeof(float));
        b->data = temp;
    }
    
    b->data[b->size] = val;
    b->size ++;
}

void freeBucket(struct bucket*b){
    free(b->data);
    free(b);
}

//insertion sort on buckets
void insertionSort(float arr[],int n){
    for(int i=1;i<n;i++){
        float key = arr[i];
        int j = i-1;
        
        while(j>=0 && arr[j]>key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void bucketSort(float arr[],int n){
    struct bucket * item = (struct bucket*)malloc(n * sizeof(struct bucket));

    //insitialize the buckets 
    for(int i=0;i<n;i++){
        initializeBucket(&item[i]);
    }

    //distribute elements in the bucket
    for(int i=0;i<n;i++){
        int index = n*arr[i];
        if(index>=n){
            index = n-1;
        }
        push_bucket(&item[index],arr[i]);
    }

    //sort all the bucket 
    for(int i=0;i<n;i++){
        insertionSort(item[i].data,item[i].size);
    }

    //gather all elements sorted elements from the buckets and store it 
    int k=0;
    for(int i = 0;i<n;i++){
        for(int j=0;j<item[i].size;j++){
            arr[k] = item[i].data[j];
            k++;
        }
    }
}

int main(){
    int arr []= {7,3,9,2,0,1,5,8};
    // int n = sizeof(arr)/sizeof(arr[0]);

    
    // shellSort(arr,n);
    // for(int i=0;i<n;i++){
    //     printf("%d ",arr[i]);
    // }

    float brr[]={0.78f, 0.17f, 0.39f, 0.26f, 0.72f, 0.94f, 0.21f, 0.12f, 0.23f, 0.68f};
    int n = sizeof(brr)/sizeof(brr[0]);

    bucketSort(brr,n);
    for(int i=0;i<n;i++){
        printf("%f ",brr[i]);
    }
}