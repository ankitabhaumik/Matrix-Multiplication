#include<iostream>
#include<thread>
#include<vector>
#include<chrono>
using namespace std;

void matrixmultiplysinglethreaded(vector<vector<int>> &matx1 , vector<vector<int>> &matx2 ,vector<vector<int>> &res, int r1,int c2, int r2)
{
    //N X M * M X P = N X P
    for(int i=0;i<r1;i++)
    {
        for(int k=0;k<c2;k++)
        {
            for(int j=0;j<r2;j++)
            {
                res[i][k] = res[i][k] + (matx1[i][j] * matx2[j][k]);
            }
        }
    }
 
}

void matrixmultiplymultithreaded(vector<vector<int>> &matx1 , vector<vector<int>> &matx2,vector<vector<int>> res_mul, int startr1, int endr1,int c2, int r2)
{
    //N X M * M X P = N X P
    int r1 = endr1-startr1+1;
    for(int i=startr1;i<endr1;i++)
    {
        for(int k=0;k<c2;k++)
        {
            res_mul[i][k]=0;
            for(int j=0;j<r2;j++)
            {
                res_mul[i][k] = res_mul[i][k] + (matx1[i][j] * matx2[j][k]);
            }
        }
    }
 
}


void getmatrixmultiplymultithreaded(vector<vector<int>> &matx1,vector<vector<int>> &matx2,int row1,int col2, int row2)
{

    //Multithreaded Matrix calculation
    int num_threads = thread::hardware_concurrency(); //Number of concurrent threads supported.
    vector<vector<int>> res_mul(row1, vector<int>(col2,0));
    vector<thread> threads;

    int row_chunk = row1/num_threads;

    for(int i=0;i<num_threads;i++)
    {
        int startrow = i*row_chunk;
        int endrow = (i==row_chunk-1)? row1 :(i+1)*row_chunk ;

        threads.emplace_back(matrixmultiplymultithreaded,matx1,matx2,ref(res_mul),startrow,endrow,col2,row2);
    }

    for(auto& thread : threads)
    {
        thread.join();
    }

}


void main()
{
    int row1,col1,row2,col2;
      
    cout<<"Enter row of matrix1 : ";
    cin>> row1;
    cout<<"Enter col of matrix1 : ";
    cin>> col1;

    cout<<"Enter row of matrix2 : ";
    cin>> row2;
    cout<<"Enter col of matrix2 : ";
    cin>> col2;

    if(col1 != row2)
    {
        cout<<"Invalid matrix "<<endl;
        return;
    }

    vector<vector<int>> matx1(row1, vector<int>(col1));
    vector<vector<int>> matx2(row2, vector<int>(col2));

    cout<<"Enter the elements of matrix one " <<endl;
    for(int i = 0;i<row1;i++)
    {
        for(int j=0;j<col1;j++)
        {
            cin>>matx1[i][j];
        }
    }

    cout<<"Enter the elements of matrix two " <<endl;

    for(int i = 0;i<row2;i++)
    {
        for(int j=0;j<col2;j++)
        {
            cin>>matx2[i][j];
        }
    }

    //Single Threaded Matrix Calculation 
    vector<vector<int>> res(row1, vector<int>(col2,0));

    auto start = chrono :: high_resolution_clock::now();
    thread t1(matrixmultiplysinglethreaded,matx1,matx2,ref(res),row1,col2,row2);
    auto end = chrono :: high_resolution_clock::now();
    chrono::duration<double> time_taken = end -start;
    cout<<"time taken for singlethread : "<<time_taken.count()<<"seconds \n";

    t1.join();


    start = chrono :: high_resolution_clock::now();
    getmatrixmultiplymultithreaded(matx1,matx2,row1,col2,row2);
    end = chrono :: high_resolution_clock::now();
    time_taken = end -start;
    cout<<"time taken for multithread : "<<time_taken.count()<<"seconds \n";
  


}