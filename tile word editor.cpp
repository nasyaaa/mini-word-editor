#include <iostream>
#include <iomanip> //create pattern of tile
#include <fstream> //file load and save
#include <string>
#include <cstring>
#include <sstream> //splitting string to word
using namespace std;

void printTile(string board[],string& selection,string filename,int& dash);
void insertText(string board[],int& dash,int& tileExist,string undo[]);
void deleteText(string board[],int& tileExist,string undo[]);
void overText(string board[],int& tileExist,string undo[],int& dash);
void loadFile(string& filename,int& tileExist,string board[],string undo[]);
void saveFile(string& filename,string board[]);
void undoProgram(string undo[],string board[],int& tileExist);
void copyText(string board[],string clipBoard[],int tileExist,string undo[],int& counter);
void cutText(string board[],string clipBoard[],int& tileExist,string undo[],int& counter);
void pasteText(int& tileExist,string board[],string clipBoard[],string undo[],int counter);
void findText(string board[],string undo[],string& selection,string filename,int& dash);
void quitProgram();

int main()
{
	int tileExist=0,i=80,dash=4,counter;
	string selection,filename;
	string board[i] = {};
	string undo[i] = {};
	string clipBoard[10]={};	
	
	//initial screen
	cout << "\n* ===============================================================================================" << endl;
	cout << "\nFile name : NULL " << endl;
	
	cout << "\n[N]ew, [I]nsert, [D]elete, [O]verwrite, [L]oad, [S]ave, [C]opy, show-clip[B]oard, [X]cut, [P]aste, [F]ind, [U]ndo\n" <<
	"==> ";
	getline (cin,selection);
	cin.clear();
	cin.ignore(-1);
	
	if (selection == "q" || selection == "Q"){
		quitProgram();
		return 0;
	}
	
	if (selection == "b" || selection == "B"){ //show clipboard part
		bool tries = true;
				
		while (tries == true){				
			if (clipBoard[0]=="\0"){
				cout << "\nError : Empty Clipboard" << endl;
				tries = false;
			}	
			else{
				cout << "\n\nClipboard : ";
				for (int i=0;i<10;i++){
					cout << clipBoard[i] << " ";
				}
				cout << endl;
				tries = false;		
			}				
		}	
		tries = true;
		printTile(board,selection,filename,dash);			
	}
	
	while (selection != "n" && selection != "N" && selection != "L" && selection != "l" && selection != "b" && selection != "B"){
		
		cout << "\nError : Selection is not valid.Try again." << endl;
		cout << "\n[N]ew, [I]nsert, [D]elete, [O]verwrite, [L]oad, [S]ave, [C]opy, show-clip[B]oard, [X]cut, [P]aste, [F]ind, [U]ndo\n" <<
		"==> ";
		cin>>selection;
		cin.clear();
		cin.ignore(9999,'\n');
		
		if (selection == "q" || selection == "Q"){
			quitProgram();
			return 0;
		}
	}
	
	while (selection != "q" && selection != "Q"){
		
		if (selection == "n" || selection == "N"){
			
			cout << "\nNew file name ==> ";
			cin.sync();
			getline(cin,filename);
			printTile(board,selection,filename,dash);
			
			while (selection != "N" && selection != "n" && selection != "I" && selection != "i" && selection != "Q" && selection != "q" && selection != "L" && selection != "l" && selection != "B" && selection != "b")
			{
				
				cout << "\nError : Selection is not valid.Try again.";			
				cout << "\n[N]ew, [I]nsert, [D]elete, [O]verwrite, [L]oad, [S]ave, [C]opy, show-clip[B]oard, [X]cut, [P]aste, [F]ind, [U]ndo\n" <<
				"==> ";
				cin >> selection;
				cin.clear();
				cin.ignore(9999,'\n');
				
				if (selection == "q" || selection == "Q"){					
					quitProgram();
					return 0;
				}				
			}
		}
		
		else if (selection == "i" || selection == "I"){ //insert new word part
			insertText(board,dash,tileExist,undo);
			printTile(board,selection,filename,dash);
		}
		
		else if (selection == "d" || selection == "D"){ //delete part
			deleteText(board,tileExist,undo);
			printTile(board,selection,filename,dash);
		}
		
		else if (selection == "o" || selection == "o"){ //overwrite part
			overText(board,tileExist,undo,dash);
			printTile(board,selection,filename,dash);
		}
		
		else if (selection == "u" || selection == "U"){ //undo part
			undoProgram(undo,board,tileExist);
			printTile(board,selection,filename,dash);
		}
		
		else if (selection == "s" || selection == "S"){  //save to file part
			saveFile(filename,board);
			printTile(board,selection,filename,dash);
		}
		
		else if (selection == "l" || selection == "L"){  //load from existing file part
			loadFile(filename,tileExist,board,undo);
			printTile(board,selection,filename,dash);
		}
				
		else if (selection == "f" || selection == "F"){  //find word
			findText(board,undo,selection,filename,dash);
		}
		
		else if (selection == "b" || selection == "B"){ //show clipboard part
			bool tries = true;
					
			while (tries == true){				
				if (clipBoard[0]=="\0"){
					cout << "\nError : Empty Clipboard" << endl;
					tries = false;
				}	
				else{
					cout << "\n\nClipboard : ";
					for (int i=0;i<10;i++){
						cout << clipBoard[i] << " ";
					}
					cout << endl;
					tries = false;		
				}				
			}	
			tries = true;
			printTile(board,selection,filename,dash);			
		}
		
		else if (selection == "x" || selection == "X"){ //cut the word part
			cutText(board,clipBoard,tileExist,undo,counter);
			printTile(board,selection,filename,dash);
		}
		
		else if (selection == "c" || selection == "C"){ //copy part
			copyText(board,clipBoard,tileExist,undo,counter);
			printTile(board,selection,filename,dash);
		}
		
		else if (selection == "p" || selection == "P"){ //paste part
			pasteText(tileExist,board,clipBoard,undo,counter);
			printTile(board,selection,filename,dash);
		}
		
		else{
			cout << "\nError : Selection is not valid.Try again.";			
			cout << "\n[N]ew, [I]nsert, [D]elete, [O]verwrite, [L]oad, [S]ave, [C]opy, show-clip[B]oard, [X]cut, [P]aste, [F]ind, [U]ndo\n" <<
			"==> ";
			cin >> selection;
		}
	}	
	
	quitProgram();	
	return 0;
}

