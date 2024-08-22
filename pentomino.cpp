#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include "pieces.h"
#include<array>
#include<cmath>
#include<list>
#include<tuple>
#include<algorithm>

using namespace :: std;

const float pi = atan(1)*4; // define pi number.
typedef int (*shapes_p)[2]; // an array of pointers to int *[2] 
typedef int (*pointer)[2];
// this class is to create a vector that holds char symbols and the pieces(aka pointer to arrays).
class mypairs{
public:
char ch1;
int (*p)[2];
//public:
mypairs(char ch2,int (*np)[2]){
ch1=ch2;
p=np; // assignment!
}
};

vector<vector<char>> create_board(){
/// create empty board with all chars 'b'.
const int rows   = 10;
const int colums =  6;
vector< vector <char> > board;
for (int i = 0; i < rows; i++){
    vector<char>mytemp;
    for (int j = 0; j < colums; j++){
     mytemp.push_back('b');}
     board.push_back(mytemp);
  //   mytemp.clear(); // reset to empty.
}
return board;
}

void save_to_file(vector<vector<char>> &board){
 vector<char> solutions;
 std::ofstream ost;
 ost.open("solutions_final.dat",std::ios_base::app);
 cout << "save solution to file" << endl;
 for (size_t i = 0; i < board.size(); i++){
  for (size_t j = 0; j < board[i].size(); j++){
     solutions.push_back(board[i][j]);
  }
 }

 for (char ch : solutions) {  ost << ch << " ";};
 ost << std::endl;
} 

struct piece_array{ 
// A class of 2D array that holds all possible valid variations of pieces in a given square (X,Y).

vector< vector<pair<int,int>> > v;
piece_array(vector< vector<pair<int,int>> > vek):v(vek){};

int vek_size(){
 int n = v.size();
 return n;}
};

// print to screen the vector<piece_array> class.
void print_vek(vector< vector<pair<int,int>> > &myvek){
 for (auto currentvector : myvek){
     for (auto ptr : currentvector){
     cout << ptr.first << '\t' << ptr.second << endl;
     }
 cout << endl;
 }
}

// this STRUCT assigns for each pair of points a char that corresponds to the same piece.
struct pieces{

int  X;
int  Y;
char s;
pieces(int,int,char);
};

pieces::pieces(int n1, int n2,char ss){
X=n1;
Y=n2;
s=ss;
};

void error(string ss){ // useful for debugging.
throw runtime_error(ss);
};  

void update_vector(vector<pair<int,int>> &piece_vek,vector< vector <char> > &board,char &last_added_piece){
int count=0;
    for (size_t i = 0; i < board.size(); i++){
      for (size_t j = 0; j < board[i].size(); j++){
        if (board[i][j]==last_added_piece){
          piece_vek[count].first=i;
          piece_vek[count].second=j;
          ++count;}
      }
    }
}

void print_board(vector < vector <char> > &board ){
cout << " " << endl;
cout << "print board to the screen" << endl;
for (size_t i = 0; i < board.size(); i++){
 for (size_t j = 0; j < board[i].size(); j++){
  cout << board[i][j]<<'\t';} 
  cout << "\n";}
}

// 1. 'fill' is a function that creates the pieces.
// instead of int a[][2] try int** &my_arr
vector<pieces> fill(vector<pieces> vec,int a[][2],char xx){
for (int i=0;i<5;++i){
 for (int j=0;j<1;++j){
  vec.push_back(pieces(a[i][j],a[i][j+1],xx));}
} return vec;};

// 1.1 fill pieces but after a rotation. it takes a int** arr argument.
vector<pieces> fill_rotate(vector<pieces> vec,int** a,char xx){
for (int i=0;i<5;++i){
 for (int j=0;j<1;++j){
 vec.push_back(pieces(a[i][j],a[i][j+1],xx));}
 } return vec;};

// 2. 'add_pieces' is a function that add pieces to the board.
void add_pieces(vector<pieces> vek,vector< vector <char> > &board,int x_disp,int y_disp){
for (int i=0;i<5;++i){
 int  a = vek[i].X + x_disp;
 int  b = vek[i].Y + y_disp; 
 char c = vek[i].s;
 board[a][b] = c;}
};

// 2.1. 'delete_pieces' deletes the pieces from the board.
void delete_pieces(vector< vector <char> > &board,char letter){
 for  (size_t i = 0; i < board.size(); i++){
  for (size_t j = 0; j < board[i].size(); j++){
   if (board[i][j]==letter){board[i][j]='b';}
  }
 }
//cout << "Piece " << letra << " deleted from the board." << endl;
}

// 2.2. 'delete_piece_list'.
// Decide how many pieces to delete. Then add it with new reflexion/rotation combination.
char delete_n_pieces(vector<char> &piece_label,vector< vector <char> > &board,int delete_p){
    
    cout << "Inside function. Needs to delete " << delete_p << " pieces" << endl;
    cout << "Subroutine delete_n_pieces " << endl;
    // 'delete_p' chars from piece_label;

   int  start = piece_label.size() - delete_p;  // index to start.
   int  end   = piece_label.size();             // end of vector. 
   char my_char; // char of piece to delete

   // delete n pieces from the board.
   vector<char> pieces_deleted;
   int li = piece_label.size() - delete_p;
   for (int i=li; i < piece_label.size();++i){
   my_char = piece_label[i];
   pieces_deleted.push_back(my_char);  // add pieces to be deleted to this vector.
   delete_pieces(board,my_char);       // call delete_pieces() from the board.
   }

   // loop through pieces_deleted.
   for (char x : pieces_deleted) {cout << x << " Pieces to be Deleted from piece_label." << endl;}

   // next delete n pieces from piece_label. 
   my_char = piece_label[start]; // 
   piece_label.erase(next(piece_label.begin(), start),next(piece_label.begin(), end) );
return my_char;}

