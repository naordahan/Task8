#include "Board.h"
#include <fstream>

using namespace std;
Board::Board(){
 length=0;
 b = new Spot*[length];
 
    for(int i = 0; i < length; i++){
        b[i] = new Spot[length]; //On heap
    }
        

}
// uint Board::size(){
//     uint a=this->length;
//     return a;
// }
Board::Board(uint length2){
length=length2;
 b = new Spot*[length];
 
    for(int i = 0; i < length; i++){
        b[i] = new Spot[length]; //On heap
    }
        
}

Board::Board(const Board& b2){
    length=b2.length;
    b=new Spot*[length];
    for(int i=0;i<length;i++)
    b[i]=new Spot[length];
    for(int i=0;i<length;i++)
    for(int j=0;j<length;j++){
        // b[i][j].c='*';
        char c2=b2.b[i][j].c;
        Spot t(i,j,c2);
        b[i][j]=t;
       
        
    }  
}

Spot& Board::operator[](Coordinate p2) const{
     if((p2.x>=length)||(p2.y>=length)){throw IllegalCoordinateException(p2.x,p2.y);}
    return b[p2.x][p2.y];
}

Board& Board::operator=(char in){
    if((in!='.')&&(in!='X')&&(in!='O')){throw IllegalCharException(in);}
    for(int i=0;i<length;i++)
    for(int j=0;j<length;j++){
        Spot t(i,j,in);
        b[i][j]=t;
       
        
    } 
 return *this;
}

Board& Board::operator=(const Board& b2){
    if(this==&b2){
        return *this;
        
    }
    
    for(int i=0; i<length; i++){
        delete[] b[i];
    } 
    
    delete[]b;
    length=b2.length;
    b=new Spot*[length];
    
    for(int i=0;i<length;i++){
        b[i]=new Spot[length];
        for(int j=0;j<length;j++){
            char c2=b2.b[i][j].c;
            Spot t(i,j,c2);
            b[i][j]=t;
        }  
    }
    return *this;
 }



ostream& operator<< (ostream& os, const Board& temp_b){
    for(int i=0;i<temp_b.length;i++){
        for(int j=0;j<temp_b.length;j++){
            os<<temp_b.b[i][j].c;
        }
        os<<endl;
    }
    return os;
    
}
istream& operator>> (istream& input, Board& b_out){
    string s;
    cin>>s;
    uint l=s.length();
    Board t{l};
    for(int i=0;i<l;i++){
        for(int j=0;j<l;j++){
            t.b[i][j].c=s[j];
        }
        cin>>s;
    }
    b_out=t;
    return input;
}
    
Board::~Board(){
    for (int i = 0; i < length; i++){
         delete[] b[i];
    }
    delete[] b;
        
}
 bool Board::operator==(const Board &b2) const{
        if(length!=b2.length){return false;}
        for(int i=0;i<length;i++){
         for(int j=0;j<length;j++){
             if(b[i][j]!=b2.b[i][j]){return false;}
         }
        }
        return true;
    }

    string Board::draw(int Pixels)
    {
    int numfile = 0;
    int cellSize = Pixels / this->size();
    while (true)
        {
        ifstream f(to_string(numfile) + ".ppm");
        if (!f.good()) // if stream is inturupted
            break;
        else
            numfile++;
    }
    string fname = to_string(numfile) + ".ppm";
    int size=this->length;
    int redC, greenC, blueC;
    const static int dimx =Pixels, dimy =Pixels ;
    RGB image[dimx*dimy];
    ofstream imageFile(fname, ios::out | ios::binary);
    //printing the grid+white background

  for (int j = 0; j < dimy; ++j)  {  // row
    for (int i = 0; i < dimx; ++i) { // column
    if(i%256==0||j%256==0)
    {
      image[dimx*j+i].red = (0);
      image[dimx*j+i].green = (0);
      image[dimx*i+j].blue = (0);
      }
    else{
      image[dimx*j+i].red = (255);
      image[dimx*j+i].green = (255);
      image[dimx*j+i].blue = (255);
      }
    } 
  }
  		for (int m = 0; m < this->size(); ++m)  {  // row
			for (int k = 0; k < this->size(); ++k) { // column
				char c = this->b[m][k].c;
				switch(c){
					case 'X':
						redC=234;
					    	greenC=0;
					    	blueC=59;
						break;
					case 'O':
					    	redC=0;
					   	greenC=163;
					   	blueC=82;
						break;
				}
				if(c == '.'){ //draws instead of dot a square
					
				}
				else if(c == 'X'){ //draws X
					int left=m*cellSize, right=k*cellSize;
					for (int i = (cellSize*0.10); i <(cellSize*0.90); ++i) {
						for (int j = 0; j <cellSize*0.01 ; ++j) {
						//left
						image[dimx*(i+left)+(i+(right))+j].red = redC;
						image[dimx*(i+left)+(i+(right))+j].green = greenC;
						image[dimx*(i+left)+(i+(right))+j].blue = blueC;
						//right
						image[dimx*(cellSize+left)-dimx*i+(i+right)+j].red = redC;
						image[dimx*(cellSize+left)-dimx*i+(i+right)+j].green = greenC;
						image[dimx*(cellSize+left)-dimx*i+(i+right)+j].blue = blueC;
						}
					}
				}
				
				else{// c == 'O', draws O			
				    int circle_radius=cellSize;
				    int xmid = cellSize/2.0;
				    int ymid = cellSize/2.0;
				    for (int i = 0; i <cellSize ; ++i) {
					for (int j = 0; j <cellSize ; ++j) {
						int tempx = i;
						int tempy = j;
						if(pow((((i-xmid)*(i-xmid)+(j-ymid)*(j-ymid)-(((cellSize)*0.45)*((cellSize)*0.45)))),2)<=pow(cellSize,2)){
							image[dimx*(i+m*cellSize)+(j+(k*cellSize))].green = redC;
							image[dimx*(i+m*cellSize)+(j+(k*cellSize))].red = greenC;
							image[dimx*(i+m*cellSize)+(j+(k*cellSize))].blue = blueC;
						}
					}
				    }
				}	
}
    

    }
    }

