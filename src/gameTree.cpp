#include<iostream>
#include <vector>
using namespace std;

enum player{Min,Max};
//enum color{red,blue,yellow,green,orange,white,pink};

static int board_Size;

class action{
public:
	 int x,y,x1,y1;
	 action(){

	 }
	 action(int i,int j,int k,int l){
		x=i;y=j;x1=k;y1=l;
	}
};
class action2{
public:
	int x,y;
	int color;
	double probability;
	action2(){

	}
	action2(int i,int j,int  col,double p){
		x=i;
		y=j;
		color=col;
		probability=p;
	}
};

class state{
public:
	int **board;
	int depth;
	double probability;
	int stateScore;
	int *parentState;
	state(){
		depth=0;
		probability=1;
		board=new int*[board_Size];
		for(int i=0;i<board_Size;i++){
			board[i]=new int[board_Size];
			for(int j=0;j<board_Size;j++){
				board[i][j]=-1;
			}
		}
	}
	state(state* s){
		board=new int*[board_Size];
		for(int i=0;i<board_Size;i++){
			board[i]=new int[board_Size];
			for(int j=0;j<board_Size;j++){
				board[i][j]=s->board[i][j];
			}
		}
		probability=s->probability;
		depth=s->depth;
	}
	~state(){
		for(int i=0;i<board_Size;i++){
			delete[] board[i];
		}
		delete[] board;
	}
	// state* result(state* s, action a){
	// 	state* s1=new state(s);
	// 	int temp=s1->board[a.x][a.y];
	// 	s1->board[a.x][a.y]=-1;
	// 	s1->board[a.x1][a.y1]=temp;
	// 	s1->depth=s->depth+1;
	// 	return s1;
	// }
	// state* result2(state*s, action2 a){
	// 	state* s1=new state(s);
	// 	s1->board[a.x][a.y]=a.color;
	// 	s1->depth=s->depth+1;
	// 	s1->probability*=a.probability;
	// 	return s1;
	// }
	int utility(){
		numPalindrome();
		return this->stateScore;
	}
	
	vector<action> orderActions(){
		vector<action> actions;
		action a(0,0,0,0);
		actions.push_back(a);

		for(int i=0;i<board_Size;i++){
			for(int j=0;j<board_Size;j++){
				if(board[i][j]!=-1){
					vector<action> right,left,up,down;
					right=moveRight(i,j);
					left=moveLeft(i,j);
					up=moveUp(i,j);
					down=moveDown(i,j);

					actions.insert(actions.end(),right.begin(),right.end());
					actions.insert(actions.end(),left.begin(),left.end());
					actions.insert(actions.end(),up.begin(),up.end());
					actions.insert(actions.end(),down.begin(),down.end());
				}
			}
		}
		return actions;
	}
	
	

	vector<action> moveRight(int i,int j){
		int k=i+1;
		vector<action> actions;
		while(k<board_Size){
			if(board[k][j]==-1){
				action a(i,j,k,j);
				actions.push_back(a);
				k++;
			}
			else{
				break;
			}

		}
		return actions;
	}
	vector<action> moveLeft(int i,int j){
		int k=i-1;
		vector<action> actions;
		while(k>=0){
			if(board[k][j]==-1){
				action a(i,j,k,j);
				actions.push_back(a);
				k--;
			}
			else{
				break;
			}
		}
		return actions;

	}
	vector<action> moveUp(int i,int j){
		int k=j+1;
		vector<action> actions;
		while(k<board_Size){
			if(board[i][k]==-1){
				action a(i,j,i,k);
				actions.push_back(a);
				k++;
			}
			else{
				break;
			}
		}
		return actions;

	}
	vector<action> moveDown(int i,int j){
		int k=j-1;
		vector<action> actions;
		while(k>=0){
			if(board[i][k]==-1){
				action a(i,j,i,k);
				actions.push_back(a);
				k--;
			}
			else{
				break;
			}
		}
		return actions;
	}