// A function that return and integer value of how many 'b' within a given square (boundary not included)
int return_bs_square(vector < vector <char> > &board,int row_i,int row_k,int col_i,int col_k){

int num_b    = 0;
int bs_line6 = 0;
int bs_line7 = 0;

for (size_t i = row_i + 1; i < row_k; i++){
 for (size_t j = col_i + 1; j < board[i].size() -5 + col_k -1; j++){
 if (board[i][j]=='b'){++num_b;} 
  //cout << board[i][j]<<'\t';}
  //cout << "\n";}
 }
}
return num_b;}

// Check for overlapping between board&pieces and gaps between pieces.
 string check_overlapping(vector<pieces> &vek,vector< vector <char> > &board,int x_disp,int y_disp)
 {
  string status1;
  string piece_status;
  string piece_on_board="on";

 for (int i=0;i<5;++i){
  int aa = vek[i].X + x_disp;
  int bb = vek[i].Y + y_disp;
  //cout << "aa , bb " << aa << " " << bb << endl;
  if (aa < 0 || bb < 0 || bb > 5 || aa > 9){
   piece_on_board="off";}
 if (piece_on_board=="off"){
  piece_status="failed";
  //cout << "1 .Piece outside the board! " << aa << '\t' << bb <<endl;
  return piece_status;}
 } // first loop
 
 // if the piece is on the board then checks for overlapping.
 for (int i=0;i<5;++i)
 {
  int  a = vek[i].X + x_disp;
  int  b = vek[i].Y + y_disp;
  char c = vek[i].s;
  //cout << a << '\t'<< b << " i: " << i << endl;  
  if (board[a][b]!='b'){
    status1="failed";
    }
  else{
     status1="empty";
     }
  if (status1=="failed") 
     {break;}
  } // end of for loop.

vector< vector <char> > newboard;
newboard=board; // copy board.
// vek is a vector<pieces> .
for (int i=0;i<5;++i){
  int  a = vek[i].X + x_disp;
  int  b = vek[i].Y + y_disp;
  char c = vek[i].s;
  newboard[a][b] = c; // tries to add char c in the position [a,b]
}

// 3.1 CHECK FOR GAPS NOW using newboard.

list<int>count_lower;
list<int>count_upper;
list<int>count_b;
list<int>count_middle;
list<int>count_1thcolumn;
list<int>count_2thcolumn;
list<int>count_4thcolumn;
list<int>count_5thcolumn;

for (size_t i = 0; i < newboard.size(); i++){ // start from line 1.
  int count1=0;
  int count2=0;
  int count3=0;
  int count4=0;
  int count1th=0;
  int count2th=0;
  int count4th=0;
  int count5th=0;

  // counts for each line 'i' and all 'j' columns, save to each list and repeat.
  // until finish the 2 for loops.
  for (size_t j = 0; j < newboard[i].size(); j++){
   switch(j){
   case 0 ... 2:
    if (newboard[i][j]=='b'){
    ++count1;} // count_lower columns 0-2 // needed for lowergaps.
    break;
   case 3 ... 5:
    if (newboard[i][j]=='b'){
    ++count2;} // count_upper columns 3-5
    break;
   }
  switch(j){
    case 1 ... 3:
    if (newboard[i][j]=='b'){ 
     ++count4;} // count_middle 1-3
     break;
   }
   switch(j){
    case 1:
    if (newboard[i][j]=='b'){
    ++count1th;}
    break;
    case 2:
    if (newboard[i][j]=='b'){
    ++count2th;}
    break;
    case 4:
    if (newboard[i][j]=='b'){
    ++count4th;}
    break;
    case 5:
    if (newboard[i][j]=='b'){
    ++count5th;}
    break;
   }
   if (newboard[i][j]=='b'){
    ++count3;} // count_b count all columns. 
   }
  count_lower.push_back(count1);
  count_upper.push_back(count2);
  count_b.push_back(count3);
  count_middle.push_back(count4);
  count_1thcolumn.push_back(count1th);
  count_2thcolumn.push_back(count2th); 
  count_4thcolumn.push_back(count4th);
  count_5thcolumn.push_back(count5th);
}
///// check for gaps in bottom right of the board. columns 4th,5th.
int column1 = 0;
int column2 = 0;
int column4 = 0;
int column5 = 0;
for (int x : count_1thcolumn){column1 = x + column1;}
for (int x : count_2thcolumn){column2 = x + column2;}
for (int x : count_4thcolumn){column4 = x + column4;}
for (int x : count_5thcolumn){column5 = x + column5;}

string bottomleft_corner;
string bottomright_corner;
if (column1!=0 && column2==0)
{
// there is a gap in column 1 last row!.
bottomleft_corner="NOGAP";
}
else {
bottomleft_corner="NOGAP";
}


if (column4==0 && column5!=0)
{
// there is a gap in column 5 last row!.
bottomright_corner="GAP";
}
else {
bottomright_corner="NOGAP";
}
/////////////////


// Count last 3 rows only and "b's" in columns 0:2 .
// in a matriz 3X3 at 7:10 and columns 0:2 there must be 
// at least 3 'b's, otherwise there is a gap.

int c1=0;
int c2=0;
int c3=0;
for ( size_t i = 7; i < newboard.size(); i++){
  if (newboard[i][0]=='b'){
  ++c1;}
  if (newboard[i][1]=='b'){
  ++c2;}
  if (newboard[i][2]=='b'){
  ++c3;}
}

auto p1 = count_lower.begin();
advance(p1, 7);
int line7 = *p1;

auto p2 = count_lower.begin();
advance(p2,8);
int line8 = *p2;

auto p3 = count_lower.begin();
advance(p3,9);
int line9 = *p3;

vector<int> bek;
bek.push_back(c1);
bek.push_back(c2);
bek.push_back(c3);
bek.push_back(line7);
bek.push_back(line8);
bek.push_back(line9);


int max = *max_element(bek.begin(), bek.end());
string lower_bottom;
if (max==0 || max==3 || c1==0){
lower_bottom="nogap";
}
else {
lower_bottom="gap";
}

/////
//// middle gaps.
///  Count rows 4:6 only and 'bs' in columns 1:3 .
///  same as above.

// list<int> count_middle; Defined above.
int c4=0;
int c5=0;
int c6=0;
for (size_t i = 4; i < 7; i++){
  if (newboard[i][1]=='b'){
  ++c4;}
  if (newboard[i][2]=='b'){
  ++c5;}
  if (newboard[i][3]=='b'){
  ++c6;}
}

auto p4 = count_middle.begin();
advance(p4, 4);
int line4 = *p4;

auto p5 = count_middle.begin();
advance(p5,5);
int line5 = *p5;

auto p6 = count_middle.begin();
advance(p6,6);
int line6 = *p6;

vector<int> bek2;
bek2.push_back(c4);
bek2.push_back(c5);
bek2.push_back(c6);
bek2.push_back(line4);
bek2.push_back(line5);
bek2.push_back(line6);

int max2 = *max_element(bek2.begin(), bek2.end());
string middle_gap;
if (max2==0 || max2==3){
middle_gap="nogap";
}
if (max2!=0 && max2!=3 && line4==0 && line5==0) {
middle_gap="nogap";
}
else {
middle_gap="nogap";
}

/////

// GAPS at UPPER EDGE.
// GAPS of b in a cross.
string edge_gap       = "nogap"; 
string break_edgeloop = "NO";
for (size_t i = 1; i < newboard.size()-1; i++){
   if (newboard[i][5]=='b'){
    char i1 = newboard[i+1][5];
    char c2 = newboard[i][4];
    if (i1!='b' && c2!='b'){
     edge_gap="gap";
     break_edgeloop="YES";
     }
   } // main if 
   if (newboard[i][0]=='b'){
    char i0 = newboard[i+1][0];
    char c1 = newboard[i][1];
    if (i0!='b' && c1!='b')
    {
    edge_gap="gap";
    break_edgeloop="YES";
    }
   }
if (break_edgeloop=="YES") {
  //cout << "Gap at the edge! " << endl;
  break;}
} // first for loop


//// GAPS of b in a cross.
string cross_gap="nogap"; 
string break_loop="NO";
//cout << "cross gap below " << endl;
for (size_t i = 1; i < newboard.size()-1; i++){
  for (size_t j = 1; j < newboard[i].size()-1; j++){
   if (newboard[i][j]=='b'){
    char i1 = newboard[i-1][j];
    char i2 = newboard[i+1][j];
    char c1 = newboard[i][j-1];
    char c2 = newboard[i][j+1];
    //cout << i << " i,j cross gap " << j << endl;
    //cout << i1 <<'\t' << i2 << '\t' << c1 << '\t' << c2 << endl;
    //print_board(newboard);
    //cout << "//////////"<< endl;
    if (i1!='b' && i2!='b' && c1!='b' && c2!='b'){
     cross_gap="gap";
     break_loop="YES";
     }
   } // main if 
  if (break_loop=="YES") {break;}
  } //second for loop
if (break_loop=="YES") {break;}
} // first for loop


//cout << "GAPS: " << edge_gap << '\t' << cross_gap << '\t' << middle_gap << '\t' << lower_bottom << endl;
string gaps;
if (edge_gap=="nogap" && cross_gap=="nogap" && middle_gap=="nogap" && 
    lower_bottom=="nogap"){gaps="nogap";}
else{gaps="gap";}

// from 0-9. LOWER GAPS.
string status_lower;
for (int i=0;i<10;++i){
 auto position1 = count_lower.begin();
 auto position2 = count_lower.begin();
 advance(position1, i);
 int bb = *position1;
 advance(position2, i+1);
 int cc = *position2; 
 //cout << "LOWER GAP BOTTOM" << bb << '\t'<< cc << '\t';
 //cout << endl;
 if (bb==cc==0){status_lower="nolowergap";}
 if (bb>cc && cc==0){
  status_lower="lowergap";
  break;}
 else if (bb >= cc && cc!=0){
 status_lower="nolowergap";
 }
 else if (cc >= bb && cc!=0){
 status_lower="nolowergap";
 }
}
// UPPER GAP.
// from 0-9.
string status_upper;

for (int i=0;i<10;++i){
 auto position1 = count_upper.begin();
 auto position2 = count_upper.begin();
 advance(position1, i);
 int bb = *position1;
 advance(position2, i+1);
 int cc = *position2; 
 //cout <<"UPPER GAP " << bb << '\t'<< cc << '\t';
 //cout << endl;
 if (bb==cc==0){status_upper="nopuppergap";}
 if (bb>cc && cc==0){
  status_upper="uppergap";
  //cout << "There is an upper gap!";
  break;}
 else if (bb >= cc && cc!=0){
 status_upper="nouppergap";
 }
 else if (cc >= bb && cc!=0){
 status_upper="nouppergap";
 }
}


// from 0-9.
// for all the columns.
string status2;
for (int i=0;i<10;++i){
 auto position1 = count_b.begin();
 auto position2= count_b.begin();
 advance(position1, i);
 int bb = *position1;
 advance(position2, i+1);
 int cc = *position2; 
 //cout <<"ALL COLUMNS " << bb << '\t'<< cc << '\t';
 //cout << endl;
 if (bb==cc==0){status2="nogap";}
 if (bb>cc && cc==0){
  status2="gap";
  //cout << "There is a gap!";
  break;}
 else if (bb >= cc && cc!=0){
 status2="nogap";
 }
 else if (cc >= bb && cc!=0){
 status2="nogap";
 }
}

/// Below another section that finds for line6, line7
/// If there are squares of fixed size with b's in it.
/// Find if lines 6,7 have no b's.

int bs_line6=0;
int bs_line7=0;

for (size_t i = 0; i < newboard.size(); i++){
 for (size_t j = 0; j < newboard[i].size(); j++){
  if (i==6 && newboard[i][j]=='b'){++bs_line6;}
  if (i==7 && newboard[i][j]=='b'){++bs_line7;}
 }
}

// it is enough if bs_line6 = 0 .
if (bs_line6==0 && bs_line7!=0){bs_line7=bs_line6;}

// from line 7 to 10. column 1-4.
int col1 = 0;
int col2 = 0;
int col3 = 0;
int col4 = 0;

// from line7 to 10. Columns 1 to 4.
for  (size_t i = 7; i < newboard.size();i++){
  if (board[i][1]=='b'){++col1;}
  if (board[i][2]=='b'){++col2;}
  if (board[i][3]=='b'){++col3;}
  if (board[i][4]=='b'){++col4;}
}

//if (bs_line6==0){ cout << "Line 6 is full" << endl;}

// IF LINE 7 IS FREE FROM b's .

//if (bs_line7==0){cout << "Line 7 is full" << endl;}
string st1,st2,st3,st4,st5,st6,st7,st8;


string squares_b="NOGAP";
if  (bs_line7==0){
 if (col1==0){
  int m1 = return_bs_square(newboard,7,10,0,1); 
  if (m1 > 0) {st1="GAP";}
  int m2 = return_bs_square(newboard,7,10,1,6); 
  if (m2 % 5==0){st2="NOGAP";} // multiple of 5, no gap.
  if (m2 == 1){st2="GAP";}; // odd number of b's then there is GAP.
   
  if (m2==1){st2="GAP";}
 }
 if (col2==0){
  int m1 = return_bs_square(newboard,6,10,-1,2); 
  if (m1< 5){ st3="GAP";}
  int m2 = return_bs_square(newboard,6,10,2,6);
  //m2 = (m2 % 5);
  if (m2<5){st4="GAP";} 
 }
 st3="NOGAP";
 st4="NOGAP";

 if (col3==0){
  int m1 = return_bs_square(newboard,7,10,0,3); 
  if (m1 > 0){st5="GAP";}
  int m2 = return_bs_square(newboard,7,10,3,6);
  if (m2 < 5){st6="GAP";}
 }
 if (col4==0){
    int m1 = return_bs_square(newboard,7,10,0,4); 
    m1 = (m1 % 2);
    if  (m1==1){ st7="GAP";} // if m1 is odd there is GAP.
    int m2 = return_bs_square(newboard,7,10,4,6);
    if (m2 > 0){ st8="GAP";} 
 }
 if (st1=="GAP"||st2=="GAP"||st3=="GAP"||st4=="GAP"||st5=="GAP"||st6=="GAP"||st7=="GAP"||st8=="GAP"){squares_b="GAP";}
}

string upperleft;
int ll1 = return_bs_square(newboard,-1,3,0,3); // .
if (ll1==1){upperleft ="GAP";}
if (ll1!=1){upperleft  ="NOGAP";}

string upperright;
int ll2 = return_bs_square(newboard,-1,3,2,6);
if (ll2<=1){upperright="GAP";}
if (ll2>1){upperright="NOGAP";}
if (ll2==0){upperright="NOGAP";}
string bottomright;
int ll3 = return_bs_square(newboard,6,10,2,6); // last 3 rows and last 3 columns.
if (ll3<=3){bottomright="GAP";}
if (ll3==0){bottomright="NOGAP";}
if (ll3>3){bottomright="NOGAP";}

//cout << "GAPs for the squares from 1 to 8 :" << endl;
//cout << " <- " << st1 << " - "  << st2 << " - " << st3 << " - " <<st4 << "->"<< endl;
//cout << " <- " << st5 << " - "  << st6 << " - " << st7 << " - "<< st8 << "->"<< endl;
//if (squares_b=="GAP") error("mind the GAP ");

/////
status_lower = "nolowergap";
upperleft    = "NOGAP";
upperright   = "NOGAP";

string status; 

bottomright="NOGAP";
if (bottomright=="NOGAP" && upperright=="NOGAP" && upperleft=="NOGAP" && squares_b=="NOGAP" && bottomleft_corner=="NOGAP" && bottomright_corner=="NOGAP" && gaps=="nogap" && status1=="empty" && status_lower=="nolowergap" && status_upper=="nouppergap" && status2=="nogap"){status="empty";}
else{status="failed";}

//cout << endl;
//cout << "upperleft " << upperleft << endl;
//cout << "upperright " << upperright << endl;
//cout << "square b " << squares_b << endl;
//cout << "Bottom left corner " << bottomleft_corner << endl;
//cout << "Bottom right corner " << bottomright_corner << endl;
//cout << "Middle gaps: "  << gaps << endl;
//cout << "Overlap: "     << status1 << endl;
//cout << "Lower gaps: "   << status_lower << endl;
//cout << "Upper gaps: "   << status_upper <<endl; 
//cout << "All columns: "  << status2 <<endl;
//cout << "Overlap or GAPS: " << status << endl;
//cout << endl;

return status;};