void insertText(string board[],int& dash,int& tileExist,string undo[]){
	int wordLength,numTile,c;
	string textEle;
	bool tries = false;
	
	for (int i=0;i<80;i++){
		undo[i] = board[i];
	}
	
	while (tries == false){			
		cout << "\n\nTile number ==> ";
		cin >> numTile ;
				
		if(cin.fail()){			
			cin.clear();
			cin.ignore(999,'\n');
			cout<<"Error : Invalid input.\n";
		}
		
		else if ( numTile < 1 || numTile > 80 ){
			
			cout << "Error : Tile number out of range." << endl;
		}	
		else if (numTile < 1 || numTile > tileExist+1){
			cout <<  "Error : Selection must follow sequence of tile number." << endl;	
		}
		else {
			tries = true;
		}
	}	
	tries = false;
	numTile--;
		
	while (tries==false){  //checking for 10 words part and ask for word
		
		char word[9999]={};
		int countWord=0;
		
		cout << "\nText ==> ";
		cin.sync();
		cin.getline(word,9999);
		
		for(int i = 0; word[i] != '\0'; i++){
			if (word[i] == ' '){
				++countWord;
			}
		}
		++countWord;
		c = (numTile + 1) + (countWord);
		
		if (countWord>10){
			cout << "\nError : Words inserted is out of range.Insert 1-10 words at a time.";
		}
		else if (c > 80){
			cout << "\nError : Words inserted have over reached the limit of tile." << endl;
		}
		else{
			tileExist = tileExist + (countWord);
			textEle=word;
			tries=true;
		}
	}	
		
	istringstream iss(textEle);		
	while (iss){		//split the string of word
		string split;
		iss >> split;
		if (split == "\0"){
			return;
		}
		for (int i=79 ; i>=numTile+1; i--){
				board[i] = board [i-1];
		}
		board[numTile] = split;
		++numTile;
		
				
		wordLength = split.length();
		if (dash <= wordLength){		
			dash = wordLength;
		}
	}
	
	return;
} 

