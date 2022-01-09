#include <iostream>
using namespace std;
#define status int
#define MAX_SIZE 30
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void PT(int *a, int n)
{
    for (int i = 1; i < n + 1; i++)
        cout << a[i] << " ";
}
//希尔排序
void ShellSort_Up(int *arr, int length)
{
    int increase = length;
    int i, j, k, temp;
    do
    {
        increase = increase / 3 + 1; 
        for (i = 0; i < increase; i++)
        {
            for (j = i + increase; j < length; j += increase)
            {
                temp = arr[j]; //待插入元素
                for (k = j - increase; k >= 0 && temp < arr[k]; k -= increase)
                    arr[k + increase] = arr[k];
                arr[k + increase] = temp;
            }
        }
    } while (increase > 1);
}
//快速排序
void quickSort(int array[], int low, int high)
{
    int i = low;
    int j = high;
    if (low < high)
    {
        int temp = array[low];
        while (i < j)
        {
            while (i < j && array[j] >= temp)
                j--;
            if (i < j)
            {
                array[i] = array[j];
                i++;
            }
            while (i < j && array[i] < temp)
                i++;
            if (i < j)
            {
                array[j] = array[i];
                j--;
            }
        }
        array[i] = temp;
        quickSort(array, low, i - 1);
        quickSort(array, i + 1, high);
    }
}
//堆排序
void QuickSort(int *arr, int begin, int end)
{
    if (begin >= end)
        return;
    int left = begin;
    int right = end;
    int keyi = begin;
    while (begin < end)
    {
        while (arr[end] >= arr[keyi] && begin < end) //右边选小
            --end;
        while (arr[begin] <= arr[keyi] && begin < end) //左边选大
            ++begin;
        swap(&arr[begin], &arr[end]);//交换
    }
    swap(&arr[keyi], &arr[end]);
    keyi = end;
    QuickSort(arr, left, keyi - 1);
    QuickSort(arr, keyi + 1, right);
}

//归并排序
void merge(int array[], int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int *L1 = new int[n1];
    int *L2 = new int[n2];
    for (int i = 0; i < n1; i++)
        L1[i] = array[low + i]; 
    for (int j = 0; j < n2; j++)
        L2[j] = array[mid + 1 + j];
    int i = 0;
    int j = 0;
    int k = low;
    while (i < n1 && j < n2)
    {
        if (L1[i] <= L2[j])
            array[k++] = L1[i++];
        else
            array[k++] = L2[j++];
    }
    while (i < n1)
        array[k++] = L1[i++];
    while (j < n2)
        array[k++] = L2[j++];
}
void mergeSort(int array[], int low, int high) //归并排序主函数
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(array, low, mid);      //左
        mergeSort(array, mid + 1, high); //右
        merge(array, low, mid, high);    //合并
    }
}
int main()
{
    int A[30] = {};
    int L=5;
    int n;
    cout << "请输入数据个数n=";
    cin >> n;
    cout << "请依次输入这n个整数:" << endl;
    int tmp = 0;
    while (tmp < n)
    {
        int x;
        scanf("%d", &x);
        A[tmp] = x;
        tmp++;
    }
    int B[MAX_SIZE]; //创建一个新的数组来备份A数组的值
    for (int i = 0; i < n + 1; i++)
        B[i] = A[i];
    do
    {
        cout << "请选择要进行的排序:" << endl;
        cout << "1.希尔排序" << endl;
        cout << "2.快速排序" << endl;
        cout << "3.堆排序" << endl;
        cout << "4.归并排序" << endl;
        cout << "0.退出" << endl;
        cout << endl;
        cin >> L;
        switch (L)
        {
        case 1:
            ShellSort_Up(B, n);
            cout << "希尔排序输出:" << endl;
            for (int i = 0; i < n; i++)
                cout << B[i] << " ";
            cout << endl;
            cout << endl;
            break;
        case 2:
            quickSort(B, 0, n);
            cout << "快速排序输出:" << endl;
            PT(B, n);
            cout << endl;
            cout << endl;
            break;
        case 3:
            QuickSort(B, 0, n);
            cout << "堆排序输出:" << endl;
            PT(B, n);
            cout << endl;
            cout << endl;
            break;
        case 4:
            mergeSort(B, 0, n);
            cout << "归并排序输出:" << endl;
            PT(B, n);
            cout << endl;
            cout << endl;
            break;
        case 0:
            break;
        default:
            break;
        }
    } while (L != 0);  
    system("pause");
    return 0;
}