// Function to ROTATE pieces.

int** rotate(int** &my_arr,float theta){
int** rot = 0;
rot = new int*[5];
for (int i=0;i<5;++i){
 rot[i] = new int[2];
 rot[i][0] = round(cos(theta)*my_arr[i][0]) - round(sin(theta)*my_arr[i][1]);
 rot[i][1] = round(sin(theta)*my_arr[i][0]) + round(cos(theta)*my_arr[i][1]);
 }
return rot;
}

// Function to inverse pieces.
int** reflexion(int my_arr[5][2],int nn){
int** ref = 0;
ref = new int*[5];
for (int i=0;i<5;++i){
 ref[i] = new int[2];
 ref[i][0] = 1*my_arr[i][0]  + 0*my_arr[i][1];
 ref[i][1] = 0*my_arr[i][0]  - nn*my_arr[i][1];
 }
return ref;
}



// important: clean up memory
void clean_memory( int** my2DArray){
   for (int h = 0; h < 5; h++) // loop variable wasn't declared
   {
   delete [] my2DArray[h];
   }
   delete [] my2DArray;
   my2DArray = 0;
   //cout << "Array deleted!" << endl;
}


// Function that keeps an ordering to fill in the board.
// keep_count(rows,column,min empty x,min empty y)
 tuple<int,int> keep_count(int x, int y,int a, int b){

 if (y<7){
  x=x;
  ++y;
 }
 if (y==6){
  ++x;
  y=0;
 }
 //cout << x << " --- "<< y << endl;
 if (x>10){error("STOP: Piece outside the board not allowed!.");}
 /////
 if (x > a && a!=0){ // if the count_row is larger than the min empty value.
 x=a;
 y=0;
 }
 if ( x >= 0 && x < a){ // if the count laggs behind respect to min empty slot.
 x = a;
 y = 0;
 }
 return make_tuple(x,y); 
}

