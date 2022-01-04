#include "end_menu_renderers.h"

	void menu_renderer(SDL_Renderer* ecran, world_t world){
		SDL_RenderClear(ecran);
		apply_text(ecran, WINDOW_WIDTH/2-100, 10, 100, 100, "Uber Quiche", world.font);
		apply_text(ecran, 100, WINDOW_HEIGHT/2, 500, 100, "press space pour commencer", world.font);
		SDL_RenderPresent(ecran);
	}

	void end_renderer(SDL_Renderer* ecran, world_t world){
		SDL_RenderClear(ecran);
		score_read(ecran, &world);
		apply_text(ecran, WINDOW_WIDTH/2-250, 50, 500, 200, "Liste des derniers scores", world.font);
        apply_text(ecran, 0, 0, 300, 200, "Redemarrer le jeu pour rejouer", world.font);
		SDL_RenderPresent(ecran);
	}