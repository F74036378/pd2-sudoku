#include"Sudoku.h"
using namespace std;

void Sudoku::GiveQuestion(){
	int i = 0;
	int rquestion[144]={0};
	int question[144] = {0, 1, 0, 0, 0, 0, 0, 6, 4, -1, -1, -1,
	0, 7, 3, 0, 0, 0, 1, 0, 0, -1, -1, -1,
	4, 5, 0, 0, 0, 9, 0, 0, 0, -1, -1, -1,
	0, 0, 0, -1, -1, -1, 0, 4, 0, 0, 0, 0,
	0, 0, 9, -1, -1, -1, 3, 0, 5, 0, 0, 0,
	0, 3, 0, -1, -1, -1, 0, 2, 0, 0, 0, 7,
	-1, -1, -1, 0, 0, 0, 7, 0, 0, 0, 2, 9,
	-1, -1, -1, 0, 0, 4, 0, 0, 0, 1, 0, 0,
	-1, -1, -1, 0, 8, 0, 0, 0, 0, 0, 6, 0,
	5, 0, 0, 0, 6, 0, -1, -1, -1, 8, 1, 0,
	0, 0, 0, 8, 5, 0, -1, -1, -1, 6, 0, 0,
	0, 0, 0, 0, 7, 0, -1, -1, -1, 0, 0, 0,
	};
	srand((unsigned)time(NULL));
	int seed = rand()%6;
	int sign = 0;
	if(seed%5==0){
		for(i = 0;i<144;i++){
			sign = ((11-((i-(i%12))/12))*12)+(i%12);
			rquestion[sign] = question[i];
		}
	}
	if(seed%5==1){
                for(i = 0;i<144;i++){
                        sign = (((i%12)-11)*(-1))+((i/12)*12);
                        rquestion[sign] = question[i];
                }
        }
	if(seed%5==2){
                for(i = 0;i<144;i++){
                        sign = ((i%12)*12)+(i/12);
                        rquestion[sign] = question[i];
                }
        }
	if(seed%5==3){
                for(i = 0;i<144;i++){
			if(question[i]==0 || question[i]==-1){
				rquestion[i] = question[i];
			}
			else{
                        	rquestion[i] = (question[i]-10)*(-1);
			}
                }
        }
	if(seed%5==4){
                for(i = 0;i<144;i++){
                        rquestion[i] = question[i];
                }
        }

	cout<<seed<<endl;
	for(i=0;i<144;i++){
		cout<<rquestion[i]<<" ";
		if(i%12 == 11){
			cout<<endl;
		}
	}		
}

bool Sudoku::isCorrect(int *sudoku, int pos, int val){
        vector<int> array(10, 0) ;
        int head = (pos/12)*12 ;
        for(int i=head ; i<head+12 ; i++){  // parellel
                if(sudoku[i]==0 || sudoku[i]==-1)  continue ;
                if(array[sudoku[i]]==1)    return false ;
                array[sudoku[i]]++ ;
        }
        array.assign(10, 0) ;

        head = pos%12 ;
        for(int i=head ; i<head+144 ; i+=12){  // vertical
                if(sudoku[i]==0 || sudoku[i]==-1)  continue ;
                if(array[sudoku[i]]==1)    return false ;
                array[sudoku[i]]++ ;
        }
        array.assign(10, 0) ;

        head = (pos/36)*36 + ((pos%12)/3)*3 ;
        for(int i=0 ; i<9 ; i++){
                int index = (i/3)*12+(i%3) + head ;
                if(sudoku[index]==0 || sudoku[index]==-1)  continue ;
                if(array[sudoku[index]]==1)    return false ;
                array[sudoku[index]]++ ;
        }
        return true ;
}

void Sudoku::ReadIn(){
	sp1 = 0;
	sp2 = 0;
        for(int i=0 ; i<144 ; i++){
                cin >> sudoku[i] ;
                if(sudoku[i]){   
			canModify[i] = 0 ;
		}
                else{
			sp2++;
			canModify[i] = 1 ;
		}
		if(sudoku[i] == -1){
			sp1++;
		}
        }
}

