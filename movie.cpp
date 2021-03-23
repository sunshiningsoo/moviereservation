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

int** realReserve(int** &movie,const int row, const int col, int &reserveNum, int &reservenumber, char x,char y){

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
        cout<<"자리예약이 되었습니다.\n";
        reserveNum -= 1;
        cout<<"예약 번호는 "<<reservenumber<<endl;
        movie[x-'A'][y-'1'] = reservenumber;
        reservenumber += 1;

    }
    return movie;
}


int** cancel(int** &movie, int &reserveNum, char &x,char &y, int &i, int &row,int &col){
    for(int j=0;j<row;j++) {
        for(int k=0;k<col;k++) {
            if (movie[j][k] == i) {
                movie[j][k] = false;
                cout << "예약 취소가 되었습니다.\n";
                reserveNum += 1;
            }
        }
    }
    return movie;
}
//저장되는 값이 이전 값으로 저장되있

void recheck(string movie1, int ** &movie, int &reserveNumber, char &x,char &y, int &row,int &col){
    cout<<"201811255 박성수 "<<endl;
    cout<<"확인 하려는 예약번호를 알려주세요 : ";
    int i;
    cin>>i;
    for(int j=0;j<row;j++) {
        for(int k=0;k<col;k++) {
            if (movie[j][k] == i) {
                cout<<"예매하신 영화 :"<<movie1<<endl;
                cout<<"예매하신 좌석 : "<<static_cast<char>(static_cast<char>(j)+'A')<<static_cast<char>(static_cast<char>(k)+'1')<<endl;
                for(int a=0;a<col;a++){
                    cout<<"\t"<<a+1;
                }
                cout<<"\n\n";
                for(int l=0;l<row;l++){
                    cout<<static_cast<char>('A'+l)<<"\t";
                    for(int m=0;m<col;m++){
                        if(l == j && m == k){
                            cout<<"!"<<"\t";
                        }else{
                            cout<<"O"<<"\t";
                        }
                    }
                    cout<<"\n\n";
                }
            }else{
                cout<<"예약번호가 존재하지 않습니다."<<endl;
                break;
            }
        }
    }
}

void finish(int** &movie,const int row){
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
    int reserveNumber = 1; // 예약번호 주는거
    char x,y; // 입력인자 받는 거

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
                cout<<"좌석 입력( ex==> A1 ) : ";
                cin>>x>>y;
                movieArray1 = realReserve(movieArray1, row1, col1, reserveNum1, reserveNumber,x,y);
            }else if(movieSelect == 2){
                showMovieMap(movieArray2, row2, col2);
                cout<<"좌석 입력( ex==> A1 ) : ";
                cin>>x>>y;
                movieArray2 = realReserve(movieArray2, row2, col2, reserveNum2,reserveNumber, x,y);
            }else if(movieSelect ==3){
                showMovieMap(movieArray3, row3, col3);
                cout<<"좌석 입력( ex==> A1 ) : ";
                cin>>x>>y;
                movieArray3 = realReserve(movieArray3, row3, col3, reserveNum3, reserveNumber,x,y);
            }
        }else if(menuPick==2){
            cout<<"201811255 박성수 "<<endl;
            cout<<"취소하려는 예약번호를 작성해주세요 : ";
            int i;
            cin>>i;
            cancel(movieArray1,reserveNum1, x,y, i,row1,col1);
            cancel(movieArray2,reserveNum2, x,y, i,row2,col2);
            cancel(movieArray3,reserveNum3, x,y, i,row3,col3);
            //여기 위에 수정해야함
        }else if(menuPick==3){
            recheck(movie1,movieArray1, reserveNumber, x,y,row1,col1);
            recheck(movie2,movieArray2, reserveNumber, x,y,row2,col2);
            recheck(movie3,movieArray3, reserveNumber, x,y,row3,col3);
        }else if(menuPick==4){
            cout<<"201811255 박성수 "<<endl;
            finish(movieArray1, row1);
            finish(movieArray2, row2);
            finish(movieArray3, row3);
            cout<<"프로그램을 종료합니다.";
            option = false;
        }
    }


    return 0;
}