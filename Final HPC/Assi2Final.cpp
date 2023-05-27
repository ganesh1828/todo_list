#include<iostream>
using namespace std;

void bubbleSort(int arr[],int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<(n-1);j++)
		{
			if(arr[j]>arr[j+1])
			{
				swap(arr[j],arr[j+1]);
			}
		}
	}

	for(int i=0;i<n;i++)
	{
		cout<<arr[i]<<" ";
	}

}

void parallelBubbleSort(int arr[],int n)
{
	for(int i=0;i<n;i++)
	{
		#pragma omp parallel for
		for(int j=0;j<(n-1);j++)
		{
			if(arr[j]>arr[j+1])
			{
				swap(arr[j],arr[j+1]);
			}
		}
	}

	for(int i=0;i<n;i++)
	{
		cout<<arr[i]<<" ";
	}

}



void merge(int arr[],int low,int mid,int high)
{
	int i=low;
	int j=mid+1;
	int n=high-low+1;
	int *temp=new int[n];

	int k=0;
	while(i<=mid && j<=high)
	{
		if(arr[i]<arr[j])
		{
			temp[k]=arr[i];
			i++;
		}
		else
		{
			temp[k]=arr[j];
			j++;
		}
		k++;
	}

	while(i<=mid)
	{
		temp[k]=arr[i];
		i++;
		k++;
	}

	while(j<=high)
	{
		temp[k]=arr[j];
		j++;
		k++;
	}

	k=0;
	for(int l=low;l<=high;l++)
	{
		arr[l]=temp[k];
		k++;
	}
}

void mergesort(int arr[],int low,int high)
{
	if(low<high)
	{
		int mid=(low+high)/2;

		mergesort(arr,low,mid);
		mergesort(arr,mid+1,high);

		merge(arr,low,mid,high);
	}
}

void parallelMergeSort(int arr[],int low,int high)
{
	if(low<high)
	{
		int mid=(low+high)/2;
		#pragma omp parallel sections num_threads(2)
		{
			#pragma omp section
			{
				mergesort(arr,low,mid);
			}
			#pragma omp section
			{	
				mergesort(arr,mid+1,high);
			}
		}
		
		merge(arr,low,mid,high);
	}
}

int main()
{
	cout<<"Number of elements\n";
	int n;
	cin>>n;
	int *arr=new int[n];

	for(int i=0;i<n;i++)
	{
		cin>>arr[i];
	}
	cout<<"\n";
	// bubbleSort(arr,n);

	// parallelBubbleSort(arr,n);

	// mergesort(arr,0,n-1);

	parallelMergeSort(arr,0,n-1);

	cout<<"\n";
	for(int i=0;i<n;i++)
	{
		cout<<arr[i]<<" ";
	}
}