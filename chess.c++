//project by moksh oswal
#include <iostream>
#include <map>
#include <stdlib.h>
using namespace std;
struct node{
    int from[2];
    int to[2];
    char piece;
    struct node *next;
    struct node *prev;
};
void add_nodes(struct node **head,struct node **tail,int from[],int to[],char p){
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    //adding data to node
    newnode->from[0]=from[0];
    newnode->from[1]=from[1];
    newnode->to[0]=to[0];
    newnode->to[1]=to[1];
    newnode->piece=p;
    if(*tail==NULL){
        *head=newnode;
        *tail=newnode;
    }else{
       newnode->prev=*tail;
       newnode->next=NULL;
        (*tail)->next=newnode;
        *tail=newnode;

    }
}
void makeboard(char board[][9]){
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            board[i][j]='-';
            if(j==0 && i<8){
                board[i][j]='a'+i;
            }

            else if(i==8 && j>0){
                board[i][j]= to_string(j)[0];;
            }

            else if(i==8 && j==0){
                board[i][j]=' ';
            }

        }

    }
}

void printboard(char board[][9]){

    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool valid(char board[][9],int from[2],int to[2],int color,map<char,int>& obj){
    char p = board[from[0]][from[1]];
    return (from[0]>=0 && from [0] < 8 && from [1]>=1 && from[1]<9 &&
            to[0]>=0 && to [0] < 8 && to [1]>=1 && to[1]<9 && obj[p]==color);
}
// to check when rook queen or bishop move there are no pieces in between that they are jumping
bool diagonal_check(char board[][9] ,int from[2],int to[2],int x,int y){
    int from_x=from[0],from_y=from[1];
    int to_x=to[0],to_y=to[1];
    int add_x =1,add_y=1;
    if (x<0){
        add_x=-1;
    }
    else if(x==0){
        add_x=0;
    }
    if (y<0){
        add_y=-1;
    }
    else if (y==0){
        add_y=0;
    }

    from_x = from_x+add_x;
    from_y=from_y+add_y;
    // this to check if there is something in between or not

    while(from_x!=to_x || from_y!=to_y){
        if( board[from_x][from_y]!='-'){

            return false;
        }
        from_x = from_x+add_x;
        from_y=from_y+add_y;
    }
    return true;
}
bool bishop_move(char board[][9] ,int from[2],int to[2]) {
    int x = to[0]-from[0];
    int y= to[1]-from[1];
    // this check if the coordinate is movebale or not
    if(abs(x)==abs(y)){
        return diagonal_check(board,from,to,x,y);
    }else{
        return false;
    }
}

bool horse_moves(int from[],int to[]){
    int tempx,tempy;
    tempx = abs(from[0]-to[0]);
    tempy = abs(from[1]-to[1]);
    return((tempx == 2 && tempy == 1)||(tempx ==1 && tempy ==2));
}


bool rook_moves(char board[][9],int from[],int to[]){
    int x,y;
    x = to[0]-from[0];
    y=to[1]-from[1];
    if (from[0]==to[0] || from[1]==to[1]){

        return diagonal_check(board,from,to,x,y);
    }else{
        return false;
    }
}

bool queen_moves(char board[][9],int from[],int to[]){

    int x = to[0]-from[0];
    int y= to[1]-from[1];
    if((from[0]==to[0] || from[1]==to[1]) || (abs(x)==abs(y))){
        return diagonal_check(board,from,to,x,y);
    }else{
        return false;
    }
}
bool king_move(int from[],int to[]){
    int x, y;
    x = abs(from[0] - to[0]);
    y = abs(from[1] - to[1]);

    return( x== 1 || y == 1);
}

bool pawn_move(int from[],int to[],char piece){
    int x,y;
    x = from[0]-to[0];
    y=from[1]-to[1];
    if(piece == 'p'){
        if((x==-1 && y==0)||(from[0]==1 && x==-2 && y==0)){
            return true;
        }
        return false;
    }else{
        if((x==1 && y==0) ||(from[0]==6 && x==2 && y==0)){
            return true;
        }
        return false;
    }

}
void place(char board[][9],int from[2],int to[2],char piece,int color,map<char,int>& obj){
    if(board[to[0]][to[1]] == '-' or obj[board[to[0]][to[1]]]!=color){
        board[from[0]][from[1]] = '-';
        board[to[0]][to[1]] = piece;}
}

bool check_own(char board[][9],int from[2],int to[2],map<char,int>& obj){
    int x,y;
    x = board[from[0]][from[1]];
    y = board[to[0]][to[1]];
    return (obj[x]!=obj[y]);
}
void mapping(map<char,int>& obj){
//black pieces
    obj['b']=-1;
    obj['h']=-1;
    obj['q']=-1;
    obj['r']=-1;
    obj['k']=-1;
    obj['p']=-1;
//white pieces
    obj['B']=1;
    obj['H']=1;
    obj['Q']=1;
    obj['R']=1;
    obj['K']=1;
    obj['P']=1;

}
void black_piece(char board[][9]){
    int i;
    for(i=1;i<9;i++){
        board[1][i]='p';
    }

    board[0][1] = board[0][8] = 'r';
    board[0][2] = board[0][7] = 'h';
    board[0][3] = board[0][6] = 'b';
    board[0][4]= 'q';
    board[0][5]='k';

}

void white_piece(char board[][9]){
    int i;
    for(i=1;i<9;i++){
        board[6][i]='P';
    }

    board[7][1] = board[7][8] = 'R';
    board[7][2] = board[7][7] = 'H';
    board[7][3] = board[7][6] = 'B';
    board[7][4]= 'Q';
    board[7][5]='K';

}

void mapping_coord(map<char,int>& obj,map<int,char>& obj2){
    for(int i=0;i<8;i++){
        obj['a'+i]=i;
    }
    for(int i=0;i<8;i++){
        obj2[i]='a'+i;
    }
}

void remove_node(struct node **tail){
    if((*tail==NULL)){
        return;
    }else{
        struct node *temp;
        temp=*tail;
        (*tail)=temp->prev;
        if((*tail)!=NULL){
        (*tail)->next=NULL;}
        free(temp);
    }
};


void make_move(char board[][9],int color,map<char,int>& obj,map<char,int>& cord,char piece,int from[],int to[]){
    char row1,row2;
    cout<<"enter the from coordinates:";
    cin>>row1>>from[1];
    cout<<"enter the to coordinates:";
    cin>>row2>>to[1];
    from[0]=cord[row1];
    to[0]=cord[row2];
    int move_made = 1;
    if(valid(board,from,to,color,obj) && check_own(board,from,to,obj)){
        piece = board[from[0]][from[1]];
        if(piece == 'b' || piece == 'B'){
            if (bishop_move(board,from,to)){place(board,from,to,piece,color,obj);
                return;}
            else{
                move_made=1;
            }
        }

        else if(piece == 'h' || piece == 'H'){
            if (horse_moves(from,to)){ place(board,from,to,piece,color,obj);
                return;}else{
                move_made=1;
            }
        }

        else if(piece == 'r' || piece == 'R'){
            if (rook_moves(board,from,to)){place(board,from,to,piece,color,obj);
                return;}
            else{
                move_made=1;
            }
        }

        else if(piece == 'q' || piece == 'Q'){
            if (queen_moves(board,from,to)){ place(board,from,to,piece,color,obj);return;}
            else{
                move_made=1;
            }
        }

        else if(piece == 'p' || piece == 'P'){
            if(pawn_move(from,to,piece)){ place(board,from,to,piece,color,obj);return;}
            else{
                move_made=1;
            }
        }

        else if(piece == 'k' || piece == 'K'){
            if(king_move(from,to)){ place(board,from,to,piece,color,obj);return;}
            else{
                move_made=1;
            }
        }
        else{
            move_made = 1;

        }
    }else{
        move_made=1;
    }

    if(move_made==1 ){
        cout<<"invalid move"<<endl;
        return make_move(board,color,obj,cord,piece,from,to);
    }
}

int colorswitch(int color){
    if(color==1){
        return -1;
    }else{
        return 1;
    }
}

void trav(struct node *head,map<int,char>& obj){
    struct node *p;
    p=head;
    while(p!=NULL){
        cout<<"from coordinates: "<<obj[p->from[0]]<<p->from[1]<<endl;
        cout<<"to coordinates: "<<obj[p->to[0]]<<p->to[1]<<endl;
        printf("piece moved: %c \n\n",p->piece);
        p=p->next;
    }
}
int main(){
    char board[9][9];
    int from[2],to[2];
    char piece;
    struct node *head = NULL;
    struct node *tail = NULL;
    char black_out[8];
    char white_out[8];
    string chance="start";
    int color=1;
    bool run=true;
    map<char,int> mapped_piece;
    map<char,int> mapped_cord;
    map<int,char> map_co_alpha;
    mapping_coord(mapped_cord,map_co_alpha);
    mapping(mapped_piece);
    makeboard(board);
    black_piece(board);
    white_piece(board);
    printboard(board);

    while(run){

        make_move(board,color,mapped_piece,mapped_cord,piece,from,to);

        add_nodes(&head,&tail,from,to,board[to[0]][to[1]]);
        printboard(board);
        while(chance=="start") {
            cout << "what do you wish perform [undo,next,exit]:";
            cin >> chance;
            if (chance == "next") {
                color = colorswitch(color);
            } else if (chance == "undo") {
                place(board, tail->to, tail->from, tail->piece, color, mapped_piece);
                remove_node(&tail);
                printboard(board);
            }
            else if(chance=="exit"){
                run=false;
                break;
            }
        }
        chance = "start";
    }

    //to print all the moves made
    trav(head,map_co_alpha);


}
