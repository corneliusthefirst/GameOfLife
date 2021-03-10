#include "fenetre.h"
#include "wx/sizer.h"
bool MyApp::OnInit() {
	//Grille defaut
	Grille grille(50,80);
	Jeu jeu(grille);
        fenetre = new Fenetre(wxT("Conway Jeu De La Vie"),jeu);
        fenetre->Show(true);
        return true;
}
IMPLEMENT_APP(MyApp);

void MyApp::OnIdle(wxIdleEvent& ev){
	// On va faire avancer le jeu seulement 1 fois chaque 5 appels au OnIdle
	// C'est pour creer une "periode" de mettre a jour
	if(render_loop_on){
		if(interval == 5){
	 		fenetre->_jeu.Avance();
			fenetre->TriggerPaint();
			interval = 0;
		}
		interval++;
		// Comme le IdleEvent est appele qu'une fois, il faut refaire un appel avec RequestMore
		ev.RequestMore();
	}
}
		
void MyApp::RenderLoopOn(){
	if(!render_loop_on){
		// Connect va creer un lien entre un evenement et un handler qui va le traiter
		Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(MyApp::OnIdle));
		render_loop_on = true;
	}
}
void MyApp::RenderLoopOff(){
	if(render_loop_on){
		Disconnect(wxEVT_IDLE, wxIdleEventHandler(MyApp::OnIdle));
		render_loop_on = false;
	}
}


