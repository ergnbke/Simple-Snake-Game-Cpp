#include<iostream>
#include<windows.h>
#include<cstdlib>
#include<ctime>
#include<conio.h>
using namespace std;

bool gamestatus;
const int genislik=50;
const int uzunluk=20;
int x,y,Fx,Fy;
enum eDir{DUR=0,SOL,SAG,UP,DOWN};
eDir dir;
int score;
int tailX[genislik*uzunluk];
int tailY[genislik*uzunluk];
void setbait(){
	bool ontail=false;
	bool onhead=true;
	while(ontail || onhead){
		Fx=1+rand()%(genislik-2);
		Fy=1+rand()%(uzunluk-2);
		ontail=false;
		if(!(x==Fx && y==Fy))
			onhead=false;
		for(int i=0;i<score;i++){
			if(Fx==tailX[i] && Fy==tailY[i])
				ontail=true;
		}
	}
		
}
void setup(){
	gamestatus=true;
	dir=DUR;
	x=genislik/2;
	y=uzunluk/2;
	score=0;
	do{
		Fx=1+rand()%(genislik-2);
		Fy=1+rand()%(uzunluk-2);
	}while(x==Fx && y==Fy);	
}
void draw(){
	
	char ekranM[uzunluk][genislik];
	for(int j=0;j<uzunluk;j++){
		for(int i=0;i<genislik;i++){	
			if(i==0 || i==genislik-1 || j==0 || j==uzunluk-1)
				ekranM[j][i]='#';
			else if(i==x && j==y)
				ekranM[j][i]='@';
			else if(i==Fx && j==Fy)
				ekranM[j][i]='+';
			else
				ekranM[j][i]=' ';	
			for(int ii=0;ii<score;ii++){
				if(tailX[ii]==i && tailY[ii]==j)
					ekranM[j][i]='o';
			}	
		}
	}
	char ekran[uzunluk*genislik+(uzunluk-1)];
	int a=0;
	for(int j=0;j<uzunluk;j++){
		for(int i=0;i<genislik;i++){
			ekran[a]=ekranM[j][i];	
			a++;
		}
		ekran[a]='\n';
		a++;
	}
	string strekran=ekran;
	system("cls");
	cout<<strekran<<endl<<">LEFT:	a , f	>RIGHT:	d , t"<<endl<<">UP:	w , t	>DOWN:	s , f"<<endl<<endl<<"	Score: "<<score;
}
void input(){
	if(_kbhit()){
		switch(_getch()){
			case 'a':
				if(dir!=SAG)
					dir=SOL;
				break;
			case 'd':
				if(dir!=SOL)
					dir=SAG;
				break;
			case 'w':
				if(dir!=DOWN)
					dir=UP;
				break;
			case 's':
				if(dir!=UP)
					dir=DOWN;
				break;
			case 'x':
				gamestatus=false;
				break;
			case 'f':
				if(dir==DOWN || dir==UP)
					dir=SOL;
				else if(dir==SOL || dir==SAG)
					dir=DOWN;
				break;
			case 't':
				if(dir==UP || dir==DOWN)
					dir=SAG;
				else if(dir==SAG || dir==SOL)
					dir=UP;
				break;
		}
	}
}
void logic(){
	int tempX=x;
	int tempY=y;
	switch(dir){
		case SAG:
			x++;
			if(x>=genislik-1)
				x=1;
			break;
		case SOL:
			x--;
			if(x<=0)
				x=genislik-2;
			break;
		case UP:
			y--;
			if(y==0)
				y=uzunluk-2;
			break;
		case DOWN:
			y++;
			if(y==uzunluk-1)
				y=1;
			break;
	}
	if (x==Fx && y==Fy){
		score++;
		setbait();
	}
	if(score>0){
			for(int i=score-1;i>=0;i--){			
				tailX[i+1]=tailX[i];
				tailY[i+1]=tailY[i];		
			}
			tailX[0]=tempX;
			tailY[0]=tempY;			
	}
	for(int i=0;i<score;i++){
		if(x==tailX[i] && y==tailY[i])
			gamestatus=false;
	}		
}
endofgame(){
	cout<<endl<<endl<<"		GAME OVER"<<endl;
	_getch();
}
int main(){
	srand(time(NULL));
	setup();
	while(gamestatus){		
		draw();
		input();
		logic();
		Sleep(100);
	}
	endofgame();	
	return 0;
}
