/* REVERSI OYUNU'NU CLASS VE VEKTORLERLE YAZMA...
 * File:   main.cpp
 * Author: tayyip(131044054)
 *
 * Created on 14 Kasım 2015 Cumartesi, 13:43
 */
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

class Cell
{
public:
    Cell();
    
    void set_X(int a);
    void set_Y(int b);
    void set_member(char c);
    void set3(int a,int b,char c);
    
    int get_X()const{return X;}
    int get_Y()const{return Y;}
    char get_member()const{return member;} 
private:
    int X;
    int Y;
    char member;
};

class Reversi
{
public:
    Reversi();
    Reversi(int x);
    Reversi(int x,int y);
    
    vector<Cell>W;
    
    void tablo_doldur();
    void ekrana_yazma();
    void dosyaya_yazma();
    void foo();
    void kayitli_oyun();
    
    int play();
    int play(int x,int y);
    
    void playGame();
    char kullanici_degistirme(char player);
    
    int current_height();
    int current_width();
    
    void set_satir_sutun(int x,int y);

    void game();
    bool game_ended(int ilk,int son);
    
    char kim_kazandi();
    int yerdegis(int ilk ,char son,char oyuncu_tasi,int yazsin);
    static int living_cells();
    
private:
    int satir,sutun;
    vector<vector<Cell> >gameCells;
};
static int counter;//Oyunda bulunan 'x-o' lari sayan statik degisken

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
int main() 
{

    Reversi game1(6,6);
    /*DOSYADAN OKUMA YAPIP EKRANA BASAN FONK. KULLANMAK ICIN YORUMU KALDIRIN*/
    //game1.kayitli_oyun();
    
    game1.playGame();
    
    return 0;
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//Cell sinifi fonksiyonlarim
Cell::Cell()
{
    X=0;
    Y=0;
}
void Cell::set3(int a, int b, char c)
{
    X=a;
    Y=b;
    member=c;
}

void Cell::set_X(int a)
{
    X=a;
}

void Cell::set_Y(int b)
{
    Y=b;
}

void Cell::set_member(char c)
{
    member=c;
}
/*----------------------------------------------------------------------------*/
//Reversi sinifi fonksiyonlarim
Reversi::Reversi()
{
  satir=10;
  sutun=10;
  W.resize(sutun);
  gameCells.resize(satir,W);  
}

Reversi::Reversi(int x)
{
  satir=x;
  sutun=10;
  W.resize(sutun);
  gameCells.resize(satir,W);  
}

Reversi::Reversi(int x,int y)
{
  satir=x;
  sutun=y;
  W.resize(sutun);
  gameCells.resize(satir,W);  
}
//STATIK OLARAK YASAYAN HUCRE SAYISI
int Reversi::living_cells()
{
    counter++;   
    cout<<"YASAYAN HUCRE SAYISI==>"<<counter<<endl;
    return counter;
}
//SATIR VE SUTUN DEGISTIREN FONKSIYON
void Reversi::set_satir_sutun(int x,int y)
{
  gameCells.erase(gameCells.begin(),gameCells.end());   
  satir=x;
  sutun=y;
  W.resize(sutun);
  gameCells.resize(satir,W);
 
}
//BASLANGIC DEGERLERINI KOYAN FONKSIYON
void Reversi::foo()
{
   int a,b;
   a=(satir/2)-1;	//Baslangic degerlerini koyma.
   b=satir/2;  
   gameCells[a][a].set_member('X');     
   gameCells[a][b].set_member('O');
   gameCells[b][a].set_member('O');
   gameCells[b][b].set_member('X');
}
//GAMECELLS IN BOYU
int Reversi::current_height()
{
    return (gameCells.size());
}
//GAMECELLS IN GENISLIGI
int Reversi::current_width()
{
    return (W.size());
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//DOSYAYA YAZILAN OYUNU OKUYUP GAMECELLS E DOLDURAN FONKSIYON
void::Reversi::kayitli_oyun()
{   
    char c;
    ifstream in_file;
    in_file.open("out.txt");   
    
    if(in_file.fail()){ 
        cerr<<"HATA DOSYA ACILAMADI"<<endl;
        exit(1);}
    
    
    c=in_file.get();
    while(in_file.good()){
        cout<<c;
        c=in_file.get();} 
    
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//TABLOYU NOKTALARLA DOLDURAN FONKSIYON
void Reversi::tablo_doldur()
{
    counter+=4;
    cout<<"\nKULLANICI:O"<<endl;
    cout<<"BILGISAYAR:X"<<endl;    
    cout<<"SATIR="<<current_height()<<endl;
    cout<<"SUTUN="<<current_width()<<endl;
    cout<<endl; 
    for(int i=0;i<current_height();++i){
        for(int j=0;j<current_width();++j)
            gameCells[i][j].set3(i,j,'.');
            } 
    foo();
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//VERILERI EKRANA YAZAN FONKSIYON
void Reversi::ekrana_yazma()
{
    char harf1,harf2='A';
    harf1=harf2;
    
    cout<<"   ";	//(0,0) noktasini bos biraktik ve ilk satiri yazdirdim.
    for(harf2;harf2<harf1+sutun;++harf2)
	cout<<" "<<harf2<<" ";
    cout<<"\n";


    for(int i=0;i<current_height();i++){
	if(i<9)
            cout<<""<<i+1<<"  ";	
	else
            cout<<""<<i+1<<" ";
        for(int j=0;j<current_width();j++)
            cout<<" "<<gameCells[i][j].get_member()<<" ";
	cout<<"\n";}   
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//VERILERI DOSYAYA YAZAN FONKSIYON
void Reversi::dosyaya_yazma()
{
    ofstream on_file;
    on_file.open("out.txt");   
    if(on_file.fail()){ 
        cerr<<"HATA DOSYA ACILAMADI"<<endl;
        exit(1);}

    char harf1,harf2='A';
    harf1=harf2;
    
    on_file<<"   "; 	//(0,0) noktasini bos biraktik ve ilk satiri yazdirdim.

    for(harf2;harf2<harf1+sutun;++harf2)
        on_file<<" "<<harf2<<" ";
    on_file<<"\n";

    for(int i=0;i<current_height();i++){
	if(i<9)
            on_file<<""<<i+1<<"  ";	
	else
            on_file<<""<<i+1<<" ";
        for(int j=0;j<current_width();j++)
            on_file<<" "<<gameCells[i][j].get_member()<<" ";

       on_file<<"\n";}   
   
    on_file.close();
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//BILGISAYAR ICIN MUSAIT YER VARMI DIYE BAKAN VE VARSA O NOKTAYI 'X' YAPAN FONKSIYON
int Reversi::play()
{   
    //yerdegis fonk. cagiriken son parametre olarak burada 1 gonderdim.cunku hem bakmasini hemde yazmasini istiyorum.
    for(int i=0;i<current_height();++i){
        for (int j=0;j<current_width();++j){
            if(gameCells[i][j].get_member()=='.' && yerdegis(i,j,'X',1)!=0){
                cout<<endl;
		cout<<"\nBILGISAYARIN HAMLESI:"<<endl;
                cout<<i+1<<char(j+65)<<endl;
		ekrana_yazma();
                living_cells();
		return 0;}}}
    return -1;
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//KULLANICI ICIN MUSAIT YER VARMI DIYE BAKAN FONKSIYON
int Reversi::play(int x, int y)
{
    int z;
    for(int i=0;i<current_height();++i){
	for (int j=0;j<current_width();++j){
            if(gameCells[i][j].get_member()=='.'){
		z=yerdegis(i,j,'O',0);//son parametre olarak burada 0 gonderdim.cunku sadece bakmasini 
		if(z!=0)             //istiyorum.yazmasini istemiyorum.                   
                    return 0;}}}
		
    return -1;
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//KULLANICI DEGISTIREN FONKSIYON
char Reversi::kullanici_degistirme(char player)
{
    if(player=='X'){
        player='O';
        return player;}
    else{
        player='X';
        return player;}
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//OYUNDA KAZANAN VARSA ONA GORE DEGER DONDEREN FONKSIYON
char Reversi::kim_kazandi()
{
    int x=0,o=0,a=0,b=0;
    for(int i=0;i<current_height();i++){									
        for(int j=0;j<current_width();j++){
            if(gameCells[i][j].get_member()=='X')
		a++;
            else if(gameCells[i][j].get_member()=='O')
		b++;}}
	
    while((a+b)==current_height()*current_width())
    {
        for(int i=0;i<current_height();i++){
            for(int j=0;j<current_width();j++){
                if(gameCells[i][j].get_member()=='X')
                    x++;
		else if(gameCells[i][j].get_member()=='O')
                    o++;}}

	cout<<"OYUN BITTI:\nX==>"<<x<<""<<endl;
	cout<<"\nO==>"<<o<<"\n\n";
	if(x>o) 
		return 'X';
	else if (o>x)
		return 'O';
	else if(o==x)
		return 'B';	
    }
	return 'N';
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*bize verilen nokta ornegin m,n noktasi ise bizim===>
(n-1),(n+1),(m-1),(m+1),(m-1,n-1),(m-1,n+1),(m+1,n+1),(m+1,n-1) yani;
(SOL),(SAG),(UST),(ALT),(SOL UST),(SAG UST),(SAG ALT),(SOL ALT) noktalarina 
bakmamiz gerekmektedir.*/
int Reversi::yerdegis(int ilk ,char son, char oyuncu_tasi, int yazsin)
{
    int yeninokta2,buldumu=0,cevirme=0,sabit;
   
//..............................................................................
//............................SAG TARAFINA BAKIYOR..............................
//..............................................................................
    for(int yeninokta=son+1;gameCells[ilk][yeninokta].get_member()!='.' &&yeninokta<satir+1 && buldumu==0;yeninokta++)
	{           
        if(gameCells[ilk][yeninokta].get_member()==oyuncu_tasi){		 	
            sabit=son+1;
            while(sabit<yeninokta)
            {
		if(yazsin==1) {
                    gameCells[ilk][sabit].set_member(oyuncu_tasi);
                    gameCells[ilk][son].set_member(oyuncu_tasi);
                }
                sabit++;
                cevirme++;         
            }
		buldumu=1;}
	}

//..............................................................................
//.........................SOL TARAFINA BAKIYOR.................................
//..............................................................................
    buldumu=0;
    for(int yeninokta=son-1;gameCells[ilk][yeninokta].get_member()!='.' &&yeninokta>=0 && buldumu==0;yeninokta--)
	{
	if(gameCells[ilk][yeninokta].get_member()==oyuncu_tasi){
            sabit=son-1;         
            while(sabit>yeninokta)
            {
		if(yazsin==1){
		gameCells[ilk][sabit].set_member(oyuncu_tasi);
                gameCells[ilk][son].set_member(oyuncu_tasi);
                }
                sabit--;
                cevirme++;
            }
		buldumu=1;}
	} 

//..............................................................................
//..........................ALT TARAFINA BAKIYOR................................
//.............................................................................. 
    buldumu=0;
    for(int yeninokta=ilk+1;yeninokta<satir && buldumu==0;yeninokta++)
    {	
        
        if(gameCells[yeninokta][son].get_member()=='.')
            buldumu=99;
        
        else if(gameCells[yeninokta][son].get_member()==oyuncu_tasi){
            sabit=ilk+1;
             
            while(sabit<yeninokta)
            {
                if(yazsin==1) {    
                  gameCells[sabit][son].set_member(oyuncu_tasi);
                  gameCells[ilk][son].set_member(oyuncu_tasi);}
                
                sabit++;
		cevirme++;
               
            }
             
            buldumu=1;}
    }
//..............................................................................
//.........................UST TARAFINA BAKIYOR.................................
//..............................................................................
    buldumu=0;
    for(int yeninokta=ilk-1; yeninokta>=0 && buldumu==0;yeninokta--)
    {
        if(gameCells[yeninokta][son].get_member()=='.')
            buldumu=99;
        
        else if(gameCells[yeninokta][son].get_member()==oyuncu_tasi){
            sabit=ilk-1;
            while(sabit>yeninokta)
            {
                if(yazsin==1){
                  gameCells[sabit][son].set_member(oyuncu_tasi);
                  gameCells[ilk][son].set_member(oyuncu_tasi);
            }
                sabit--;
                cevirme++;
            }
            buldumu=1;}
    } 
//..............................................................................
//.........................SOL ALT CAPRAZ TARAFINA BAKIYOR......................
//..............................................................................
    buldumu=0;
    for(int yeninokta1=ilk+1,yeninokta2=son-1;
	yeninokta1<satir && yeninokta2>=0 && buldumu==0;
	yeninokta1++,yeninokta2--){
       
        if(gameCells[yeninokta1][yeninokta2].get_member()=='.')
            buldumu=99;
        
        else if(gameCells[yeninokta1][yeninokta2].get_member()==oyuncu_tasi){
            int sabit2=son-1;
            sabit=ilk+1;
            while(yeninokta1>sabit && sabit2>yeninokta2)
            {
                if(yazsin==1){
		gameCells[sabit][sabit2].set_member(oyuncu_tasi);
                gameCells[ilk][son].set_member(oyuncu_tasi);}
		sabit++;
		sabit2--;
		cevirme++;
            }
		buldumu=1;}
    }   
//..............................................................................
//........................SAG ALT CAPRAZ TARAFINA BAKIYOR.......................
//..............................................................................
    buldumu=0;
    for(int yeninokta1=ilk+1,yeninokta2=son+1;
	yeninokta1<satir && yeninokta2<sutun && buldumu==0;
	yeninokta1++,yeninokta2++){

        if(gameCells[yeninokta1][yeninokta2].get_member()=='.')
            buldumu=99;
        
        else if(gameCells[yeninokta1][yeninokta2].get_member()==oyuncu_tasi){
            sabit=ilk+1;
            int sabit2=son+1;
            while(yeninokta1>sabit && yeninokta2>sabit2)
            {
		if(yazsin==1){
		gameCells[sabit][sabit2].set_member(oyuncu_tasi);
                gameCells[ilk][son].set_member(oyuncu_tasi);}
		sabit++;
		sabit2++;
		cevirme++;
            }
		buldumu=1;}}
//..............................................................................
//.......................SOL UST CAPRAZ TARAFINA BAKIYOR........................
//..............................................................................
    buldumu=0;
    for(int yeninokta1=ilk-1,yeninokta2=son-1;
	yeninokta1>=0 && yeninokta2>=0 && buldumu==0;
	yeninokta1--,yeninokta2--){
        
        if(gameCells[yeninokta1][yeninokta2].get_member()=='.')
            buldumu=99;
        
	else if(gameCells[yeninokta1][yeninokta2].get_member()==oyuncu_tasi){
            sabit=ilk-1;
            int sabit2=son-1;
            while(yeninokta1<sabit && yeninokta2<sabit2)
            {
		if(yazsin==1){
		gameCells[sabit][sabit2].set_member(oyuncu_tasi);
                gameCells[ilk][son].set_member(oyuncu_tasi);}
		sabit--;
		sabit2--;
		cevirme++;
            }
		buldumu=1;}}
//..............................................................................
//.....................SAG UST CAPRAZ TARAFINA BAKIYOR..........................
//..............................................................................
    buldumu=0;
    for(int yeninokta1=ilk-1,yeninokta2=son+1;
	yeninokta1>=0 && yeninokta2<sutun && buldumu==0;
	yeninokta1--,yeninokta2++){
        
        if(gameCells[yeninokta1][yeninokta2].get_member()=='.')
            buldumu=99;
        
	else if(gameCells[yeninokta1][yeninokta2].get_member()==oyuncu_tasi){
            sabit=ilk-1;
            int sabit2=son+1;
            while(yeninokta1<sabit && yeninokta2>sabit2)
            {
                if(yazsin==1){
		gameCells[sabit][sabit2].set_member(oyuncu_tasi);
                gameCells[ilk][son].set_member(oyuncu_tasi);}
		sabit2++;
		sabit--;
		cevirme++;
            }
		buldumu=1;}}    
return cevirme;
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//OYUNUN BITIP BITMEDIGINI KONTROL EDEN FONKSIYON
bool Reversi::game_ended(int ilk,int son)
{  
    int a=0,b=0;   
    if(play(ilk,son)==-1 && play()==-1)
    {
	cout<<"\nHER IKI  KULLANICININDA OYNAYACAK YERI KALMADI\n";
        
	for(int i=0;i<current_height();i++){									
            for(int j=0;j<current_width();j++){
		if(gameCells[i][j].get_member()=='X'){
                    a++;}
		else if(gameCells[i][j].get_member()=='O')
                    b++;}}	

	cout<<"OYUN BITTI:\nX==>"<<a<<""<<endl;
	cout<<"\nO==>"<<b<<"\n\n";
	if(a>b)
            cout<<"\nX OYUNCUSU KAZANDI.\n";
	else if (b>a)
            cout<<"\nO OYUNCUSU KAZANDI.\n";
	else if(b==a)
            cout<<"\nOYUN BERABERE BITTI.\n";
        
        return true;
    }   
    return false;
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//OYUNUN OYNANDIGI FONKSIYON
void Reversi::playGame()
{
    int ilk,sayac,mumkun,a=0,b=0,oyun,x,y;
    char son,galip_var_mi,player,mult,kayit;

    char tercih;    	
    cout<<"TABLO BOYUTLARINI DEGISTIRMEK ISTERMISINIZ:(EVET(E-e)---HAYIR(H-h))"<<endl;
    cin>>tercih;
        
    if(tercih=='E'||tercih=='e')
    {
        cout<<"LUTFEN TABLO BOYUTLARINI GIRINIZ:(ORNEGIN:4*4,4*6,8*12......)\n";
        cout<<"TABLO BOYUTUNU EN AZ 3*3 OLARAK GIRINIZ:\n";
        cin>>x>>mult>>y;
        if(isalpha(x)!=0 || isalpha(y)!=0){//KULLANICI 2 TANE SAYI GIRMEZSE HATA VERIP CIKIYOR
            cerr<<"HATALI GIRIS YAPTINIZ\n"<<endl;       
            exit(1);}
                
        if(x<3 || y<3){//TABLO BOYUTLARI 3 TEN KUCUK OLURSA HATA VERIP CIKIYOR
            cerr<<"HATALI GIRIS YAPTINIZ\n"<<endl;       
            exit(1);} 
        else
            set_satir_sutun(x,y);
    }

    else if(tercih!='E'&&tercih!='e'&&tercih!='H'&&tercih!='h'){
        cerr<<"HATALI GIRIS YAPTINIZ\n"<<endl;       
        exit(1);} 
    
    cout<<"HOSGELDINIZ:\n"<<endl;
    cout<<"X'IN BASLAMASI ICIN 1 "<<endl;
    cout<<"O'NUN BASLAMASINI ICIN 0 E BASINIZ.\n"<<endl;   //OYUNA ONCE KIMIN BASLICAGINI SORUYORUM...       
    cin>>oyun;
    
    if(oyun==1)
        player='X';
    else if(oyun==0)
        player='O';
    else{
        cerr<<"HATALI GIRIS YAPTINIZ\n"<<endl;       
        exit(1);}
    
    tablo_doldur();
    ekrana_yazma();
  
/******************************************************************************/
/************BILGISAYAR KULLANICI ARASINDA OYNANIYORSA*************************/
/******************************************************************************/
    //break komutunu alana kadar devam edecek.
    cout<<endl;   
    while(1) 
    {
    dosyaya_yazma();    
    //Her 2 kullanicida tas alamiyorsa taslari say ve oyunu bitir.   
    if(game_ended(ilk,son)==true)
	break;
    
    //Kullanici X iken.
    else if(player=='X'){
        sayac=play();
	if(sayac==-1)
            player=kullanici_degistirme(player);            
	else
            player=kullanici_degistirme(player);
        
        dosyaya_yazma();}
    
    else if(game_ended(ilk,son)==true)
	break;
    
    //Kullanici O iken.
    else if(player=='O')
    {
     	int son2,sonuc;
	int yer_var=0;   
        cout<<"\n\nKULLANICI SIRASI "<<player<<""<<endl;
        cout<<"LUTFEN TAS YERINI GIRINIZ:(ORNEGIN:1A,2B,3C,4D......)"<<endl;
	cin>>ilk>>son;
        if(isalpha(son)==0){//KULLANICI ONCE SAYI SONRA HARF GIRMEZSE HATA VERIP CIKIYOR
            cerr<<"HATALI GIRIS YAPTINIZ.(ONCE SAYI SONRA HARF)\n"<<endl;       
            exit(1);}
	son=toupper(son);//kullanici kucuk harf girerse onu buyuk harfe ceviriyor.
	ilk=ilk-1;
	son=son-65;//sutun kismi harflerden olustugu icin 65 cikarttim cunku A=65 dir.		
	son2=son;
        

        
        mumkun=play(ilk,son);
	if(mumkun==-1)
            player=kullanici_degistirme(player);
	else{//Eger kullanicinin oynayabilecegi ve rakibin tasini alabilecegi yer varsa else nin icine giriyor.
        cout<<"------------------------------------------";	
	cout<<"\nKULLANICI HAMLESI:\n";
	
	while(ilk<0 || current_height()<ilk || son2<0|| current_width()<son|| 
                gameCells[ilk][son2].get_member()=='X' ||gameCells[ilk][son2].get_member()=='O')
        {
            cout<<"SATIR VE SUTUN DEGERLERI TABLOYA UYMUYOR VEYA GIRDIGINIZ NOKTALAR UYGUN DEGIL TEKRAR GIRINIZ:\n";
            cin>>ilk>>son;
            if(isalpha(son)==0){
                cerr<<"HATALI GIRIS YAPTINIZ\n"<<endl;       
                exit(1);}
            son=toupper(son);
            ilk=ilk-1;
            son=son-65;
            son2=son;
        }
	sonuc=yerdegis(ilk,son,player,1);
	cout<<"KULLANICININ DONDURDUGU TAS SAYISI==> "<<sonuc<<""<<endl;

	//eger girilen noktalardan tas alamiyorsa kullanici,tekrardan deger girmesi istenecek.
	while(sonuc==0)
	{
            cout<<"\nGIRDIGIN DEGER LEGAL DEGIL TEKRAR DENEYIN:\n"<<endl;
            cin>>ilk>>son;
            if(isalpha(son)==0){
                cerr<<"HATALI GIRIS YAPTINIZ\n"<<endl;       
                exit(1);}            
            son=toupper(son);
            ilk=ilk-1;
            son=son-65;
            son2=son;
		
            while(ilk<0 || current_height()<ilk || son2<0|| current_width()<son || 
                    gameCells[ilk][son2].get_member()=='X' ||gameCells[ilk][son2].get_member()=='O')
            {
		cout<<"SATIR VE SUTUN DEGERLERI TABLOYA UYMUYOR VEYA GIRDIGINIZ NOKTALAR UYGUN DEGIL TEKRAR GIRINIZ:\n";
                cin>>ilk>>son;
                if(isalpha(son)==0){
                    cerr<<"HATALI GIRIS YAPTINIZ\n"<<endl;       
                    exit(1);}                
		son=toupper(son);
		ilk=ilk-1;
		son=son-65;
		son2=son;
            }
            sonuc=yerdegis(ilk,son,player,1);
            cout<<"KULLANICININ DONDURDUGU TAS SAYISI==> "<<sonuc<<""<<endl;
            
	}
        living_cells();
	gameCells[ilk][son2].set_member(player);
	player=kullanici_degistirme(player);
	galip_var_mi=kim_kazandi();	
	//oyunda galip varmi diye bakiyor varsa kazanan oyuncuyu yazip while(1) den cikip oyunu bitiriyor.
	if(galip_var_mi=='X'){
            ekrana_yazma();
            cout<<"\nX OYUNCUSU KAZANDI.\n";
            break;}
	else if(galip_var_mi=='O'){
            ekrana_yazma();
            cout<<"\nO OYUNCUSU KAZANDI.\n";
            break;}
	else if(galip_var_mi=='B'){
            ekrana_yazma();
            cout<<"\nOYUN BERABERE BITII.\n";
            break;}	
	else
            ekrana_yazma();
	}}}
}
    