// The next 2 functions are just to print to the screen.
void print_reflexion(int** &arr_ref){
//cout << "Molecule Inversed and centered" << endl;
 for (int h = 0; h < 5; h++){
 for (int w = 0; w < 2; w++){
  printf("%i,", arr_ref[h][w]);
 } printf("\n");}
}


void print_rotate(int** &arr){
 //cout << "ROTATED AND CENTERED" << endl;
 for (int h = 0; h < 5; h++){
   for (int w = 0; w < 2; w++)
    {printf("%i,", arr[h][w]);}
  printf("\n");
 }
}

// function that performs reflections and rotations 
// on each piece and tries to fit them on the board.

string fit_piece(shapes_p &shapes,int xx,int yy,char ch,vector < vector <char> > &board,int new_ref,int nrot,vector<char> &pieces_in_order,vector<char> &piece_label,vector< pair<int,int> > &piece_vek,
vector<piece_array> &piece_var,int ii)
{
  string statusX; 
  string status="failed";
  vector<pieces>temp_rot; 
  vector<pair<int,int>> vpair;
  vector< vector<pair<int,int>> > v_vpair;
  int** arr_ref; // declared
  int** arr; // declared 
  int cou=0;
  int count_el=0;
  int num=1;
  // piecedata is a vector<piece_data>
  list<int> nn{new_ref,-1*new_ref}; // -1 or 1 for the identity, inverse matrix.
  for (auto k : nn){ // Loop N 1
    arr_ref = reflexion(shapes,k); // nn has two values -1 1.
   //print_reflexion(arr_ref); // useful for debugging.
   //cout << " ........... " << ch << endl;
   
   for (int n=nrot;n<4;++n){ // LOOP N 2.
      arr = rotate(arr_ref,n*pi/2); 
      // next we have 2 for loops that moves 'arr' to xx,yy.
      // cout << " ----------------- " <<endl; 
      // cout << " Reflection,Rotation "  << k << '\t' <<  n << '\t' << ch<<endl;
      for (int i=0; i<5; ++i){ // loop N 3
       int  a = xx - arr[i][0];
       int  b = yy - arr[i][1];
       for (int j=0;j<5;++j)       { 
        arr[j][0] = arr[j][0] + a;
        arr[j][1] = arr[j][1] + b; }
        //print_rotate(arr);
        // cout << "......" << endl;
        // vector<pieces>temp_rot; defined above.
        temp_rot = fill_rotate(temp_rot, arr,ch); // create a rotated piece.
        statusX = check_overlapping(temp_rot,board,0,0); // function that checks overlapping. 
        //cout << " status of piece " << ch << '\t' << statusX << endl;
         if (statusX=="failed"){temp_rot.clear();} 
         if (statusX=="empty" && pieces_in_order[ii]==ch){ // begin if label: A1
          add_pieces(temp_rot,board,0,0);
          delete_pieces(board,ch); // delete same piece.
          // this variable: vector<pair<int,int>> vpair was defined above. 
          for (int i=0;i<5;++i){ // create a vector pair named vn.
           vpair.push_back(make_pair(temp_rot[i].X,temp_rot[i].Y));
          }
          sort(vpair.begin(),vpair.end()); // sorts vector in ascending order 
          if (v_vpair.size()==0){v_vpair.push_back(vpair);}
          string bol;
          bol="False";
          for (int i=0;i<v_vpair.size();++i){
           if (v_vpair[i]==vpair){
             bol="True";
             }
          }
          if (bol=="False"){v_vpair.push_back(vpair);}
          vpair.clear();
          temp_rot.clear();
         } // end if label: A1
        } //LOOP N3
        } //LOOP N2
        } // LOOP N1
        //vector<piece_array> piece_var: this is a vector of vector of vector<pairs>
        // basically each line corresponds to a piece (a vector) and new line of the vector
        // are possible valid rotations and reflections. 
        piece_var.push_back(v_vpair);
        v_vpair.clear(); 
         
        if (piece_var[ii].v.size()>0 && pieces_in_order[ii]==ch){
        status="empty";
        }
        if (piece_var[ii].v.size()==0 && pieces_in_order[ii]==ch){status="failed";}
        if (status=="empty" && pieces_in_order[ii]==ch){
           vector<pieces> to_add;
           vector<vector<pair<int, int>>> F_pair = piece_var[ii].v; // to make a copy, .v is a method in the CLASS.
           vector<pair<int,int>> S_pair = F_pair[0]; // first vector (piece) of the vector.
           for (int i=0;i<5;++i){
             to_add.push_back(pieces(S_pair[i].first,S_pair[i].second,ch));
            }
            add_pieces(to_add,board,0,0);
            int el = count(piece_label.begin(),piece_label.end(),ch); //count how many times variable ch in piece_label.
            if (el==0) {piece_label.push_back(ch);}
            cout << ch << " piece added inside fit_piece() function " << endl;
            cout << " .............. " << endl;
            cout << "Min (x,y) is... " << xx << '\t' << yy << endl; 
            print_board(board);
            clean_memory(arr_ref);
            clean_memory(arr);
        }
            
return status;} // end of fit_piece function.