void printTile(string board[],string& selection,string filename,int& dash){
	
	cout << "\n\n---------------------------------- new screen ----------------------------------" << endl;
	cout << "File Name : " << filename << endl;
		
	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "|   |";
	}

	for (int y = 1; y<9 ; y++){			
		cout <<setfill(' ') << setw(dash) << y << "|";	
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 00|";
	}

	for (int i = 0; i<8 ; i++){
		cout <<setfill(' ') << setw(dash) << board[i] << "|";
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 08|";
	}

	for (int i = 8; i<16 ; i++){
			cout <<setfill(' ') << setw(dash) << board[i] << "|";
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 16|";
	}

	for (int i = 16; i<24 ; i++){
		cout <<setfill(' ') << setw(dash) << board[i] << "|";
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 24|";
	}

	for (int i = 24; i<32 ; i++){
		cout <<setfill(' ') << setw(dash) << board[i] << "|";
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 32|";
	}

	for (int i = 32; i<40 ; i++){
		cout <<setfill(' ') << setw(dash) << board[i] << "|";
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 40|";
	}

	for (int i = 40; i<48 ; i++){
		cout <<setfill(' ') << setw(dash) << board[i] << "|";
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 48|";
	}

	for (int i = 48; i<56 ; i++){
		cout <<setfill(' ') << setw(dash) << board[i] << "|";
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 56|";
	}

	for (int i = 56; i<64 ; i++){
		cout <<setfill(' ') << setw(dash) << board[i] << "|";
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 64|";
	}

	for (int i = 64; i<72 ; i++){
		cout <<setfill(' ') << setw(dash) << board[i] << "|";
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 72|";
	}

	for (int i = 72; i<80 ; i++){
		cout <<setfill(' ') << setw(dash) << board[i] << "|";
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){
			cout <<setfill('-') << setw(dash) << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
	}
	
	cout << "\n[N]ew, [I]nsert, [D]elete, [O]verwrite, [L]oad, [S]ave, [C]opy, show-clip[B]oard, [X]cut, [P]aste, [F]ind, [U]ndo\n"
	<< "==> ";
	cin>>selection;
	cin.clear();
	cin.ignore(9999,'\n');

	return;
}

void deleteText(string board[],int& tileExist,string undo[]){
	bool tries = false;
	int fromTile,toTile,c;
	
	for (int i=0;i<80;i++){
		undo[i] = board[i];
	}
	
	while (tries == false){			
		cout << "\nFrom Tile number ==> ";
		cin >> fromTile ;
				
		if(cin.fail()){			
			cin.clear();
			cin.ignore(999,'\n');
			cout<<"Error : Invalid input.\n";
		}			
		else if (fromTile>tileExist || fromTile<1){
			cout <<  "Error : Error in tile number\n";	
		}
		else {
			tries = true;
		}	
		
		cout << "\nTo Tile number ==> ";
		cin >> toTile ;
				
		if(cin.fail()){			
			cin.clear();
			cin.ignore(999,'\n');
			cout<<"Error : Invalid input.\n";
		}
		else if (toTile<fromTile||toTile>tileExist){
			cout <<  "Error : Error in tile number\n";	
		}
		
		c=toTile-fromTile;
		
		if (c>10){
			cout << "Error : Cannot be more than 10 tiles";
		}
		else {
			tries = true;
		}		
	}	
	tries = false;
	fromTile--;
	toTile--;	
	while (c >=0){
		for (int i=fromTile; i<79; i++){
			board[i] = board [i+1];
		}
		c--;
		tileExist--;
	}
			
	return;
}

//created by : nursyawana

