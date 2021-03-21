#include <iostream>
#include <string>
#include <fstream>
#include <malloc/malloc.h>

using namespace std;

int* reservation(int &movieNum, string &movie1, string &movie2, string &movie3,int &row1,int &row2,int &row3,int &col1,int &col2,int &col3){
    cout<<"==========영화 예매=========="<<endl;
    ifstream fin("/Users/parksungsoo/konkuk/2-1/objectProgramming/3_worksheet/cpp/movie.txt");
    fin>>movieNum;
    fin>>movie1;
    fin>>row1>>col1;
    fin>>movie2;
    fin>>row2>>col2;
    fin>>movie3;
    fin>>row3>>col3;
}

void showMovieList(string &movie,int &row, int& col, int&reserveNum, int num){
    if(reserveNum>0) {
        cout << num << ") " << movie << "\t" << reserveNum << "/" << row * col << endl;
    }else{
        cout << num << ") " << movie << "\t" << "매진" << "/" << row * col << endl;
    }
}

int** loadMap(int& row, int& col){ //함수에서부터 받아와야하기 떄문에 레퍼런스타입
    int** movie = new int*[row];
    for(int i=0;i<row;i++){
        movie[i] = new int[col];
    }
    return movie;
}

void showMovieMap(int** &movie,const int row, const int col){
    for(int i=0;i<col;i++){
        cout<<"\t"<<i+1;
    }
    cout<<"\n\n";
    for(int i=0;i<row;i++){
        cout<<static_cast<char>('A'+i)<<"\t";
        for(int j=0;j<col;j++){
            cout<<(movie[i][j]? "X" : "O")<<"\t";
        }
        cout<<"\n\n";
    }

}

int** realReserve(int** &movie,const int row, const int col, int &reserveNum){
    cout<<"좌석 입력( ex==> A1 ) : ";
    char x,y;
    cin>>x>>y;
    if(movie[x-'A'][y-'1']){
        cout<<"이미 예약된 자리입니다.\n";
    }
    else if(x<'A' || x>=static_cast<char>('A'+row)){
        cout<<"잘못된 정보를 기입하셨습니다."<<endl;
    }
    else if(y<'1' || y>=static_cast<char>('1'+col)){
        cout<<"잘못된 정보를 기입하셨습니다."<<endl;
    }
    else{
        movie[x-'A'][y-'1'] = true;
        int *ran = &movie[x][y];
        cout<<"자리예약이 되었습니다.\n";
        reserveNum -= 1;
        cout<<"예약번호는 : "<<ran<<endl;


    }
    return movie;
}

void initArray(int** (&arr)){
    size_t row = malloc_size(arr) / sizeof(arr[0]);
    size_t col = malloc_size(arr[0]) / sizeof(arr[0][0]);
    int num = 0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            arr[i][j] = num++;
        }
    }

    for(int i=0;i<100;i++){
        int r1 = rand()%row;
        int c1 = rand()%col;
        int r2 = rand()%row;
        int c2 = rand()%col;
        if(r1 != r2 || c1!=c2){
            int temp = arr[r1][c1];
            arr[r1][c1] = arr[r2][c2];
            arr[r2][c2] = temp;
        }else
            i--;
    }
}

void cancel(){
    cout<<"201811255 박성수 "<<endl;
    cout<<"안녕 from cancel"<<endl;

}

void recheck(){
    cout<<"201811255 박성수 "<<endl;
    cout<<"안녕 from recheck"<<endl;

}

void finish(int** &movie,const int row, const int col){
    for(int i=0;i<row;i++){
        delete[] movie[i];
    }
    delete[] movie;
}




int main(){
    bool option = true;
    int menuPick, movieNum, movieSelect;
    string movie1, movie2, movie3;
    int row1,row2,row3,col1,col2,col3,reserveNum1,reserveNum2,reserveNum3;

    int* map = reservation(movieNum, movie1,movie2,movie3,row1,row2,row3,col1,col2,col3);
    int** movieArray1 = loadMap(row1, col1);
    int** movieArray2 = loadMap(row2, col2);
    int** movieArray3 = loadMap(row3, col3);


    reserveNum1 = col1*row1;
    reserveNum2 = col2*row2;
    reserveNum3 = col3*row3;

    cout<<"201811255 박성수 "<<endl;
    while(option){
        cout<<"==========홍길동 시네마=========="<<endl;
        cout<<"1)영화 예매 2)예매 취소 3)예매 확인 4)종료"<<endl;
        cout<<"메뉴를 선택하세요 : ";
        cin>>menuPick;
        if(menuPick==1){
            showMovieList(movie1,row1,col1, reserveNum1,1);
            showMovieList(movie2,row2,col2, reserveNum2,2);
            showMovieList(movie3,row3,col3, reserveNum3,3);
            cout<<"예매할 영화를 선택하시요 : ";
            cin>> movieSelect;
            if(movieSelect == 1){
                showMovieMap(movieArray1, row1, col1);
                movieArray1 = realReserve(movieArray1, row1, col1, reserveNum1);
            }else if(movieSelect == 2){
                showMovieMap(movieArray2, row2, col2);
                movieArray2 = realReserve(movieArray2, row2, col2, reserveNum2);
            }else if(movieSelect ==3){
                showMovieMap(movieArray3, row3, col3);
                movieArray3 = realReserve(movieArray3, row3, col3, reserveNum3);
            }
        }else if(menuPick==2){
            cancel();
        }else if(menuPick==3){
            recheck();
        }else if(menuPick==4){
            cout<<"201811255 박성수 "<<endl;
            finish(movieArray1, row1,col1);
            finish(movieArray2, row2,col2);
            finish(movieArray3, row3,col3);
            cout<<"프로그램을 종료합니다.";
            option = false;
        }
    }


    return 0;
}