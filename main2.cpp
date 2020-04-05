#include <sstream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include <allegro.h>
#include <fstream>
#include "Pieza.h"
#include "PiezaL.h"
#include "PiezaJ.h"
#include "PiezaO.h"
#include "PiezaT.h"
#include "PiezaI.h"
#include "PiezaZ.h"
#include "PiezaS.h"
#include <typeinfo>
using namespace std;
void printtab(char**);
void printScore(int,int,int);
void actualizar();
Pieza* piezaRandom(int);
void printContenedor(Pieza*);
void printSiguiente(Pieza*);
void printGameOver(int,bool);
string IngresarNombre();
void printHelp();
void printPuntuaciones();
int Menu();
void jugar(int);
int SelectLevel();
BITMAP* buffer;


int main(int argc, char * argv[]){
	srand(time(NULL));
	
	allegro_init();
	set_window_title("TETRIS");
	install_keyboard();
	install_mouse();
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) { 
       allegro_message("Error al iniciar el sistema de sonido\n%s\n", allegro_error); 
       return 0; 
    }
	set_color_depth(32);
	if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,32*20,32*22,0,0)!=0){
		set_gfx_mode(GFX_TEXT,0,0,0,0);
		allegro_message("Imposible iniciar el modo video\n",allegro_error);
		return 0;
	}
	buffer=create_bitmap(SCREEN_W,SCREEN_H);
	/*Muestra el menu principal*/
	int opc=Menu();
	while(opc!=4){
		if(opc==1){
			jugar(1);
		}//fin del if opc==1
		else if(opc==2){
			int level= SelectLevel();
			jugar(level);
		}else if(opc==3){
			printPuntuaciones();
		}
		opc=Menu();
	}//fin del while del menu
	return 0;
}
END_OF_MAIN();

