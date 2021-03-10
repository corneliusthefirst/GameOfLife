#ifndef FENETRE_H
#define FENETRE_H

#include <wx/wx.h>
#include <iostream>
#include <tuple>
#include "jeu.h"

class Fenetre : public wxFrame
{
public:
	Jeu _jeu;
	Fenetre(const wxString &title, Jeu jeu);

	// PARTIE BOUTONS
	wxButton *btnStart;
	wxButton *btnStop;
	wxButton *btnClear;

	void OnStart(wxCommandEvent &ev);
	void OnStop(wxCommandEvent &ev);
	void OnClear(wxCommandEvent &ev);

	// PARTIE DESSINER
	// OnPaint va s'executer chque fois la fenetre est redemarree
	void OnPaint(wxPaintEvent &ev);

	// TriggerPaint va creer un wxPaintEvent pour executer OnPaint
	void TriggerPaint();

	// PARTIE SOURIS
	void OnLeftClick(wxMouseEvent &ev);

	// PARTIE MENUBAR
	wxMenuBar *menubar;
	wxMenu *select;
	wxMenu *stable;
	wxMenu *period;
	wxMenu *vaisseau;
	wxMenu *autres;
	wxMenuItem *infini;

	// Chaque methode va ajouter des celulles necessaires.
	void OnBloc(wxCommandEvent &WXUNUSED(ev));
	void OnTube(wxCommandEvent &WXUNUSED(ev));
	void OnBateau(wxCommandEvent &WXUNUSED(ev));
	void OnRuche(wxCommandEvent &WXUNUSED(ev));
	void OnHamecon(wxCommandEvent &WXUNUSED(ev));
	void OnClig(wxCommandEvent &WXUNUSED(ev));
	void OnHorloge(wxCommandEvent &WXUNUSED(ev));
	void OnPenta(wxCommandEvent &WXUNUSED(ev));
	void OnGalaxie(wxCommandEvent &WXUNUSED(ev));
	void OnGliss(wxCommandEvent &WXUNUSED(ev));
	void OnLeger(wxCommandEvent &WXUNUSED(ev));
	void OnR(wxCommandEvent &WXUNUSED(ev));
	void OnU(wxCommandEvent &WXUNUSED(ev));
	void OnInfini(wxCommandEvent &WXUNUSED(ev));
	void Fenetre_Add(std::vector<int> x, std::vector<int> y);
	wxDECLARE_EVENT_TABLE();
};
// LISTE ID
enum
{
	BUTTON_start = 102,
	BUTTON_stop = 103,
	BUTTON_clear = 104,
	STABLE_BLOC = 105,
	STABLE_TUBE = 106,
	STABLE_BATEAU = 107,
	STABLE_RUCHE = 108,
	STABLE_HAMECON = 109,
	PERIOD_CLIG = 110,
	PERIOD_HORLOGE = 111,
	PERIOD_PENTA = 112,
	PERIOD_GALAXIE = 113,
	V_GLISS = 114,
	V_LEGER = 115,
	A_R = 116,
	A_U = 117,
	INFINI = 118,
};

// Application
class MyApp : public wxApp
{
public:
	int interval = 0;
	Fenetre *fenetre;

	// boucle d'action pour chaque iteration du jeu.
	bool render_loop_on = false;
	bool OnInit() override;
	void OnIdle(wxIdleEvent &ev);

	void RenderLoopOn();	//Activer le boucle
	void RenderLoopOff(); //Desactiver la boucle
};
DECLARE_APP(MyApp);

#endif