bool Sudoku::Solve(){
        bool Go = 1 ;
        int theAnswer = 0;
        int theOne = 0;
        int theLast = 0;
        int i;
	if(sp2 == 108){
		cout<<2<<endl;
		return 0;
	}
	if(sp1 != 36){
		cout<<0<<endl;
		return 0;
	}
	
	
	int b;
	int sp3;
        int head;
	for(b = 0;b<144;b++){
		if(sudoku[b]==-1){
        		head = (b/36)*36 + ((b%12)/3)*3 ;
			sp3 = 0;
        		for(int i=0 ; i<9 ; i++){
                		int index = (i/3)*12+(i%3) + head ;
                		if(sudoku[index]==-1)  sp3++ ;
        		}
			if(sp3!=9){
				cout<<0<<endl;
				return 0;
			}
			sp3 = 0;
			int head = (b/12)*12 ;
        		for(int i=head ; i<head+12 ; i++){  // parellel
                		if(sudoku[i]==-1)  sp3++;
        		}
			if(sp3!=3){
				cout<<0<<endl;
				return 0;
			}
			sp3 = 0;
			head = b%12 ;
		        for(int i=head ; i<head+144 ; i+=12){  // vertical
                		if(sudoku[i]==-1){
					sp3++;
				}
        		}
			if(sp3!=3){
				cout<<0<<endl;
				return 0;
			}
		}
	}

        for(i=0;i<144;i++){
                if(canModify[i] == 1){
                        theOne = i;
                        break;
                }
        }
        for(i=0;i<144;i++){
                if(canModify[i]==1){
                        theLast = i;
                }
        }
        vector<int> answer(144,0);
        vector<int> currentNum(144,1);
        int currentPos = 0 ;
       	while(1){
		if(currentNum[currentPos]==10){
			sudoku[currentPos] = 0;
			Go = 0;
			currentNum[currentPos] = 1;
			currentPos--;
			continue;
		}	
                if(currentPos<0 || currentPos>143){
                        break;
                }
                if(theAnswer > 1){
                        cout<<2<<endl;
                        break;
                }
                
                if(Go){
                        if(canModify[currentPos]){
                                sudoku[currentPos] = currentNum[currentPos] ;
                                if(isCorrect(sudoku, currentPos, currentNum[currentPos])){
                                        if(currentPos == theLast){
						if(currentNum[currentPos]<10){
							for(int k=0;k<144;k++){
								answer[k] = sudoku[k];
							}
							Go = 1;
							theAnswer++;
							currentNum[currentPos]++;
							continue;
						}
						else{
							Go = 0;
							currentNum[currentPos] = 1;
							currentPos--;
							continue;
						}
                                        	
                                        }
                                        else{
						if(currentNum[currentPos]<10){
							Go = 1;
							currentNum[currentPos]++;
							currentPos++;
							continue;
						}
						else{
							Go = 0;
							currentNum[currentPos] = 1;
							currentPos--;
							continue;
						}
                                        }
                                }
                                else{
					sudoku[currentPos] = 0;
                                	currentNum[currentPos]++;
					Go = 1;
					continue;
                                }
                        }
                        else{
                                currentPos++;
                                continue;
                        }
                }

                else{
                        if(canModify[currentPos]){
                        sudoku[currentPos] = currentNum[currentPos] ;
                                if(isCorrect(sudoku, currentPos, currentNum[currentPos])){
                                        
                                                if(currentNum[currentPos]<10){
							Go = 1;
							currentNum[currentPos]++;
							currentPos++;
							continue;
						}
						else{
							Go = 0;
							currentNum[currentPos] = 1;
							currentPos--;
							continue;
						}
                                        
                                }
                                else{
                                        currentNum[currentPos]++;
					continue;

                                }

                        }
                        else{
                                currentPos--;
                                continue;
                        }
                }
        }
        if(theAnswer == 1){
		cout<<1<<endl;
                for(i=0;i<144;i++){
                        cout<<answer[i]<<" ";
                        if(i%12 == 11){
                                cout<<endl;
                        }
                }
	}
        else{
		if(theAnswer == 0){
                cout<<0<<endl;
		}
        }
}