void jugar(int lev){
	SAMPLE* music;
	SAMPLE* soundfx;
	vector<Pieza*> fila;
	Pieza* actual;
	Pieza* siguiente;
	Pieza* contenedor;
	int level=lev;
	bool pego=true;
	bool perdio=false;
	int rot=4;//rotar a la izquierda
	int rot2=4;//rotar a la derecha
	int ralentizar=0;//ralentizar de caida de pieza
	int ralentizar2=0;//ralentizar del movimiento y rotacion
	int ralentizar3=0;//ralentizar de choque
	int indactual=0;//indice de la pieza actual
	int indsiguiente=0;//indice de la pieza actual
	int indcontenedor=7;//indice del contenedor
	int score=0;
	int total_lines=0;
	int lineas_nivel=0;
	bool contiene=false;
	char ** tablero=new char*[22];
	for(int i=0;i<22;i++){
		tablero[i]=new char[22];
	}
	for(int i=0;i<22;i++){
		for(int j=0;j<12;j++){
			if((i==21)||(i==0)||(j==0)||(j==11))
				tablero[j][i]='*';
			else
				tablero[j][i]='-';
		}
	}
	indactual=rand()%7;
	fila.push_back(piezaRandom(indactual));
	int rmusic=rand()%2;
	if(rmusic==1){
		music = load_sample("./sounds/tetris_music_a.wav");
	}else{
		music = load_sample("./sounds/tetris_music_b.wav");
	}	
	if(!music){
		set_gfx_mode(GFX_TEXT,0,0,0,0);
		allegro_message("Imposible iniciar audio\n",allegro_error);
	}else{
		set_volume(90, 90);
    	play_sample(music,300,150,1000,1);
	}	
	while(!perdio) {
		if(key[KEY_ESC]){
			stop_sample(music);
			perdio=true;
			break;
		}
		if(pego){
			rot=0;
			rot2=0;
			contiene=false;//para poder cambiar de pieza
			indsiguiente=rand()%7;
			actual=piezaRandom(indactual);
			fila.push_back(piezaRandom(indsiguiente));
			siguiente=fila[1];
			//verificar linea por linea desde abajo hacia arriba, si hay una linea horizontal
			int cont=0;
			int cfilas=0;
			for(int i=20;i>0;i--){
				for(int j=10;j>0;j--){
					if(tablero[j][i]!='-'){
						cont++;
					}
				}
				int indfila;
				if(cont==10){
					indfila=i;
					for(int j=10;j>0;j--){
						tablero[j][i]='-';
					}
					i++;
					total_lines++;
					lineas_nivel++;
					cfilas++;
					//empujar filas
					for(int k=indfila;k>cfilas;k--){
						for(int j=10;j>0;j--){
							tablero[j][k]=tablero[j][k-1];
						}
					}
				}
				cont=0;
			}//termina de verificar
			//Determinar el nivel
			if(lineas_nivel-5>=0){
			level++;
			lineas_nivel=0;
			}//termina de determinar el nivel
			//Determinar el score
			if(cfilas==1){//single
				score+=1000;
				soundfx=load_sample("./sounds/single.wav");
				play_sample(soundfx,300,150,1000,0);
			}else if(cfilas==2){//double
				score+=3000;
				soundfx=load_sample("./sounds/double.wav");
				play_sample(soundfx,300,150,1000,0);
			}
			else if(cfilas==3){//triple
				score+=4000;
				soundfx=load_sample("./sounds/triple.wav");
				play_sample(soundfx,300,150,1000,0);
			}	
			else if(cfilas==4){//TETRIS!!!
				score+=6000;
				soundfx=load_sample("./sounds/tetris.wav");
				play_sample(soundfx,300,150,1000,0);
			}
			//comprobar si la primera linea del tablero esta vacia
			//es decir si el jugador hace un perfect clear
			bool perfect_clear=false;
			int ctemp=0;//contador de cada espacio vacio en la primera fila
			for(int i=1;i<11;i++){
				if(tablero[i][20]=='-'){
					ctemp++;
				}
			}
			if((score>0)&&(ctemp==10)){
				perfect_clear=true;//ha hecho un perfect clear!!! omg
				ctemp=0;
			}
			if(perfect_clear){
				perfect_clear=false;
				score+=15000;//y le doy 15000 porque en verdad se merece bastante puntaje
				soundfx=load_sample("./sounds/Incredible.wav");
				play_sample(soundfx,300,150,1000,0);
			}
			//Termina de determinar el score
			pego=false;
		}//fin if pego
		vector<int> posy;
		vector<int> posx;
		int may=0;
		for(int k=0;k<4;k++){
			posy.push_back(actual->getTetrimino()[k].getY());
			posx.push_back(actual->getTetrimino()[k].getX());
		}
		//comprueba si pego
		if(ralentizar3==100){
			for(int k=0;k<4;k++){
				if(tablero[posx[k]][posy[k]+1]!='-'){
					soundfx=load_sample("./sounds/put.wav");
					play_sample(soundfx,300,150,1000,0);
					pego=true;
					indactual=indsiguiente;
					fila.erase(fila.begin());
					break;
				}
			}
			ralentizar3=0;
		}
		//fin de colision
		if(level==26){
			clear(buffer);
			/*printGameOver(score);
			actualizar();*/
			perdio=true;
		}
		//dejar caer la pieza
		if(ralentizar>=(100-(level*4))) {
			ralentizar=0;
			actual->mover(*actual,3,tablero);
		}
		clear_bitmap(buffer);
		for(int k=0;k<4;k++)
			tablero[actual->getTetrimino()[k].getX()][actual->getTetrimino()[k].getY()]=actual->getId();
		printtab(tablero);
		if(indcontenedor!=7){
			printContenedor(contenedor);
		}
		printHelp();
		printScore(score,total_lines,level);
		printSiguiente(siguiente);
		actualizar();
		//borrar la posicion anterior
		if(!pego)
		for(int k=0;k<4;k++){
			tablero[actual->getTetrimino()[k].getX()][actual->getTetrimino()[k].getY()]='-';
		}
		if(key[KEY_P]){//pausa
			ralentizar2++;
			if(ralentizar2==15){
				set_volume(10,10);
				do{
					FONT* f=load_font("./fonts/GameOverFont.pcx",NULL,NULL);
					textprintf_centre_ex(buffer, f, SCREEN_W/2, (SCREEN_H/2)+92,
			   			makecol(230, 255, 100), -1,
				   		"PAUSA");
					textprintf_centre_ex(buffer, f, SCREEN_W/2, (SCREEN_H/2)+120,
			   			makecol(230, 255, 100), -1,
			   			"Pulse Q Para Continuar");
					actualizar();
				}while(!key[KEY_Q]);
				set_volume(90,90);
				ralentizar2=0;
			}			
		}
		if(key[KEY_C]){//si presiona el boton de contenedor
			if(!contiene){
				if(!contenedor){//si el contenedor esta vacio
					contenedor=piezaRandom(indactual);
					actual=piezaRandom(indsiguiente);
					indsiguiente=rand()%7;
					siguiente=piezaRandom(indsiguiente);
				}else{
					actual=piezaRandom(indcontenedor);
					contenedor=piezaRandom(indactual);
				}
				//reinicia los controladores de rotacion
				rot=0;
				rot2=0;
				indcontenedor=indactual;
				contiene=true;
			}		
		}
		if(key[KEY_X]){
			ralentizar2++;
			if(ralentizar2==15){			
				//rotar a la derecha
				if(typeid(*actual)!=typeid(PiezaO)){
					if((rot2==4)||(rot2==0)||(rot==4)||(rot==0)){
						rot2=1;
						rot=3;
					}else{
						rot2++;
						rot--;
					}
					soundfx=load_sample("./sounds/rotate.wav");
					play_sample(soundfx,300,150,1000,0);
					actual->rotard(*actual,rot,rot2,tablero);
				}				
				ralentizar2=0;
			}
		}else if(key[KEY_Z]){
			ralentizar2++;
			if(ralentizar2==15){
				//rotar a la izquierda
				if(typeid(*actual)!=typeid(PiezaO)){
					if((rot==4)||(rot==0)||(rot2==4)||(rot2==0)){
						rot=1;
						rot2=3;
					}else{
						rot++;
						rot2--;
					}
					soundfx=load_sample("./sounds/rotate.wav");
					play_sample(soundfx,300,150,1000,0);
					actual->rotari(*actual,rot,rot2,tablero);
				}								
				ralentizar2=0;
			}
		}else if(key[KEY_LEFT]){
			ralentizar2++;
			if(ralentizar2==15){
				actual->mover(*actual,1,tablero);
				ralentizar2=0;
			}			
		}else if(key[KEY_RIGHT]){
			ralentizar2++;
			if(ralentizar2==15){
				actual->mover(*actual,2,tablero);
				ralentizar2=0;
			}
		}else if(key[KEY_DOWN]){
			ralentizar2++;
			if(ralentizar2==15){
				actual->mover(*actual,3,tablero);
				ralentizar2=0;
			}					
		}else if(key[KEY_SPACE]){
			actual->mover(*actual,3,tablero);
		}
		rest(0);
		ralentizar++;
		ralentizar3++;
		//comprobar si perdio
		for(int i=1;i<11;i++){
			if(tablero[i][1]!='-'){
				perdio=true;
				break;
			}
		}
		if(perdio){
			break;
		}
		clear(buffer);
		//actualizar();
	}//fin de while !perdio || !key[KEY_ESC]
	clear_bitmap(buffer);
	clear_bitmap(screen);
	actualizar();
	if(perdio){
		remove_keyboard();
		bool activarGameover=true;
		stop_sample(music);
		music=load_sample("./sounds/game_over.wav");
		play_sample(music,300,150,1000,0);
		printGameOver(score,activarGameover);
	}
	clear_keybuf();
}
void printtab(char ** tab){
	BITMAP* wall = load_bitmap("./bitmaps/pared.bmp",NULL);
	BITMAP* PI = load_bitmap("./bitmaps/I.bmp",NULL);
	BITMAP* PO = load_bitmap("./bitmaps/O.bmp",NULL);
	BITMAP* PZ = load_bitmap("./bitmaps/Z.bmp",NULL);
	BITMAP* PT = load_bitmap("./bitmaps/T.bmp",NULL);
	BITMAP* PS = load_bitmap("./bitmaps/S.bmp",NULL);
	BITMAP* PJ = load_bitmap("./bitmaps/J.bmp",NULL);
	BITMAP* PL = load_bitmap("./bitmaps/L.bmp",NULL);	
	if((!wall)||(!PI)||(!PO)||(!PZ)||(!PT)||(!PS)||(!PJ)||(!PL)){
		set_gfx_mode(GFX_TEXT,0,0,0,0);
		allegro_message("No se pudieron leer los minos\n",allegro_error);
		exit(0);
	}	
	for(int i=0;i<22;i++){
		for(int j=0;j<12;j++){
			if((tab[j][i]=='*')){
				draw_sprite(buffer, wall ,j*32,i*32);
			}
			if((tab[j][i]=='L')){
				draw_sprite(buffer, PL ,j*32,i*32);
			}
			if((tab[j][i]=='J')){
				draw_sprite(buffer, PJ ,j*32,i*32);
			}
			if((tab[j][i]=='S')){
				draw_sprite(buffer, PS ,j*32,i*32);
			}
			if((tab[j][i]=='Z')){
				draw_sprite(buffer, PZ ,j*32,i*32);
			}
			if((tab[j][i]=='I')){
				draw_sprite(buffer, PI ,j*32,i*32);
			}
			if((tab[j][i]=='O')){
				draw_sprite(buffer, PO ,j*32,i*32);
			}
			if((tab[j][i]=='T')){
				draw_sprite(buffer, PT ,j*32,i*32);
			}
		}
	}

}
void printSiguiente(Pieza* p){
	BITMAP* PI = load_bitmap("./bitmaps/I.bmp",NULL);
	BITMAP* PO = load_bitmap("./bitmaps/O.bmp",NULL);
	BITMAP* PZ = load_bitmap("./bitmaps/Z.bmp",NULL);
	BITMAP* PT = load_bitmap("./bitmaps/T.bmp",NULL);
	BITMAP* PS = load_bitmap("./bitmaps/S.bmp",NULL);
	BITMAP* PJ = load_bitmap("./bitmaps/J.bmp",NULL);
	BITMAP* PL = load_bitmap("./bitmaps/L.bmp",NULL);	
	FONT * font_score= load_font("./fonts/Normal.pcx",NULL,NULL);
	textprintf_centre_ex(buffer, font_score, 15*32, 32*12,
			   makecol(0, 100, 243), -1,
			   "Siguiente pieza");
	if(typeid(*p)==typeid(PiezaL)){
		draw_sprite(buffer, PL ,13*32,32*9);
		draw_sprite(buffer, PL ,13*32,32*10);
		draw_sprite(buffer, PL ,13*32,32*11);
		draw_sprite(buffer, PL ,14*32,32*11);
	}
	if(typeid(*p)==typeid(PiezaJ)){
		draw_sprite(buffer, PJ ,14*32,32*9);
		draw_sprite(buffer, PJ ,14*32,32*10);
		draw_sprite(buffer, PJ ,14*32,32*11);
		draw_sprite(buffer, PJ ,13*32,32*11);
	}
	if(typeid(*p)==typeid(PiezaT)){
		draw_sprite(buffer, PT ,13*32,32*9);
		draw_sprite(buffer, PT ,14*32,32*9);
		draw_sprite(buffer, PT ,15*32,32*9);
		draw_sprite(buffer, PT ,14*32,32*10);
	}
	if(typeid(*p)==typeid(PiezaS)){
		draw_sprite(buffer, PS ,15*32,32*9);
		draw_sprite(buffer, PS ,14*32,32*9);
		draw_sprite(buffer, PS ,14*32,32*10);
		draw_sprite(buffer, PS ,13*32,32*10);
	}
	if(typeid(*p)==typeid(PiezaZ)){
		draw_sprite(buffer, PZ ,13*32,32*9);
		draw_sprite(buffer, PZ ,14*32,32*9);
		draw_sprite(buffer, PZ ,14*32,32*10);
		draw_sprite(buffer, PZ ,15*32,32*10);
	}
	if(typeid(*p)==typeid(PiezaI)){
		draw_sprite(buffer, PI ,14*32,32*8);
		draw_sprite(buffer, PI ,14*32,32*9);
		draw_sprite(buffer, PI ,14*32,32*10);
		draw_sprite(buffer, PI ,14*32,32*11);
	}
	if(typeid(*p)==typeid(PiezaO)){
		draw_sprite(buffer, PO ,13*32,32*9);
		draw_sprite(buffer, PO ,14*32,32*9);
		draw_sprite(buffer, PO ,13*32,32*10);
		draw_sprite(buffer, PO ,14*32,32*10);
	}
}
void printContenedor(Pieza* p){
	BITMAP* PI = load_bitmap("./bitmaps/I.bmp",NULL);
	BITMAP* PO = load_bitmap("./bitmaps/O.bmp",NULL);
	BITMAP* PZ = load_bitmap("./bitmaps/Z.bmp",NULL);
	BITMAP* PT = load_bitmap("./bitmaps/T.bmp",NULL);
	BITMAP* PS = load_bitmap("./bitmaps/S.bmp",NULL);
	BITMAP* PJ = load_bitmap("./bitmaps/J.bmp",NULL);
	BITMAP* PL = load_bitmap("./bitmaps/L.bmp",NULL);	
	FONT * font_score= load_font("./fonts/Normal.pcx",NULL,NULL);
	textprintf_centre_ex(buffer, font_score, 14*32, 32*7,
			   makecol(0, 100, 243), -1,
			   "Contenedor");
	if(typeid(*p)==typeid(Pieza)){

	}else
	if(typeid(*p)==typeid(PiezaL)){
		draw_sprite(buffer, PL ,13*32,32*4);
		draw_sprite(buffer, PL ,13*32,32*5);
		draw_sprite(buffer, PL ,13*32,32*6);
		draw_sprite(buffer, PL ,14*32,32*6);
	}else
	if(typeid(*p)==typeid(PiezaJ)){
		draw_sprite(buffer, PJ ,14*32,32*4);
		draw_sprite(buffer, PJ ,14*32,32*5);
		draw_sprite(buffer, PJ ,14*32,32*6);
		draw_sprite(buffer, PJ ,13*32,32*6);
	}else
	if(typeid(*p)==typeid(PiezaT)){
		draw_sprite(buffer, PT ,13*32,32*4);
		draw_sprite(buffer, PT ,14*32,32*4);
		draw_sprite(buffer, PT ,15*32,32*4);
		draw_sprite(buffer, PT ,14*32,32*5);
	}else
	if(typeid(*p)==typeid(PiezaS)){
		draw_sprite(buffer, PS ,15*32,32*4);
		draw_sprite(buffer, PS ,14*32,32*4);
		draw_sprite(buffer, PS ,14*32,32*5);
		draw_sprite(buffer, PS ,13*32,32*5);
	}else
	if(typeid(*p)==typeid(PiezaZ)){
		draw_sprite(buffer, PZ ,13*32,32*4);
		draw_sprite(buffer, PZ ,14*32,32*4);
		draw_sprite(buffer, PZ ,14*32,32*5);
		draw_sprite(buffer, PZ ,15*32,32*5);
	}else
	if(typeid(*p)==typeid(PiezaI)){
		draw_sprite(buffer, PI ,14*32,32*3);
		draw_sprite(buffer, PI ,14*32,32*4);
		draw_sprite(buffer, PI ,14*32,32*5);
		draw_sprite(buffer, PI ,14*32,32*6);
	}else
	if(typeid(*p)==typeid(PiezaO)){
		draw_sprite(buffer, PO ,13*32,32*4);
		draw_sprite(buffer, PO ,14*32,32*4);
		draw_sprite(buffer, PO ,13*32,32*5);
		draw_sprite(buffer, PO ,14*32,32*5);
	}
}
void printScore(int total_score,int total_lines, int level){
	FONT * font_score= load_font("./fonts/Normal.pcx",NULL,NULL);
	textprintf_right_ex(buffer, font_score, SCREEN_W -(32*3), 20,
			   makecol(0, 100, 243), -1,
			   "Puntuacion %d",
			   total_score);
	textprintf_right_ex(buffer, font_score, SCREEN_W -(32*3), 32,
			   makecol(0, 100, 243), -1,
			   "Lineas %d",
			   total_lines);
	textprintf_right_ex(buffer, font_score, SCREEN_W -(32*3), 44,
			   makecol(0, 100, 243), -1,
			   "Nivel %d",
			   level);
}
void printGameOver(int total_score,bool activarGameover){
	string nombre;
	if(activarGameover){
		nombre=IngresarNombre();
	}	
	if(nombre.compare("")==0){
	}else{
		ifstream lectura("Highscore.txt");
		string linea;
		if(!lectura){
		}else{
			do{			
				getline(lectura,linea);
			}while(!lectura.eof());
		}		
		ofstream escritura("Highscore.txt");
		escritura<<linea<<nombre<<" - "<<total_score<<";";
		escritura.close();
	}
	
	clear_bitmap(buffer);
	clear_bitmap(screen);
	actualizar();
	do{
		FONT * font_gameover=load_font("./fonts/GameOverFont.pcx",NULL,NULL);		
		textprintf_centre_ex(buffer, font_gameover, SCREEN_W/2, (SCREEN_H/2)-36,
			   makecol(230, 255, 100), -1,
			   "El juego ha terminado...");
		textprintf_centre_ex(buffer, font_gameover, SCREEN_W/2, (SCREEN_H/2),
			   makecol(230, 255, 100), -1,
			   "Puntuacion final:");
		textprintf_centre_ex(buffer, font_gameover, SCREEN_W/2, (SCREEN_H/2)+36,
			   makecol(230, 255, 100), -1,
			   "%d",total_score);
		FONT * fontNormal= load_font("./fonts/Normal.pcx",NULL,NULL);
		textprintf_centre_ex(buffer, fontNormal, SCREEN_W/2, (SCREEN_H/2)+92,
			   makecol(230, 255, 100), -1,
			   "Pulse M para volver al menu principal...");
	actualizar();
	}while(!key[KEY_M]);
}
void actualizar(){
	blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}