	/*
	int palindromicScore(){
		int score=0;
		for(int row=0;row<board_Size;row++){
			bool b=false;
			int first,second;
			for(int i=0;i<board_Size;i++){
				if(board[row][i]!=-1){
					if(!b){
						first=i;
						second=i;
						b=true;
					}
					else{
						second=i;
					}
				}
				else{
					if(b){
						score+=sumPalindrome(row,first,row,second);
						b=false;
					}
				}
			}
			if(b){
				score+=sumPalindrome(row,first,row,second);
			}
		}


		for(int column=0;column<board_Size;column++){
			bool b=false;
			int first,second;
			for(int i=0;i<board_Size;i++){
				if(board[i][column]!=-1){
					if(!b){
						first=i;
						second=i;
						b=true;
					}
					else{
						second=i;
					}
				}
				else{
					if(b){
						score+=sumPalindrome(first,column,second,column);
						b=false;
					}
				}
			}
			if(b){
				score+=sumPalindrome(first,column,second,column);
			}
		}
		return score;
	}
	int sumPalindrome(int i,int j, int k, int l){
		int score=0;
		if(i==k){
			int count =2;
			int size=l-j+1;
			while(count<=size){
				int j1=j;
				while(j1+count-1<=l){
					if(isPalindrome(i,j1,k,(j1+count-1))){
						score+=count;
					}
					j1++;
				}
				count++;
			}
		}
		else if(j==l){
			int count =2;
			int size=k-i+1;
			while(count<=size){
				int i1=i;
				while(i1+count-1<=k){
					if(isPalindrome(i1,j,(i1+count-1),l)){
						score+=count;
					}
					i1++;
				}
				count++;
			}
		}
		return score;
	}

	bool isPalindrome(int i,int j, int k, int l){
		if(i>=k && j>=l){
			return true;
		}
		else if(i==k){
			// assume j<=l
			if(board[i][j]==board[k][l]){
				return isPalindrome(i,j+1,k,l-1);
			}
			else{
				return false;
			}
		}
		else if(j==l){
			//assume i<=k
			if(board[i][j]==board[k][l]){
				return isPalindrome(i+1,j,k-1,l);
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	}
	*/

	void numPalindrome(){
		int score = 0;
		int palindromeLength = 0;
		for (int row = 0; row < board_Size; row++){
			for (int col = 0; col < board_Size; col++){
				palindromeLength = 2;
				int indexLeft = col;
				int indexRight = col+1;
				while ((indexLeft >= 0) && (indexRight <= board_Size-1)){
					if (board[row][indexRight] != -1){
						if (board[row][indexLeft] == board[row][indexRight]){
							score += palindromeLength;
							// cout<<"row "<<row<<" indexLeft "<<indexLeft<<" indexRight "<<indexRight<<" length "<<palindromeLength<<endl;
						}
						palindromeLength++;
						indexLeft--;
						if (indexLeft >= 0){
							if (board[row][indexLeft] == board[row][indexRight]){
								score += palindromeLength;
								// cout<<"row "<<row<<" indexLeft "<<indexLeft<<" indexRight "<<indexRight<<" length "<<palindromeLength<<endl;
							}
						}
						palindromeLength++;
						indexRight++;
					}
					else{
						indexLeft--;
						indexRight++;
						palindromeLength += 2;
					}
				}

				palindromeLength = 2;
				int indexTop = row;
				int indexBot = row+1;
				while ((indexTop >= 0) && (indexBot <= board_Size-1)){
					if (board[indexBot][col] != -1){
						if (board[indexTop][col] == board[indexBot][col]){
							score += palindromeLength;
							// cout<<"indexTop "<<indexTop<<" indexBot "<<indexBot<<" col "<<col<<" length "<<palindromeLength<<endl;
						}
						palindromeLength++;
						indexTop--;
						if (indexTop >= 0){
							if (board[indexTop][col] == board[indexBot][col]){
								score += palindromeLength;
								// cout<<"indexTop "<<indexTop<<" indexBot "<<indexBot<<" col "<<col<<" length "<<palindromeLength<<endl;
							}
						}
						palindromeLength++;
						indexBot++;
					}
					else{
						palindromeLength += 2;
						indexTop--;
						indexBot++;
					}
				}
				// cout<<"score = "<<score<<endl;
			}
		}
		this->stateScore = score;
		//return this->stateScore;
	}

	void printvector(vector<action> v){
		int l=v.size();
		for(int i=0;i<l;i++){
			action a=v.at(i);
			cout<<"("<<a.x<<","<<a.y<<"),("<<a.x1<<","<<a.y1<<")"<<endl;
		}
		cout<<"new vector"<<endl;
	}
	void printboard()
	{
		for(int i=0;i<board_Size;i++){
			for(int j=0;j<board_Size;j++){
				cout<<board[i][j]<<" | ";
			}
			cout<<endl;
		}
		cout<<endl<<endl;
	}

};

 