void overText(string board[],int& tileExist,string undo[],int& dash){
	bool tries = false;
	int wordLength,numTile,c;
	string textEle;
	
	for (int i=0;i<80;i++){
		undo[i] = board[i];
	}
	
	while (tries == false){			
		cout << "\n\nTile number ==> ";
		cin >> numTile ;
				
		if(cin.fail()){			
			cin.clear();
			cin.ignore(999,'\n');
			cout<<"Error : Invalid input.\n";
		}
		
		else if ( numTile < 1 || numTile > 80 ){
			
			cout << "Error : Tile number out of range.\n" << endl;
		}	
		else if (numTile < 1 || numTile > tileExist){
			cout <<  "Error : Overwrite only happen on existed tile\n";	
		}
		else {
			tries = true;
		}
	}	
	tries = false;
	numTile--;
	
	while (tries==false){
		
		char word[9999]={};
		int countWord=0;
		
		cout << "\nText ==> ";
		cin.sync();
		cin.getline(word,9999);		
				
		for(int i = 0; word[i] != '\0'; i++){
			if (word[i] == ' '){
				++countWord;
			}
		}
		++countWord;
		c = numTile + countWord;
		if (countWord>10){
			cout << "\nError : Words inserted is out of range.Insert 1-10 words at a time." << endl;
		}
		else if (c > tileExist){
			cout << "\nError : Words inserted have over reached the limit of existed tile." << endl;
		}
		else{
			textEle=word;
			tries=true;
		}
	}
	
	istringstream iss(textEle);  //split string into one-by one word
	while (iss){		
		string split;
		iss >> split;
		if (split != "\0"){ 
			board[numTile] = split;
		}
		++numTile;		
		
		wordLength = split.length();
		if (dash <= wordLength){		
		dash = wordLength;
		}
	}
	
	return;
}

void loadFile(string& filename,int& tileExist,string board[],string undo[]){	
	bool tries = false;
	int loadtileExist=0,wordCount=0;
	string loadBoard[80]={};
	string fileLoad,newWordExist;
	
	for (int i=0;i<80;i++){
		undo[i] = board[i];
	}
	
	ifstream infile;	
	while (tries == false){ //check if there is any file exist
		cout << "\nFile Name => ";
		cin.sync();
		getline(cin,fileLoad);
		infile.open(fileLoad.c_str());
		if (infile.is_open())
		{		
			for (int i=0;i<80;i++){
				infile >> loadBoard[i];
			}			
			tries = true;
		}
		else {
			cout << "Error : File not found for load operation." << endl;
			return;
		}
	}	
	infile.close();
	
	infile.open(fileLoad.c_str());
	if (infile.is_open())
	{		
		while (infile >> newWordExist){ 
			++wordCount;
		}			
	}	
	infile.close();
	
	cout << "\n\n---------------------------------- File for reference : " << fileLoad <<  "----------------------------------" << endl;
	for (int i=0;i<80;i++){
		cout << loadBoard[i] << " ";
	}
	cout << endl;
	
	for (int i=0;i<80;i++){
		board[i]=loadBoard[i];
	}	
	tileExist = wordCount; //update number of tile that has word
	
	return;
} 

void saveFile(string& filename,string board[]){
	ofstream file;
	
	cout << "\nFile name (enter " << filename << ") ==> " << endl;
	cin.sync();
	getline(cin,filename);
	
	file.open(filename.c_str());
	if (file.fail()){
		cout << "Error : Input opening file failed!" << endl;
		return;
	}
	
	if (file.is_open())
	{
		for (int i=0;i<80;i++){
			file << board[i] << "  ";
		}
	}	
	file.close();	
	cout << "File saved." << endl;
	
	cout << "\n\n---------------------------------- File for reference : " << filename <<  "----------------------------------" << endl;
	for (int i=0;i<80;i++){
		cout << board[i] << " ";
	}
	cout << endl;
	
	return ;
} 

//created by : nursyawana

void undoProgram(string undo[],string board[],int& tileExist){
	int undoTileExist=0;
	
	//set the current tile to undo tile
	for (int i=0;i<80;i++){
		board[i] = undo[i];
		if (undo[i]!= "\0"){//count the undo existing tile
			++undoTileExist;
		}
		
	}	
	tileExist=undoTileExist;
	
	return;
}

void copyText(string board[],string clipBoard[],int tileExist,string undo[],int& counter){
	int fromTile,toTile,j=0;
	bool tries=false;
	
	for (int i=0;i<80;i++){
		undo[i] = board[i];
	}
	
	while (tries == false){			
		cout << "\nFrom Tile number ==> ";
		cin >> fromTile ;
				
		if(cin.fail()){			
			cin.clear();
			cin.ignore(999,'\n');
			cout<<"Error : Invalid input.\n";
		}			
		else if (fromTile>tileExist || fromTile<1){
			cout <<  "Error : Error in tile number\n";	
		}
		else {
			tries = true;
		}		
		
		cout << "\nTo Tile number ==> ";
		cin >> toTile ;
				
		if(cin.fail()){			
			cin.clear();
			cin.ignore(999,'\n');
			cout<<"Error : Invalid input.\n";
		}
		else if (toTile<fromTile||toTile>tileExist){
			cout <<  "Error : Error in tile number\n";	
		}
		
		counter=toTile-fromTile;
		
		if (counter>10){
			cout << "Error : Cannot copy more than 10 tiles";
		}
		else {
			tries = true;
		}		
	}	
	tries = false;
	fromTile--;
	toTile--;
	
	for (int i=0;i<10;i++){ //empty the clipboard first before filling in
		clipBoard[i]="  ";
	}
	
	while (j<counter){	
		for (int i=fromTile;i<=toTile;i++){		
			clipBoard[j]=board[i];
			j++;	
		}
	}	
	
	return;	
}