// function that return the lowest 'b' value on the board.
tuple<int,int> return_min_b(vector< vector <char> > &board){
int x;
int y;
string check;
for  (size_t i = 0; i < board.size(); i++){
 for (size_t j = 0; j < board[i].size(); j++){
  if (board[i][j]=='b'){
   x=i;
   y=j;
   check="True";
   break;}
 }
 if (check=="True"){break;}
}
return make_tuple(x,y);
} 

void reset_vector(vector< pair<int,int> > piece_vek){
 for (int i=0;i<5;++i)
  {
  piece_vek[i].first=0;
  piece_vek[i].second=0;
  }
}

int return_pos(int n, vector<piece_array> &piece_var){
    cout << " "  << endl;
    cout << "Inside retrun_pos function" << endl;
    // n is the size of piece_var .
    int newpos=-1;
    for (int j = n; j --> 0;)
    {
     int nn = piece_var[j].v.size();
     if (nn==1) {newpos=-1;};
     if (nn==0) {newpos=-1;};
     if (nn>1) {newpos=j; break;} // a backward loop and when it find a vector that has multiple shapes (rotations,etc) it stops.
    }
    cout << " Position of piece with several options is: " << newpos << endl;
    //if (nn==-1){cout  << pos << '\t'<< n << '\t' << nn; error("Could not find a piece with more alternatives,STOP!");}; 
    cout << " Exit return_pos() function: " << endl;
   return newpos;
}

