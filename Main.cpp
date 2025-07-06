#include <algorithm>
#include <iostream>
#include "libs/EdubotLib.hpp"
#include <chrono>
#include <thread>

int anguloRotacao(int index);

int main(){
    EdubotLib *bot = new EdubotLib();

    const float DIST_SONARES = 40; 
    
    if(bot->connect()){ 

		int moveIndex = 2;
		bool bumpers[4];
	    float distanciaSonares[3];
	    
	    bot->sleepMilliseconds(1300);
	    while(bot->isConnected()){
	    	bot->sleepMilliseconds(200);
			
			bool bumperEsquerdo = bot->getBumper(0);
			bool bumperDireito = bot->getBumper(1);
			
			if(bumperEsquerdo || bumperDireito) {
			    bot->move(-0.5);
				bot->sleepMilliseconds(1000);
				bot->neutral();
				bot->rotate((bumperEsquerdo) ? 90 : -90);
				bot->sleepMilliseconds(1000);
				continue;
			}
			
			for(int i = 2; i >= 0; i--) {
				distanciaSonares[i] = bot->getSonar(i * 3);
				std::cout << "sonares: " << distanciaSonares[i] << std::endl;
			}
			    
 		  auto it = std::max_element(std::begin(distanciaSonares), std::end(distanciaSonares));
            int moveIndex = std::distance(std::begin(distanciaSonares), it);
		  
            bot->rotate(anguloRotacao(moveIndex));
            bot->sleepMilliseconds(1000);
            bot->move(0.28);
            bot->sleepMilliseconds((distanciaSonares[moveIndex] / 0.45) * 1000);
            bot->neutral();

		
		  std::cout << "index: " << moveIndex << std::endl;
		  std::cout << "angulo: " << anguloRotacao(moveIndex) << std::endl;
            std::cout << "tempo dos guri andando: " << (distanciaSonares[moveIndex] / 0.45) * 1000 << "milligongas" << std::endl;
	    }
    		 bot->disconnect();
    }
    	
    else{
        std::cout << "Could not connect on robot!" << std::endl;
    }
    return 0;
}

int anguloRotacao(int index) {
    int angulo;
    
    switch(index) {
        case 0:
            angulo = -90;
            break;
        case 2:
            angulo = 90;
            break;
        default:
            angulo = 0;
            break;
    }
    
    return angulo;
}