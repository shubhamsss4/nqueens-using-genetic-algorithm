#include<iostream>
#include<stdlib.h>


using namespace std;


int size=8;



int getrandom()
{
    return rand() % size;
}

int factorial(int n)
{
    int fact=1;

	while(n>=1)
	{
		fact=fact*n;
		n--;
	}
	return fact;
}

int total(int t)
{
    return (factorial(t))/(factorial(t-2)*2);
}

int evaluate(int current[])
{
    int count=0;
    for(int i=0;i<size;i++)
    {
        for(int j=i+1;j<size;j++)
        {
            if((current[i]!=current[j])&&(abs(current[i]-current[j])!=j-i))
            {
                count++;
            }
        }
    }
    return count;
}

int main()
{
    int n;
    int c=-1;
    cout<<"Enter the size of the n*n board\n";
    cin>>size;
    if(size<=0)
    {
        cout<<"Invalid Size Entered\n";
    }

    cout<<"\nEnter number of Readings : ";
    cin>>n;
    if(n<=0)
    {
        cout<<"Valid number not entered.Better luck next time\n";
        return 0;
    }
    int readings[n][size];
    int evalres[n];
    int threshold=total(size);

    /*Getting Initial Population*/
    for(int i=0;i<n;i++)
    {
        cout<<"\nEnter the "<<i<<"th reading :\n";
        for(int j=0;j<size;j++)
        {
            cout<<"\nEnter position "<<j+1<<" : ";
            cin>>readings[i][j];    
            if((readings[i][j])<=0 || (readings[i][j])>(size))
            {
                cout<<"You entered an invalid number\n";
                j--;
            }
        }
    }
    /*end of Initial Population*/

repeat:
    if(c>1000000)
    {
        cout<<"1 Lakh iterations reached\n";
        return 0;
    }
    c++;
    /*Fitness Evaluation*/
    for(int i=0;i<n;i++)
    {
        int temp[size];
        for(int j=0;j<size;j++)
        {
            temp[j]=readings[i][j];
        }
        evalres[i]=evaluate(temp);
    }

    int solpoint=size;
    cout<<"\nThe values generated are :\n";
    for(int i=0;i<n;i++)
    {
        cout<<"\n"<<i+1<<" : "<<evalres[i];
        if(evalres[i]==threshold)
        {
            solpoint=i;
        }
    }
    if(solpoint!=size)
    {
        cout<<"\n\nSolution found\n";
        for(int j=0;j<size;j++)
        {
            cout<<readings[solpoint][j]<<"\t";
        }
        cout<<"\n\n\nSolution : \n";
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
                if(readings[solpoint][j]-1==i)
                {
                    cout<<"Q ";
                }
                else
                {
                    cout<<"X ";
                }
            }
            cout<<"\n";
        }

        cout<<"\nNumber of iterations required : "<<c<<endl;
        return 0;
    }

    //Arranging as per fitness
    cout<<"\n\nArranging as per Fitness Function\n";
    for(int i=0;i<n-1;i++)
    {
        int max=i;
        for(int j=i+1;j<n;j++)
        {
            if(evalres[j]>=evalres[max])
            {
                int temp;
                temp=evalres[max];
                evalres[max]=evalres[j];
                evalres[j]=temp;
                max=j;
            }
        }

        for(int j=0;j<size;j++)
        {
            int temp;
            temp=readings[max][j];
            readings[max][j]=readings[i][j];
            readings[i][j]=temp;
        }
    }
    for(int i=0;i<n;i++)
    {
        int temp[size];
        for(int j=0;j<size;j++)
        {
            temp[j]=readings[i][j];
        }
        evalres[i]=evaluate(temp);
    }

    cout<<"\n\nReadings after Arranging as per value of Fitness Function : \n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<size;j++)
        {
            cout<<readings[i][j]<<"\t";
        }
        cout<<"\n";
    }

    cout<<"\nCorresponding Fitness Values : \n";
    for(int i=0;i<n;i++)
    {
        cout<<"\n"<<i+1<<" : "<<evalres[i];
    }

    //return 0;
    /*end of Fitness Evaluation*/

    /*Selection*/
    cout<<"\n\nInput before selection is : \n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<size;j++)
        {
            cout<<readings[i][j]<<"\t";
        }
        cout<<"\n";
    }
    /*end of Selection*/

    /*Crossover*/
    for(int i=0;i<n;i+=2)
    {
        int selpoint=getrandom();
        cout<<"\nPoint for readings "<<i+1<<" and "<<i+2<<" : "<<selpoint+1;
        for(int j=0;j<=selpoint;j++)
        {
            int temp;
            temp=readings[i+1][j];
            readings[i+1][j]=readings[i][j];
            readings[i][j]=temp;
        }
    }

    cout<<"\n\nInput after selection and crossover is : \n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<size;j++)
        {
            cout<<readings[i][j]<<"\t";
        }
        cout<<"\n";
    }

    /*end of Crossover*/


    /*Mutation*/

    for(int i=0;i<n;i++)
    {
        int mutpoint=getrandom();
        readings[i][mutpoint]=getrandom()+1;
    }

    cout<<"\n\nInput after Mutation is : \n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<size;j++)
        {
            cout<<readings[i][j]<<"\t";
        }
        cout<<"\n";
    }
    /*end of Mutation*/

    goto repeat;
    return 0;
}