void piece_iterator(vector<pieces> &to_add,vector<piece_array> &piece_var,int pos,vector<char> &pieces_in_order,vector< vector <char>> &board)
{
vector<vector<pair<int, int>>> F_pair = piece_var[pos].v;
piece_var[pos].v.erase(std::next(piece_var[pos].v.begin(),0));
F_pair.erase( std::next(F_pair.begin(),0));
vector<pair<int,int>> S_pair = F_pair[0];  //  take position of new vector at zero.
char ch1 = pieces_in_order[pos];
// vector<pieces> to_add;
// add into add_pices the new piece.
for (int k=0;k<5;++k){to_add.push_back(pieces(S_pair[k].first,S_pair[k].second,ch1));}
add_pieces(to_add,board,0,0);
cout << "Piece " << ch1 << " added again with new shape" << endl;
}

// MAIN!!!!!!!
int main(){
int cuenta=0;
int pos; 
// open file with potential soltutions and read it 
std::ifstream ist;
ist.open("solutions.dat");
std::string line;
std::vector<char> pieces_in_order;

// while getline end at the end of MAIN.
while (getline(ist,line)){
 pos=0;
 std::string solutionlabel("Solution Found"); // needed at the very end of this file.
 vector<vector<char>> board = create_board();

 // initialize vector possible_solution for the algorithms.
 for (int i=0;i<25;++++i){pieces_in_order.push_back(line[i]);};
 std::cout << " ------- " << std::endl;
///
vector<piece_array> piece_var; // vector of vector of vectors. 
vector< pair<int,int> > piece_vek; // vector of pairs.
//vector< vector<pair<int,int>> > vek1{v1}; // vector of vector of pairs.

for (int i=0;i<5;++i){piece_vek.push_back(make_pair(0,0));} // initialize.
char last_added_piece;

pointer p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12; // alias for (*pointer)[2]; 
// a pointer for each array.
p1  =  arr1; // defined in pieces.h 
p2  =  arr2;
p3  =  arr3;
p4  =  arr4;
p5  =  arr5;
p6  =  arr6;
p7  =  arr7;
p8  =  arr8;
p9  =  arr9;
p10 =  arr10;
p11 =  arr11;
p12 =  arr12;


std::vector<mypairs> vek; // vek has per line a char and a piece associated (by means of a pointer)
vek.push_back(mypairs('u',p1));
vek.push_back(mypairs('x',p2));
vek.push_back(mypairs('L',p3));
vek.push_back(mypairs('w',p4));
vek.push_back(mypairs('T',p5));
vek.push_back(mypairs('l',p6));
vek.push_back(mypairs('I',p7));
vek.push_back(mypairs('Z',p8));
vek.push_back(mypairs('z',p9));
vek.push_back(mypairs('s',p10));
vek.push_back(mypairs('D',p11));
vek.push_back(mypairs('t',p12));


shapes_p shapes[12]; // just declaration. Defined at the beginning of the code. an array  int *[2]
for (int i=0;i<pieces_in_order.size();++i){ // fills in shapes[] with pieces following the char list in pieces_in_order.
  for (int j=0;j<vek.size();++j){
   if (pieces_in_order[i]==vek[j].ch1){shapes[i]=vek[j].p;break;};
  }
};


int count_rows;
int count_columns;
string status;    // initialize the status: 'failed' or 'empty'
string status_m;  // needed at the very end.
// initialize the function  keep_count()
tie(count_rows,count_columns) = keep_count(0,-1,0,0);

vector<char> piece_label;    // it stores the labels after addition/deletion.
piece_label.reserve(12);

// BEGIN MAIN FOR LOOP!.
// from 0 to < 12 .
int max_v = 12;
for (int i=0; i < max_v;++i)
{
 char ch;
 switch (i)
 { 
 case 0: 
  ch=pieces_in_order[0];
  break;
 case 1:
  ch=pieces_in_order[1];
  break;
 case 2:
  ch=pieces_in_order[2];;
  break;
 case 3:
  ch=pieces_in_order[3];;
  break;
 case 4:
  ch=pieces_in_order[4];;
  break;
 case 5:
  ch=pieces_in_order[5];;
  break;
 case 6:
  ch=pieces_in_order[6];;
  break;
 case 7:
  ch=pieces_in_order[7];;
  break;
 case 8:
  ch=pieces_in_order[8];;
  break;
 case 9:
  ch=pieces_in_order[9];;
  break;
 case 10:
  ch=pieces_in_order[10];;
  break;
 case 11:
  ch=pieces_in_order[11];;
  break;
 } // end switch case.
 cout << endl;
 cout << " <<<<<<<<<<<<<<<<<<< >>>>>>>>>>>>>>>>>>>>>>" << endl;
 cout << " " << endl;
 cout << " Next piece is " << ch << " .Piece Number: "  << i << endl;
 print_board(board);
 int xx,yy;
 tie(xx,yy) = return_min_b(board);
 count_rows    = xx;
 count_columns = yy;
 cout << " Initial position to insert is..: " << count_rows << " -- " << count_columns << endl; 
 cout << endl;
 cout << " Minimum empty slot (x,y) " << xx << " --- " << yy << endl;
 count_rows=xx;
 count_columns=yy;
 vector<pieces>temp;
 temp   = fill(temp,shapes[i],ch); // temp is a vector<pieces>
 // fit_piece function tries to add the piece in the board.
 status = fit_piece(shapes[i],xx,yy,ch,board,-1,0,pieces_in_order,piece_label,piece_vek,piece_var,i);
 int   count_num = 0;
 while (status=="failed") // Infinite loop that is broken if it finds a solution or if return_pos() returns -1 .
 { // LOOP M1
    cout << "First Initial attempt to add " << ch << " failed " << endl;
    cout << "Count is... " << count_num;
    cout << " " << endl;
    tie(count_rows,count_columns) = keep_count(count_rows,count_columns,xx,yy);
    // keep track of the piece that will be deleted.
    last_added_piece =piece_label.back();
    // update_vector(piece_vek,board,last_added_piece); // small function that updated piece_vek.
    int n = piece_var.size();
    pos = return_pos(n,piece_var); // Call function that returns (backward loop) the i-th position of 
    cout << n << '\t'<< pos << "POS after first call" << endl;
    if (pos==-1){status="empty";status_m="empty";solutionlabel="No solution found, skip.";break;}
    cout << "First call to delete_n_pieces(): " << endl;
    int  check_size = piece_label.size() - (i-pos);
    if (check_size<0){status="empty";status_m="empty";solutionlabel="No solution found, skip.";break;}
    delete_n_pieces(piece_label,board,i-pos);
    vector<pieces> to_add;
    // piece_iterator function updates piece_var and reads the piece again in a new valid position.
    piece_iterator(to_add,piece_var,pos,pieces_in_order,board);
    char ch1 = pieces_in_order[pos];
    // update_vector(piece_vek,board,ch1);
    tie(xx,yy) = return_min_b(board);  // get min value again
    // Delete from piece_var all vectors after 'pos'.
    piece_var.erase(piece_var.begin()+pos+1,piece_var.end());
    piece_label.push_back(ch1);

    // Now start a for loop from pos+1 to i-1.
    if (pos==-1){break;};
    if ((pos+1)>=i){status_m="empty";} // status_m declared above.
    else {
     for (int j=pos+1;j<i;++j)
     {
      char ch2 = pieces_in_order[j];
      cout << "Inside second for loop..." << endl;
      cout << "Now try to add piece ... " << ch2 << endl;
      cout << "POS VALUE IS " << pos << endl;
      tie(xx,yy)    = return_min_b(board);  // get min value again
      tie(count_rows,count_columns) = keep_count(count_rows,count_columns,xx,yy);
      if (pos==-1){break;};
      status_m =fit_piece(shapes[j],xx,yy,ch2,board,-1,0,pieces_in_order,piece_label,piece_vek,piece_var,j);  
      cout << "status of piece " << ch2 << " inside the second loop is " << status_m << endl;
      if (status_m=="failed"){break;}
     }
    }
    // If status_m is still failed.
     while (status_m=="failed")
     { // while failed F2
      cout << "Inside while status_m loop: " << endl;
      last_added_piece =piece_label.back();
      //update_vector(piece_vek,board,last_added_piece); // small function that updated piece_vek.
      int n = piece_var.size();
      int pos = return_pos(n,piece_var); // Call function that returns the last position.
      std::cout << "second call to return_pos " << '\t' << pos << std::endl;
      if (pos==-1){status="failed";status_m="failed";solutionlabel="No solution found, skip.";break;}
      int ii = piece_label.size();   // size now is different
      if (pos!=-1){delete_n_pieces(piece_label,board,ii-pos);};
      vector<pieces> to_add;         // a vector that will hold a new piece with its char label.  
      // piece_iterator function updates piece_var and readds the piece again in a new valid position.
      piece_iterator(to_add,piece_var,pos,pieces_in_order,board);
      piece_var.erase(piece_var.begin()+pos+1,piece_var.end());
      char ch1 = pieces_in_order[pos];
      piece_label.push_back(ch1);
      for (int j=pos+1;j<i;++j){
       cout << "Start second while loop inside while status_m" << endl;
       char ch1 = pieces_in_order[j];
       cout << "Try to add... " << ch1 << endl;
       tie(xx,yy) = return_min_b(board);  // get min value again
       tie(count_rows,count_columns) = keep_count(count_rows,count_columns,xx,yy);
       status_m =fit_piece(shapes[j],xx,yy,ch1,board,-1,0,pieces_in_order,piece_label,piece_vek,piece_var,j);
       cout << "Status... " <<  status_m << endl;
       if (status_m=="failed") break;
       }
      if (status_m=="empty") break;
     } // while failed F2 
    if (status_m=="empty"){ 
    char ch2 = pieces_in_order[i];
    cout << "Now try to add piece 'i' " << ch2 << endl;
     cout << "POS VALUE IS " << pos << endl;
    tie(xx,yy) = return_min_b(board);  // get min value again
    tie(count_rows,count_columns) = keep_count(count_rows,count_columns,xx,yy);
    cout << "Minimum empty slot is at.. " << xx << '\t' << yy << endl;
    //reset_vector(piece_vek);
    status=fit_piece(shapes[i],xx,yy,ch2,board,-1,0,pieces_in_order,piece_label,piece_vek,piece_var,i);
    //print_board(board);
    }
   ++count_num;
   if (status=="empty"){break;} 
   if (pos==-1){break;};
 } // WHILE IF STATUS FAILED. //LOOP M1.
 if (pos==-1){break;}
if (pos==-1){break;}
} // end for loop

piece_label.clear();
pieces_in_order.clear();
reset_vector(piece_vek);
cout << " Final Solution: " << solutionlabel << endl;
if (pos!=-1 && solutionlabel=="Solution Found"){cout<<"Save solution"<<endl;print_board(board);save_to_file(board);};
if (solutionlabel=="No solution found, skip") solutionlabel="Solution found"; // reset string

cout << " ----- " << endl;
cout << "  " << endl;
cout << "  " << endl;
cout << "  " << endl;
cout << " Next piece " << endl;
cuenta=++cuenta;
cout << "Line Number " << cuenta << endl;
} // end getline

} // end main