void cutText(string board[],string clipBoard[],int& tileExist,string undo[],int& counter){
	
	int fromTile,toTile,c,j=0;
	bool tries=false;
	
	for (int i=0;i<80;i++){
		undo[i] = board[i];
	}
	
	while (tries == false){			
		cout << "\nFrom Tile number ==> ";
		cin >> fromTile ;
				
		if(cin.fail()){			
			cin.clear();
			cin.ignore(999,'\n');
			cout<<"Error : Invalid input.\n";
		}			
		else if (fromTile>tileExist || fromTile<1){
			cout <<  "Error : Error in tile number\n";	
		}
		else {
			tries = true;
		}		
		
		cout << "\nTo Tile number ==> ";
		cin >> toTile ;
				
		if(cin.fail()){			
			cin.clear();
			cin.ignore(999,'\n');
			cout<<"Error : Invalid input.\n";
		}
		else if (toTile<fromTile||toTile>tileExist){
			cout <<  "Error : Error in tile number\n";	
		}
		
		counter = toTile-fromTile;		
		if (counter>10){
			cout << "Error : Cannot cut more than 10 tiles";
		}
		else {
			tries = true;
		}		
	}	
	tries = false;
	fromTile--;
	toTile--;

	for (int i=0;i<10;i++){ //empty the clipboard first before filling in
		clipBoard[i]="  ";
	}
	
	while (j<counter){	//tranfer the cut word to clipboard
		for (int i=fromTile;i<=toTile;i++){		
			clipBoard[j]=board[i];
			j++;	
		}
	}
	
	c = counter;	
	while (c >=0){ //shifting and delete cut word
		for (int i=fromTile; i<79; i++){
			board[i] = board [i+1];
		}
		c--;
		tileExist--;
	}
	
	return;
}

//created by : nursyawana

void pasteText(int& tileExist,string board[],string clipBoard[],string undo[],int counter){
	int numTile,c=counter,j=0;
	bool tries=false;
	
	for (int i=0;i<80;i++){
		undo[i] = board[i];
	}
	
	if (clipBoard[0]=="\0"){
		cout << "\nError : Empty Clipboard" << endl;
		return;
	}	
	
	while (tries == false){			
		cout << "\nTile number ==> ";
		cin >> numTile;
		
		if(cin.fail()){			
			cin.clear();
			cin.ignore(999,'\n');
			cout<<"Error : Invalid input.\n";
		}			
		else if ((numTile < 1) || (numTile > tileExist+1)){
			cout <<  "Error : Selection must follow sequence of tile number.\n";	
		}
		else if ((counter+numTile)>80){ 
			cout << "Error : Limit of tile has overreached.\n";
		}
		else {
			tries = true;
		}
	}	
	tries = false;
	numTile--;
	
	while (c>=0){
		for (int i=79 ; i>=numTile+1; i--){
			board[i] = board [i-1];
			tileExist++;
		}
		c--;
	}
	
	int i = numTile;	
	while (j<=counter){
		board[i]=clipBoard[j];
		i++;
		j++;
	}
	
	return;
}