Pieza* piezaRandom(int indi){
	Pieza* prand;
	if(indi==0){
		prand= new PiezaL();
	}else if(indi==1){
		prand= new PiezaJ();
	}else if(indi==2){
		prand= new PiezaO();
	}else if(indi==3){
		prand= new PiezaT();
	}else if(indi==4){
		prand= new PiezaI();
	}else if(indi==5){
		prand= new PiezaZ();
	}else if(indi==6){
		prand= new PiezaS();
	}else{
		int r=rand()%7;
		return piezaRandom(r);
	}
	/*if(!prand){//si no hay memoria
		exit(0);
	}else{*/
		return prand;
	//}
}
string IngresarNombre(){
	int ralentizar=0;//parpadeo del caret
	string  texto="";                        // texto para editar
    string::iterator iter = texto.begin(); // iterador de string
    int     caret  = 0;                    // la posicion del cursor
    bool    insertar = false;           	   // para ver si toca la tecla
    // ciclo para que ingrese el texto
    FONT * fontNormal= load_font("./fonts/Normal.pcx",NULL,NULL);
    textprintf_ex(buffer, fontNormal, SCREEN_W/2, (SCREEN_H/2), makecol(230, 255, 100),-1, "Ingrese su nombre: ");
    install_keyboard();//vuelve a activar el teclado
    do{
   		while(keypressed()){
        	int  newkey   = readkey();
        	char ASCII    = newkey & 0xff;
        	char scancode = newkey >> 8;
        	// si una letra es presionada
         	if((ASCII >= 65 && ASCII <= 90)||(ASCII >= 90 && ASCII <= 122)){
           		// agregar el nuevo caracter insrtando o reemplazando
            	if(insertar || iter == texto.end())
               		iter = texto.insert(iter, ASCII);
            	else
               		texto.replace(caret, 1, 1, ASCII);
           		//incrementa la posicion del cursor
            	caret++;
            	iter++;
         	}else{
         		switch(scancode){
               		case KEY_DEL:
                  		if(iter != texto.end()){
                  			iter = texto.erase(iter);
                  		} 
               			break;
               		case KEY_BACKSPACE:
                  		if(iter != texto.begin()){
                     		caret--;
                     		iter--;
                    		iter = texto.erase(iter);
                  		}
               			break;
               		case KEY_RIGHT:
                  		if(iter != texto.end()){
                  			caret++;
                  			iter++;
                  		}   
               			break;
               		case KEY_LEFT:
                  		if(iter != texto.begin()){
                  			caret--;
                  			iter--;
                  		} 
               			break;
               		case KEY_INSERT:
                  		if(insertar){
                  			insertar = false;
                  		}else{
                  			insertar = true;
                  		}
               			break;
               		default:
               			break;
            	}//fin del switch
            }//fin else si no escribio una letra
    	}//fin while keypressed
    clear(buffer);
    textprintf_centre_ex(buffer, fontNormal, SCREEN_W/2, (SCREEN_H/2)-84,
   						makecol(230, 255, 100),-1, "Ingrese su Nombre");
    if(texto.length()<1){//hacer que parpadee el caret
    	if(ralentizar==5){
    		textprintf_centre_ex(buffer, fontNormal, SCREEN_W/2,
    			(SCREEN_H/2)-72, makecol(230, 255, 100),-1, "|");
    		ralentizar=1;
    	}
   		textprintf_centre_ex(buffer, fontNormal, SCREEN_W/2,
    			(SCREEN_H/2)-72, makecol(230, 255, 100),-1, " ");
    	rest(150);
    	ralentizar++;
    }    
    textprintf_centre_ex(buffer, fontNormal, SCREEN_W/2, (SCREEN_H/2)-72, makecol(230, 255, 100),-1, "%s",texto.c_str());
    actualizar();
    }while(!key[KEY_ENTER]); //Hasta que pulse Enter
   		return texto;
}
int Menu(){
	BITMAP* mnu;
	clear_bitmap(buffer);
	clear_bitmap(screen);
	int ralentizar=0;
	int opcion=1;
	SAMPLE* backround_music;
	backround_music = load_sample("./sounds/select_option.wav");
	play_sample(backround_music,300,150,1000,1);
	FONT * fontNormal= load_font("./fonts/Normal.pcx",NULL,NULL);
	do{
		switch(opcion){
			case 1:
				mnu=load_bitmap("./bitmaps/mainmenu1.bmp",NULL);
				break;
			case 2:
				mnu=load_bitmap("./bitmaps/mainmenu2.bmp",NULL);
				break;
			case 3:
				mnu=load_bitmap("./bitmaps/mainmenu3.bmp",NULL);
				break;
			case 4:
				mnu=load_bitmap("./bitmaps/mainmenu4.bmp",NULL);
				break;
		}
		if(ralentizar==2){
			ralentizar=0;
			if(key[KEY_DOWN]){
				if(opcion==4){
					opcion=1;
				}else{
					opcion++;
				}
			}
			if(key[KEY_UP]){
				if(opcion==1){
					opcion=4;
				}else{
					opcion--;
				}
			}
		}	
		textprintf_centre_ex(buffer, fontNormal, SCREEN_W/2, SCREEN_H-98,
   						makecol(230, 255, 100),-1, "Muevase con las teclas arriba y abajo");	
		textprintf_centre_ex(buffer, fontNormal, SCREEN_W/2, SCREEN_H-64,
   						makecol(230, 255, 100),-1, "Pulse la tecla Enter para aceptar una opcion...");
		textprintf_centre_ex(buffer, fontNormal, SCREEN_W/2, SCREEN_H-30,
   						makecol(230, 255, 100),-1, "Hecho por 4lbertyson");
		blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
		draw_sprite(buffer, mnu ,0,0);
		actualizar();
		rest(180);
		ralentizar++;
	}while(!key[KEY_ENTER]);
	stop_sample(backround_music);
	return opcion;
}
int SelectLevel(){
	BITMAP* mnu;
	int nivel=1;
	int ralentizar=0;
	FONT * fontNormal= load_font("./fonts/Normal.pcx",NULL,NULL);
	SAMPLE* backround_music;
	backround_music = load_sample("./sounds/level_select.wav");
	play_sample(backround_music,300,150,1000,1);
	clear_bitmap(buffer);
	clear_bitmap(screen);
	actualizar();
	do{
		mnu=load_bitmap("./bitmaps/submenu.bmp",NULL);
		blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
		draw_sprite(buffer, mnu ,0,0);
		actualizar();
		if(ralentizar==3){
			ralentizar=0;
			if(key[KEY_DOWN]){
				clear_bitmap(buffer);
				clear_bitmap(screen);
				actualizar();
				if(nivel==1){
					nivel=20;
				}else{
					nivel--;
				}
			}
			if(key[KEY_UP]){
				clear_bitmap(buffer);
				actualizar();
				if(nivel==20){
					nivel=1;
				}else{
					nivel++;
				}
			}
		}	
		textprintf_centre_ex(buffer, fontNormal, SCREEN_W/2, SCREEN_H/2,
   						makecol(230, 255, 100),-1, "Nivel: %d",nivel);
		textprintf_centre_ex(buffer, fontNormal, SCREEN_W/2, SCREEN_H-64,
   						makecol(230, 255, 100),-1, "Cambie el nivel con las teclas arriba y abajo");
		textprintf_centre_ex(buffer, fontNormal, SCREEN_W/2, SCREEN_H-30,
   						makecol(230, 255, 100),-1, "Pulse la tecla E para aceptar un nivel...");
		blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
		ralentizar++;
		rest(1);
	}while(!key[KEY_E]);
	stop_sample(backround_music);
	return nivel;
}
void printHelp(){
	FONT * font_score= load_font("./fonts/Normal.pcx",NULL,NULL);
	textprintf_right_ex(buffer, font_score, SCREEN_W -(32*4), SCREEN_H-200,
			   makecol(230, 255, 100), -1,
			   "Ayuda!");
	textprintf_right_ex(buffer, font_score, SCREEN_W -(33*2), SCREEN_H-185,
			   makecol(230, 255, 100), -1,
			   "Mover izquierda= <-");
	textprintf_right_ex(buffer, font_score, SCREEN_W -(33*2), SCREEN_H-170,
			   makecol(230, 255, 100), -1,
			   "Mover derecha= ->");
	textprintf_right_ex(buffer, font_score, SCREEN_W -(33*2), SCREEN_H-155,
			   makecol(230, 255, 100), -1,
			   "Rotar izquierda= z");
	textprintf_right_ex(buffer, font_score, SCREEN_W -(33*2), SCREEN_H-140,
			   makecol(230, 255, 100), -1,
			   "Rotal derecha= x");
	textprintf_right_ex(buffer, font_score, SCREEN_W , SCREEN_H-125,
			   makecol(230, 255, 100), -1,
			   "desplazar= space_bar");
	textprintf_right_ex(buffer, font_score, SCREEN_W -(33*2), SCREEN_H-110,
			   makecol(230, 255, 100), -1,
			   "Cambiar pieza= c");
	textprintf_right_ex(buffer, font_score, SCREEN_W -(33*2), SCREEN_H-95,
			   makecol(230, 255, 100), -1,
			   "Pausa= p");
	textprintf_right_ex(buffer, font_score, SCREEN_W -(33*2), SCREEN_H-80,
			   makecol(230, 255, 100), -1,
			   "Salir= esc");
}
void printPuntuaciones(){
	clear_bitmap(buffer);
	clear_bitmap(screen);
	actualizar();
	ifstream lectura("Highscore.txt");
	FONT * font_score= load_font("./fonts/Normal.pcx",NULL,NULL);
	string linea;
		if(!lectura){
			textprintf_centre_ex(buffer, font_score, SCREEN_W/2, SCREEN_H/2,
			  	makecol(230, 255, 100), -1,
			    "No se han guardado puntuaciones");
		}else{
			//listar puntuaciones
			vector<string> jugadores;
			do{			
				getline(lectura,linea);
			}while(!lectura.eof());
			boost::split(jugadores,linea,boost::is_any_of(";"));
			for(int i=0;i<jugadores.size();i++){
					textprintf_centre_ex(buffer, font_score, SCREEN_W/2, 20*i,
				  	makecol(230, 255, 100), -1,
				    "%s",jugadores[i].c_str());		
			}
			lectura.close();
		}
		actualizar();
	do{
		textprintf_centre_ex(buffer, font_score, SCREEN_W/2, SCREEN_H-60,
		  	makecol(230, 255, 100), -1,
		    "Presione ESC para volver al menu principal...");
		actualizar();
	}while(!key[KEY_ESC]);
}