void findText(string board[],string undo[],string& selection,string filename,int& dash){
	string find;
	string findBoard[80]={};
	int i=0,c;
	bool found=false;
	
	for (int i=0;i<80;i++){
		undo[i] = board[i];
		findBoard[i]=board[i];
	}
	
	cout << "\n\nEnter text to find : ";
	cin >> find;
	cin.clear();
	cin.ignore();
	
	while ((!found) && i<80){ //check if array exist or not at array
		if (find == findBoard[i]){
			found = true;
		}
		else{
			i++;
		}
	}
	
	if (!found){
		cout << "Error : Word not exist!\n";
		return;
	}
	
	cout << "\n\n---------------------------------- new screen ----------------------------------" << endl;
	cout << "File Name : " << filename << endl;
	
	//print array that has the found word in tiles form	
	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "|   |";
	}

	for (int y = 1; y<9 ; y++){			
		cout <<setfill(' ') << setw(dash) << y << "|";	
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 00|";
	}
	
	for (int i = 0; i<8 ; i++){
		if (find == findBoard[i]){
			cout <<setfill(' ') << setw(dash) << findBoard[i] << "=";			
		}
		else{
			cout <<setfill(' ') << setw(dash) << board[i] << "|";
		}	
	}
	
	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 08|";
	}
	
	for (int i = 8; i<16 ; i++){
		if (find == findBoard[i]){
			cout <<setfill(' ') << setw(dash) << findBoard[i] << "=";			
		}
		else{
			cout <<setfill(' ') << setw(dash) << board[i] << "|";
		}	
	}	
	
	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 16|";
	}
	
	for (int i = 16; i<24 ; i++){
		if (find == findBoard[i]){
			cout <<setfill(' ') << setw(dash) << findBoard[i] << "=";			
		}
		else{
			cout <<setfill(' ') << setw(dash) << board[i] << "|";
		}	
	}
	
	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 24|";
	}
	
	for (int i = 24; i<32 ; i++){
		if (find == findBoard[i]){
			cout <<setfill(' ') << setw(dash) << findBoard[i] << "=";			
		}
		else{
			cout <<setfill(' ') << setw(dash) << board[i] << "|";
		}	
	}
	
	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 32|";
	}
	
	for (int i = 32; i<40 ; i++){
		if (find == findBoard[i]){
			cout <<setfill(' ') << setw(dash) << findBoard[i] << "=";			
		}
		else{
			cout <<setfill(' ') << setw(dash) << board[i] << "|";
		}	
	}
	
	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 40|";
	}
	
	for (int i = 40; i<48 ; i++){
		if (find == findBoard[i]){
			cout <<setfill(' ') << setw(dash) << findBoard[i] << "=";			
		}
		else{
			cout <<setfill(' ') << setw(dash) << board[i] << "|";
		}	
	}
	
	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 48|";
	}
	
	for (int i = 48; i<56 ; i++){
		if (find == findBoard[i]){
			cout <<setfill(' ') << setw(dash) << findBoard[i] << "=";			
		}
		else{
			cout <<setfill(' ') << setw(dash) << board[i] << "|";
		}	
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 56|";
	}
	
	for (int i = 56; i<64 ; i++){
		if (find == findBoard[i]){
			cout <<setfill(' ') << setw(dash) << findBoard[i] << "=";			
		}
		else{
			cout <<setfill(' ') << setw(dash) << board[i] << "|";
		}	
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 64|";
	}
	
	for (int i = 64; i<72 ; i++){
		if (find == findBoard[i]){
			cout <<setfill(' ') << setw(dash) << findBoard[i] << "=";			
		}
		else{
			cout <<setfill(' ') << setw(dash) << board[i] << "|";
		}	
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){		
			cout <<setfill('-') << setw(dash)  << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
		cout << "| 72|";
	}
	
	for (int i = 72; i<80 ; i++){
		if (find == findBoard[i]){
			cout <<setfill(' ') << setw(dash) << findBoard[i] << "=";			
		}
		else{
			cout <<setfill(' ') << setw(dash) << board[i] << "|";
		}	
	}

	for (int x = 1 ; x<2 ; x++) {		
		cout << "\n|---|--";
		for (int y=7  ; y > 0 ; y--){
			cout <<setfill('-') << setw(dash) << "-+-" << setw(1) << "-";
		}
		cout <<setfill('-') << setw(dash-1) << "|" << setw(1);
		cout << endl;
	}
	
	cout << "\n[N]ew, [I]nsert, [D]elete, [O]verwrite, [L]oad, [S]ave, [C]opy, show-clip[B]oard, [X]cut, [P]aste, [F]ind, [U]ndo\n"
	<< "==> ";
	cin >> selection;
	cin.clear();
	cin.ignore(9999,'\n');
	
	return;
}
 
void quitProgram(){
	cout << "\nThank you for using this program.Have a nice day!";
	cout << "\n---------------------------------- new screen ----------------------------------" << endl;
	
	return;
}

